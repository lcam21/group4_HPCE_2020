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

//gcc -pthread rgb2yuv_pthread.c -o rgb2yuv_pthread 
//./rgb2yuv_pthread -i image.rgb -o outputPT.yuv

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>  

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

unsigned int pixelRGB[IMAGE_WIDTH*IMAGE_HEIGHT];
unsigned char pixelYUV[IMAGE_WIDTH*IMAGE_HEIGHT][3];

void *rgb2yuvPixel(void *pOption){
	
	int R, G, B, Y, V, U, limitU, limitL, size, i;
	int *option = (int*) pOption;

	unsigned int pixel32;
	unsigned char *pixel = (unsigned char *)&pixel32;
	
	size = IMAGE_WIDTH*IMAGE_HEIGHT/4;
	
	if(*option == 1){
		limitU = 0;
		limitL = size;
	}else if(*option == 2){
		limitU = size;
		limitL = size*2;
	}else if(*option == 3){
		limitU = size*2;
		limitL = size*3;
	}else if(*option == 4){
		limitU = size*3;
		limitL = size*4;
	}
	
	for(i=limitU; i<limitL; i++){

		R  = ((pixelRGB[i] & 0x000000ff));
		G  = ((pixelRGB[i] & 0x0000ff00)>>8);
		B  = ((pixelRGB[i] & 0x00ff0000)>>16);

		Y = (0.257 * R) + (0.504 * G) + (0.098 * B) + 16;
		V =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128;
		U = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128;


		if (Y > 255) {
			Y = 255;
		}

		if (U > 255) {
			U = 255;
		}

		if (V > 255) {
			V = 255;
		}

		if (Y < 0) {
			Y = 0;
		}
		
		if (U < 0) {
			U = 0;
		}

		if (V < 0) {
			V = 0;
		}

		pixel[0] = Y;
		pixel[1] = U;
		pixel[2] = V;
		pixel[3] = 0;
		
		pixelYUV[i][0] = (pixel32 & 0x000000ff);
		pixelYUV[i][1] = (pixel32 & 0x0000ff00) >> 8;
		pixelYUV[i][2] = (pixel32 & 0x00ff0000) >> 16;
	}
}

void rgb2yuv (char *input_image, char *output_image){

	pthread_t thread1, thread2, thread3, thread4;
	int  iret1, iret2, iret3, iret4;
	
	FILE *in, *out;
	int R, G, B, y2, i, size;
	int option1 = 1;
	int option2 = 2;
	int option3 = 3;
	int option4 = 4;
	
	size = IMAGE_WIDTH*IMAGE_HEIGHT;
	
	in = fopen(input_image, "rb");
	out = fopen(output_image, "wb");
	if (!in  ||  !out) {
		printf("Error..\n");
	}
	
	
	for(i=0; i<size; i++){
		fread(&pixelRGB[i], 3, 1, in);
	}
	
	iret1 = pthread_create( &thread1, NULL, rgb2yuvPixel, &option1);
	 if(iret1) {
		 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		 exit(EXIT_FAILURE);
	 }
	 
	 iret2 = pthread_create( &thread2, NULL, rgb2yuvPixel, &option2);
	 if(iret2) {
		 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		 exit(EXIT_FAILURE);
	 }
	 
	 iret3 = pthread_create( &thread3, NULL, rgb2yuvPixel, &option3);
	 if(iret3) {
		 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
		 exit(EXIT_FAILURE);
	 }
	 
	 iret4 = pthread_create( &thread4, NULL, rgb2yuvPixel, &option4);
	 if(iret4) {
		 fprintf(stderr,"Error - pthread_create() return code: %d\n",iret4);
		 exit(EXIT_FAILURE);
	 }
	 
	  pthread_join(thread1, NULL);
	  pthread_join(thread2, NULL); 
	  pthread_join(thread3, NULL); 
	  pthread_join(thread4, NULL); 
	
	for(i=0; i<size; i++){
		fwrite(pixelYUV[i], 3, 1, out);
	}
	
	fclose(in);
	fclose(out);
}


int main (int argc, char **argv) {
	
	clock_t t;
	
	int i = 0;
	int opt = -1;
	int rgbFlag = 0;
	int yuvFlag = 0;
	int infoAuhtorFlag = 0;
	int infoExcutionAppFlag = 0;
	char *pathRGBFile;
	char *pathYUVFile;
	
	char usageMessage[] = "\n# USAGE MODE: \n"
		"./rgb2yuv_c [ -i RGBfile ] [ -o YUVfile ] [-h] [-a] \n"
		"-i RGBfile specifies the RGB file to be converted. \n"
		"-o YUVfile specifies the output file name. \n"
		"-a displays the information of the author of the program. \n"
		"-h displays the usage message to let the user know how to execute the application; \n"
		"Yocto prompt: \n"
		"rgb2yuv_c -i image.rgb -o outputC.yuv \n";
	    
	char authorsInfo[] = "\n# AUTHORS INFORMATION\n"
		"# Tecnologico de Costa Rica (www.tec.ac.cr)\n"
		"# Course: MP-6171 High Performance Embedded Systems\n"
		"# Developers Name: Verny Morales and Luis Carlos Alvarez\n"
		"# Developers email: verny.morales@gmail.com and lcam03@gmail.com\n";
	
	while ((opt = getopt(argc, argv, "ioah")) != -1) {
        i++;
        switch(opt) {
		case 'i':
			pathRGBFile = argv[i+1];
			rgbFlag = 1;
			i++;
			break;
		case 'o':
			pathYUVFile = argv[i+1];
			yuvFlag = 1;
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

	if (rgbFlag == 1 && yuvFlag == 1){
		t = clock();
		rgb2yuv (pathRGBFile, pathYUVFile);
		t = clock() - t;
		printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	}

	return 0;
}

