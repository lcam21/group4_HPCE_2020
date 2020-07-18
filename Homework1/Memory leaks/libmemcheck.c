/*
 * Tecnologico de Costa Rica (www.tec.ac.cr)
 * Course: MP-6171 High Performance Embedded Systems
 * Developers Name: Verny Morales and Luis Carlos Alvarez
 * Developers email: verny.morales@gmail.com and lcam03@gmail.com
 * General purpose: 
 * Input: 
 * Output: 
 *
 */

// gcc -fPIC -shared -o libmemcheck.so libmemcheck.c

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct memoryleaks { 
    int mallocNumber;
	int freeNumber;
}; 

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int magic; // For debugging only. TODO: remove this in non-debug mode.
};

#define META_SIZE sizeof(struct block_meta)


void *global_base = NULL;
struct memoryleaks input1 = {0,0}; 
FILE *outfile;
int fileOpenFlag = 0;

void writeMemoryleaks(){
	if (fileOpenFlag == 0){
		outfile = fopen("memoryleaks.dat", "w"); // open file for writing
		fileOpenFlag = 1;
	}
	fwrite (&input1, sizeof(struct memoryleaks), 1, outfile); 
	//fprintf(outfile,"%d-%d\n",input1.mallocNumber,input1.freeNumber);
	//fclose (outfile); // close file 
}

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); // Not thread safe.
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;
}

void *malloc(size_t size) {
	input1.mallocNumber = input1.mallocNumber + 1;
	//writeMemoryleaks();
	struct block_meta *block;
	// TODO: align size?

	if (size <= 0) {
	return NULL;
	}

	if (!global_base) { // First call.
	block = request_space(NULL, size);
	if (!block) {
	  return NULL;
	}
	global_base = block;
	} else {
	struct block_meta *last = global_base;
	block = find_free_block(&last, size);
	if (!block) { // Failed to find free block.
	  block = request_space(last, size);
	  if (!block) {
		return NULL;
	  }
	} else {      // Found free block
	  // TODO: consider splitting block here.
	  block->free = 0;
	  block->magic = 0x77777777;
	}
	}

	return(block+1);
}

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}


void free(void *ptr) {
	input1.freeNumber = input1.freeNumber + 1;
	writeMemoryleaks();
	if (!ptr) {
		return;
	}

	// TODO: consider merging blocks once splitting blocks is implemented.
	struct block_meta* block_ptr = get_block_ptr(ptr);
	assert(block_ptr->free == 0);
	assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
	block_ptr->free = 1;
	block_ptr->magic = 0x55555555;
}
