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

//gcc rgb2yuv_c.c -o rgb2yuv_c `pkg-config --cflags opencv4 --libs opencv4`
//./rgb2yuv_c -i image.rgb -o outputC.yuv

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int rgb2yuvPixel (int R, int G, int B){
	
	int Y, V, U;

	unsigned int pixel32;
	unsigned char *pixel = (unsigned char *)&pixel32;


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

	return pixel32;
}

void rgb2yuv (char *input_image, char *output_image){

	FILE *in, *out;
	int R, G, B, y2;	
	unsigned int pixelRGB, pixel32;
	unsigned char pixelYUV[3];

	in = fopen(input_image, "rb");
	out = fopen(output_image, "wb");
	if (!in  ||  !out) {
		printf("Error..\n");
	}

	for(int i=0; i<640*480; i++){
		fread(&pixelRGB, 3, 1, in);
		R  = ((pixelRGB & 0x000000ff));
		G  = ((pixelRGB & 0x0000ff00)>>8);
		B  = ((pixelRGB & 0x00ff0000)>>16);
	
		pixel32 = rgb2yuvPixel(R, G, B);
		pixelYUV[0] = (pixel32 & 0x000000ff);
		pixelYUV[1] = (pixel32 & 0x0000ff00) >> 8;
		pixelYUV[2] = (pixel32 & 0x00ff0000) >> 16;

		fwrite(pixelYUV, 3, 1, out);
	}
	
	fclose(in);
	fclose(out);

}


int main (int argc, char **argv) {
	
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
		rgb2yuv (pathRGBFile, pathYUVFile);
	}

	return 0;
}
