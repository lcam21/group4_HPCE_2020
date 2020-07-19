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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

int main (int argc, char **argv) {
	
	int i = 0;
    int opt = -1;
	int memoryLeakFlag = 0;
	int infoAuhtorFlag = 0;
	int infoExcutionAppFlag = 0;
	
	char *pathFile;
	char *const args[] = {pathFile, NULL};
	char *const envp[] = {"LD_PRELOAD=../lib/.libs/libmemcheck.so", NULL};
	
	
	char usageMessage[] = "\n# USAGE MODE: \n"
		"./memcheck [ -p ./PROGRAM ] [-h] [-a] \n"
		"-a displays the information of the author of the program. \n"
		"-h displays the usage message to let the user know how to execute the application. \n"
		"-p PROGRAM specifies the path to the program binary that will be analyzed \n"
		"Example:\n"
		"./memcheck -p path/case4\n";
	    
	char authorsInfo[] = "\n# AUTHORS INFORMATION\n"
		"# Tecnologico de Costa Rica (www.tec.ac.cr)\n"
		"# Course: MP-6171 High Performance Embedded Systems\n"
		"# Developers Name: Verny Morales and Luis Carlos Alvarez\n"
		"# Developers email: verny.morales@gmail.com and lcam03@gmail.com\n";
	
	while ((opt = getopt(argc, argv, "ahp")) != -1) {
        i++;
        switch(opt) {
			case 'p':
                pathFile = argv[i+1];
                memoryLeakFlag = 1;
                i++;
                break;
			case 'a':
                infoAuhtorFlag = 1;
                break;
            case 'h':
                infoExcutionAppFlag = 1;
                break;
			default:
				printf("Error..");
		 }
    }
	
	if (infoAuhtorFlag == 1){
		printf("%s", authorsInfo);
   }
   
   if (infoExcutionAppFlag == 1){
	   printf("%s", usageMessage);
   }
   
   if (memoryLeakFlag == 1){
	   printf("\n#Analyzing the amount of memory leaks for the program: %s \n", pathFile);
	   execve(pathFile,args,envp);
   }
}
