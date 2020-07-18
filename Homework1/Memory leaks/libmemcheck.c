/*
 * Tecnologico de Costa Rica (www.tec.ac.cr)
 * Course: MP-6171 High Performance Embedded Systems
 * Developers Name: Verny Morales and Luis Carlos Alvarez
 * Developers email: verny.morales@gmail.com and lcam03@gmail.com
 * General purpose: Analyze the amount of memory leaks
 * Input: 
 * Output: Console mesage with amount of memory leaks
 * Reference: https://danluu.com/malloc-tutorial/
 * Compile: gcc -fPIC -shared -o libmemcheck.so libmemcheck.c
 */

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int magic;
};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;
int mallocNumber = 0;
int freeNumber = 0;

void __attribute__((destructor)) writeMemoryleaks(); 

void writeMemoryleaks(){
	printf("\nAnalysis finished! \nMemory allocations: %d" 
			"\nMemory free: %d \nTotal memory leaks found: %d\n\n"
			,mallocNumber-1, freeNumber, mallocNumber-1-freeNumber);
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
	
	struct block_meta *block;

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
		block->free = 0;
		block->magic = 0x77777777;
		}
	}
	
	mallocNumber++;
	return(block+1);
}

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}


void free(void *ptr) {
	if (!ptr) {
		return;
	}

	struct block_meta* block_ptr = get_block_ptr(ptr);
	assert(block_ptr->free == 0);
	assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
	block_ptr->free = 1;
	block_ptr->magic = 0x55555555;
	
	freeNumber++;
}
