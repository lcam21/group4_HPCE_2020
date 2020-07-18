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

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int mallocNumber = 0;
int freeNumber = 0;

void __attribute__((destructor)) writeMemoryleaks(); 

void writeMemoryleaks(){

	printf("Analysis finished!" 
			"\nMemory allocations: %d" 
			"\nMemory free: %d "
			"\nTotal memory leaks found: %d\n"
			, mallocNumber-1, freeNumber, 
			mallocNumber-1-freeNumber);
}

void *malloc(size_t size) {
	
	static void *(*libc_malloc) (size_t);
	
	if (!libc_malloc){
		libc_malloc = (void *(*)(size_t)) dlsym(RTLD_NEXT, "malloc");
	}
	
	mallocNumber++;
	void* ret = libc_malloc(size);
	return ret;
}

void free(void *ptr) {
	
	static void (*libc_free)(void *);
	
	if (!libc_free){
		libc_free = (void(*)(void *)) dlsym(RTLD_NEXT, "free");
	}
	
	freeNumber++;	
	libc_free(ptr);
}
