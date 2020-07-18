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

#include <stdio.h>

void free(void *ptr) {
	printf("\nEntro\n");

}
