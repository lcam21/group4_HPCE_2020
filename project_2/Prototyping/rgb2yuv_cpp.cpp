
//g++ rgb2yuv_cpp.cpp -o rgb2yuv_cpp `pkg-config --cflags opencv4 --libs opencv4`
//./rgb2yuv_cpp -i image.rgb -o outputC.yuv

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
using namespace cv;

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

void saveYUV(Mat matYUV, char *fileNameYUV){

	FILE *pFileYuv;
	int bufLen = IMAGE_WIDTH * IMAGE_HEIGHT * 3 / 2;
	unsigned char* pYuvBuf = new unsigned char[bufLen];
	
	pFileYuv = fopen(fileNameYUV, "wb");
	printf("Saving  YUV file..\n");
	fwrite(matYUV.data, sizeof(unsigned char), bufLen, pFileYuv);
	fclose(pFileYuv);

	pFileYuv = NULL;
	delete [] pYuvBuf;
}

Mat readRAWFile(char *fileNameRGB){
	Mat matRGB;
	FILE *fp = NULL;
	unsigned char* pRgbBuf = NULL;
	unsigned int pixelRGB;
	unsigned char pixelYUV[3];
	int framesize = IMAGE_WIDTH * IMAGE_HEIGHT;
	int bufLen = IMAGE_WIDTH * IMAGE_HEIGHT * 2;

	//Open rgb image
	fp = fopen(fileNameRGB, "rb");
	printf("Opening the RAW file..\n");

	//Memory allocation for bayer image data buffer.
	pRgbBuf = (unsigned char *)malloc(bufLen);
	
	//Read image data and store in buffer.
	while(!feof(fp)){
		fread(pRgbBuf, bufLen, 1, fp);
	}
	
	/*
	 for(int i=0; i<640*480; i++){
		fread(&pixelRGB, 3, 1, fp);
		pRgbBuf[i] = pixelRGB;
	}
	*/

	//Create Opencv mat structure for image dimension. For 8 bit bayer, type should be CV_8UC1.
	matRGB.create(IMAGE_HEIGHT, IMAGE_WIDTH, CV_16UC3);

	//Copy RGB image to Mat
	memcpy(matRGB.data, pRgbBuf, framesize);

	free(pRgbBuf);

	fclose(fp);
	printf("Converting  RAW file to Mat..\n");
	
	return matRGB;
}

void rgb2yuv (char *input_image, char *output_image){

	Mat matRGB, matYUV;
	
	matRGB = readRAWFile(input_image);

	printf("Converting  RGB  to YUV..\n");
	cvtColor(matRGB, matYUV, COLOR_BGR2YUV);
	
	saveYUV(matYUV, output_image);
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












