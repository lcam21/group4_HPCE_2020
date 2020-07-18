// C program for writing 
// struct to file 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// a struct to read and write 
struct memoryleaks { 
    int mallocNumber;
	int freeNumber;
}; 

int main () {
	 
	FILE *outfile; 
	
	outfile = fopen ("memoryleaks.dat", "w"); // open file for writing 

	struct memoryleaks input1 = {0,0}; 
	
	fwrite (&input1, sizeof(struct memoryleaks), 1, outfile); // write struct to file 
	
	input1.freeNumber++;
	input1.mallocNumber++;
	
	fwrite (&input1, sizeof(struct memoryleaks), 1, outfile); // write struct to file 
	
	fclose (outfile); // close file 

	return 0; 
} 
