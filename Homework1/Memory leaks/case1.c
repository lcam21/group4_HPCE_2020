// hello.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* name1 = malloc(7 * sizeof(char));
	char* name2 = malloc(7 * sizeof(char));
	//char* name3 = malloc(7 * sizeof(char));
	//char* name4 = malloc(7 * sizeof(char));
	free(name1);
	//free(name2);
	//free(name3);
	printf("Hola!\n\n");
	return 0;
}
