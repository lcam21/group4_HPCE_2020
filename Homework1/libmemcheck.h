#include<stdio.h>
#include<stddef.h>

char memory[20000];

/*The structure definition to contain metadata of each block allocated or deallocated*/
struct block{
 size_t size; 	/*Carries the size of the block described by it*/
 int free;  	/*This flag is used to know whether the block described by the metadata structure is free or not -- > if free, it is 			set to 1. Otherwise 0.*/
 struct block *next; /*Points to the next metadata block*/
};


/*Pointing to the main block of memory which is initially free (no storage allocation yet)*/
struct block *freeList=(void*)memory;

/*The function definitions which are defined in the next source file malloc.c*/
void initialize();
void split(struct block *fitting_slot,size_t size);
void *malloc(size_t noOfBytes);
void merge();

void free(void* ptr);

