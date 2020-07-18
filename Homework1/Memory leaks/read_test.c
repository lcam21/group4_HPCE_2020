// C program for reading 
// struct from a file 
#include <stdio.h> 
#include <stdlib.h> 

struct memoryleaks { 
    int mallocNumber;
	int freeNumber;
};  

// Driver program 
int main () 
{ 
	FILE *infile; 
	struct memoryleaks input; 
	
	// Open person.dat for reading 
	infile = fopen ("memoryleaks.dat", "r"); 
	if (infile == NULL) 
	{ 
		fprintf(stderr, "\nError opening file\n"); 
		exit (1); 
	} 
	
	// read file contents till end of file 
	while(fread(&input, sizeof(struct memoryleaks), 1, infile)) 
		printf ("mallocNumber = %d freeNumber = %d \n", input.mallocNumber, 
		input.freeNumber); 

	// close file 
	fclose (infile); 

	return 0; 
} 
