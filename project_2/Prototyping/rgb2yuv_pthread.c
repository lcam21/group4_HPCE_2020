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

//gcc -lpthread rgb2yuv_pthread.c -o rgb2yuv_pthread 
//./rgb2yuv_pthread -i image.rgb -o outputPT.yuv

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <time.h>  

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

int rgb2yPixel (int R, int G, int B){
	
	int Y;

	Y = (0.257 * R) + (0.504 * G) + (0.098 * B) + 16;

 	if (Y > 255) {
		Y = 255;
	}

	if (Y < 0) {
		Y = 0;
	}
	
	return Y;
}

int rgb2uPixel (int R, int G, int B){
	
	int U;

	U = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128;

	if (U > 255) {
		U = 255;
	}
	
	if (U < 0) {
		U = 0;
	}

	return U;
}

int rgb2vPixel (int R, int G, int B){
	
	int V;

	V =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128;

	if (V > 255) {
		V = 255;
	}

	if (V < 0) {
		V = 0;
	}

	return V;
}


void rgb2yuv (char *input_image, char *output_image){

	FILE *in, *out;
	int R, G, B, y2, i, size;	
	unsigned int pixelRGB, pixel32;
	unsigned char pixelYUV[3];
	unsigned char *pixel = (unsigned char *)&pixel32;

	in = fopen(input_image, "rb");
	out = fopen(output_image, "wb");
	if (!in  ||  !out) {
		printf("Error..\n");
	}
	
	iret1 = pthread_create( &thread1, NULL, rgb2yPixel, (void*) message1);
	if(iret1) {
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}
	
	iret2 = pthread_create( &thread2, NULL, rgb2uPixel, (void*) message2);
	if(iret2) {
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		exit(EXIT_FAILURE);
	}
	
	iret3 = pthread_create( &thread3, NULL, rgb2vPixel, (void*) message3);
	if(iret3) {
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
		exit(EXIT_FAILURE);
	}
	
	size = IMAGE_WIDTH*IMAGE_HEIGHT;
	for(i=0; i<size; i++){
		fread(&pixelRGB, 3, 1, in);
		R  = ((pixelRGB & 0x000000ff));
		G  = ((pixelRGB & 0x0000ff00)>>8);
		B  = ((pixelRGB & 0x00ff0000)>>16);
	
		//pixel32 = rgb2yuvPixel(R, G, B);
		
		pixel[0] = rgb2yPixel(R, G, B);
		pixel[1] = rgb2uPixel(R, G, B);
		pixel[2] = rgb2vPixel(R, G, B);
		pixel[3] = 0;
		
		pixelYUV[0] = (pixel32 & 0x000000ff);
		pixelYUV[1] = (pixel32 & 0x0000ff00) >> 8;
		pixelYUV[2] = (pixel32 & 0x00ff0000) >> 16;

		fwrite(pixelYUV, 3, 1, out);
	}
	
	fclose(in);
	fclose(out);

}


int main (int argc, char **argv) {
	
	clock_t t;
	
	pthread_t thread1, thread2, thread3;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    const char *message3 = "Thread 3";
    int  iret1, iret2, iret3;
	
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
