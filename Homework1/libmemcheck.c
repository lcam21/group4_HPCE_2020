#include<stdio.h>
#include<stddef.h>
#include "libmemcheck.h" /*Here we include the header file given above*/

/*Initializing the block of memory*/
void initialize(){
 freeList->size=20000-sizeof(struct block); 
 freeList->free=1;
 freeList->next=NULL;
}

/*Making way for a new block allocation by splitting a free block -- (Assume first fit algorithm)*/
void split(struct block *fitting_slot,size_t size){
 struct block *new=(void*)((void*)fitting_slot+size+sizeof(struct block));
 new->size=(fitting_slot->size)-size-sizeof(struct block);
 new->free=1;
 new->next=fitting_slot->next;
 fitting_slot->size=size;
 fitting_slot->free=0;
 fitting_slot->next=new;
}

/*      We use the First-fit-algorithm to find a free block to allocate memory. Assume that we get a request to allocate a block of memory of size 500 bytes. Starting from the first metadata block we can go on searching for the first block which has enough space to allocate. If we get the free block sizes to be 250, 130 and 750 in order, we will allocate the block of size 750.
		
	     If we find a free block which exactly fits the required size, we don't need to do the splitting. So this function is only required if we have what is more than required.

              The arguments accepted by this function are --- A pointer to the metadata block which refers to the block of memory whose size is more than required.(fitting_slot) and the required size of the memory chunk to be allocated.

               Here we create a new metadata block pointer called "new". And it should point to the location provided by passing(setting aside) a block of memory which is equal to the_size_of_the_metadata_block_we_considered + the_size_requested_to_be_allocated

               Then this new pointer points to the metadata block referring to the next free chunk.
As you can see from the code, I have set the attributes of both the new and fitting_slot metadata blocks accordingly.*/

/*Function MyMalloc(malloc)*/
void *malloc(size_t noOfBytes){
 
 printf("Entro");
 struct block *curr,*prev;
 void *result;
 if(!(freeList->size)){ 
  initialize();
  printf("Memory initialized\n");
 }				  /*This condition will initialize the memory if it is not initialized at the beginning. This set of 					   statements will be executed only if the size of the first metadata block is not set yet. That 					   means, if the memory is still not initialized.*/

 curr=freeList;	/*Now we make the temporary pointer curr to pint to the start of the metadata block list.*/
 while((((curr->size)<noOfBytes)||((curr->free)==0))&&(curr->next!=NULL)){
  prev=curr;
  curr=curr->next;
  printf("One block checked\n");
 } /*If this condition is met, the metadata block we checked cannot be used for the allocation. So we execute the following statements. That is you go on checking one metadata block at a time.*/


if((curr->size)==noOfBytes){
  curr->free=0;
  result=(void*)(++curr);
  printf("Exact fitting block allocated\n");
  return result;
 }		
/*If this condition is met, the metadata block we checked refers to a chunk of memory that exactly fits the required size. So set the free flag to 0, indicating that it is allocated. Then return the starting address of the block of allocated memory.*/


 else if((curr->size)>(noOfBytes+sizeof(struct block))){
  split(curr,noOfBytes);
  result=(void*)(++curr);
  printf("Fitting block allocated with a split\n");
  return result;
 }

/*If this condition is met, the metadata block we checked refers to a chunk of memory that is of size greater than what is required. So invoke the split() function to allocate only the block which is required and then return the starting address of the block of allocated memory.*/

else{
  result=NULL;
  printf("Sorry. No sufficient memory to allocate\n");
  return result;
 }
}

/*This is to merge the consecutive free blocks by removing the metadata block in the middle. This will save space.*/
void merge(){
 struct block *curr,*prev;
 curr=freeList;
 while((curr->next)!=NULL){
  if((curr->free) && (curr->next->free)){
   curr->size+=(curr->next->size)+sizeof(struct block);
   curr->next=curr->next->next;
  }
  prev=curr;
  curr=curr->next;
 }
}

void free(void* ptr){
 if(((void*)memory<=ptr)&&(ptr<=(void*)(memory+20000))){
  struct block* curr=ptr;
  --curr;
  curr->free=1;
  merge();
 }
 else printf("Please provide a valid pointer allocated by MyMalloc\n");
}
/* Here we check whether the address to which the pointer given as an argument to the function actually lies within the address range of the memory array that we used for the purpose. If yes,we simply set the free flag in the metadata block to 1 indicating that it is free and scan through and merge the consecutive blocks that are free, if any.*/

