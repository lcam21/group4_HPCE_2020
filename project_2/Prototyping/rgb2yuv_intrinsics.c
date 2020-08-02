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


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h> 
#include <arm_neon.h> 

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

void rgb2yuv(char *input_image, char *output_image){

	FILE *in, *out;
	int totalBytes = IMAGE_WIDTH * IMAGE_HEIGHT * 3;
    int totalPixels = IMAGE_WIDTH * IMAGE_HEIGHT;
	
	unsigned char buffer_in[totalBytes];
    signed char buffer_out[totalBytes];
	
	//To save results 
	uint8x16x3_t rgb_x3x16_tmp;
	uint8x16x3_t yuv_x3x16_tmp;
	
	//Buffers
	uint8_t *rgb_ptr = buffer_in;
    uint8_t *yuv_ptr = buffer_out;

	//Open files for RGB and YUV
	in = fopen(input_image, "rb");
	out = fopen(output_image, "wb");
	
	if (!in  ||  !out) {
		printf("Error..\n");
	}
	
	//Loading the buffer
	fread(buffer_in,totalBytes,1,in);
	
	//go over the image every 16 pixels
	for(int i = 0; i<totalPixels/16; i++)
		
		//loading 16 pixels (R, G, B components)
		rgb_x3x16_tmp = vld3q_u8(rgb_ptr+i*16*3);
		
		//Dividing the data of the vector for each color component
		//Red
		uint8x8_t high_r = vget_high_u8(rgb_x3x16_tmp.val[2]); //Duplicate vector element to vector
		uint8x8_t low_r = vget_low_u8(rgb_x3x16_tmp.val[2]); //Duplicate vector element to vector
		int16x8_t signed_high_r = vreinterpretq_s16_u16(vaddl_u8(high_r, vdup_n_u8(0))); //Vector reinterpret cast operation
		int16x8_t signed_low_r = vreinterpretq_s16_u16(vaddl_u8(low_r, vdup_n_u8(0))); //Vector reinterpret cast operation
		
		//Green
		uint8x8_t high_g = vget_high_u8(rgb_x3x16_tmp.val[1]); //Duplicate vector element to vector
		uint8x8_t low_g = vget_low_u8(rgb_x3x16_tmp.val[1]); //Duplicate vector element to vector
		int16x8_t signed_high_g = vreinterpretq_s16_u16(vaddl_u8(high_g, vdup_n_u8(0))); //Vector reinterpret cast operation
		int16x8_t signed_low_g = vreinterpretq_s16_u16(vaddl_u8(low_g, vdup_n_u8(0))); //Vector reinterpret cast operation
		
		//Blue
		uint8x8_t high_b = vget_high_u8(rgb_x3x16_tmp.val[0]); //Duplicate vector element to vector
		uint8x8_t low_b = vget_low_u8(rgb_x3x16_tmp.val[0]); //Duplicate vector element to vector
		int16x8_t signed_high_b = vreinterpretq_s16_u16(vaddl_u8(high_b, vdup_n_u8(0))); //Vector reinterpret cast operation
		int16x8_t signed_low_b = vreinterpretq_s16_u16(vaddl_u8(low_b, vdup_n_u8(0))); //Vector reinterpret cast operation
		
		//Y component
		//Duplicate vector element to scalar
		uint8x8_t coef1 = vdup_n_u8(66);
        uint8x8_t coef2 = vdup_n_u8(129);
        uint8x8_t coef3 = vdup_n_u8(25);
	
		uint16x8_t high_y = vmull_u8(high_r, coef1); //Unsigned Multiply long 
		high_y = vmlal_u8(high_y, high_g, coef2); //Unsigned Multiply-Add Long
		high_y = vmlal_u8(high_y, high_b, coef3); //Unsigned Multiply-Add Long
		uint16x8_t low_y  = vmull_u8(low_r, coef1); //Unsigned Multiply long 
		low_y = vmlal_u8(low_y, low_g, coef2); //Unsigned Multiply-Add Long
		low_y = vmlal_u8(low_y, low_b, coef3); //Unsigned Multiply-Add Long
		high_y = vaddq_u16(high_y, vdupq_n_u16(128)); //Add
		low_y = vaddq_u16(low_y, vdupq_n_u16(128)); //Add
		//Join two smaller vectors into a single larger vector
		//Unsigned saturating shift right narrow
		uint8x16_t y = vcombine_u8(vqshrn_n_u16(low_y, 8), vqshrn_n_u16(high_y, 8)); 
		yuv_x3x16_tmp.val[0] = y; //-> Component Y
		
		//V component
		//Duplicate vector element to scalar
		scoef1 = vdupq_n_s16(-38);
		scoef2 = vdupq_n_s16(-74);
		scoef3 = vdupq_n_s16(112);
		
		int16x8_t high_v = vmulq_s16(signed_high_r, scoef1); //Multiply
		high_v = vmlaq_s16(high_v, signed_high_g, scoef2); //Multiply-add to accumulator
		high_v = vmlaq_s16(high_v, signed_high_b, scoef3); //Multiply-add to accumulator
		int16x8_t low_v = vmulq_s16(signed_low_r, scoef1); //Multiply
		low_v = vmlaq_s16(low_v, signed_low_g, scoef2); //Multiply-add to accumulator
		low_v = vmlaq_s16(low_v, signed_low_b, scoef3); //Multiply-add to accumulator
		high_v = vaddq_s16(high_v, vdupq_n_s16(128)); //Add
		low_v = vaddq_s16(low_v, vdupq_n_s16(128)); //Add
		//Join two smaller vectors into a single larger vector
		//Unsigned saturating shift right narrow
		int8x16_t v = vcombine_s8(vqshrn_n_s16(low_v, 8), vqshrn_n_s16(high_v, 8));
		v = vaddq_s8(v, vdupq_n_s8(128)); //Add
		yuv_x3x16_tmp.val[2] = vreinterpretq_u8_s8(v); //-> Component V
		
		//U component
		//Duplicate vector element to scalar
		int16x8_t scoef1 = vdupq_n_s16(112);
		int16x8_t scoef2 = vdupq_n_s16(-94);
		int16x8_t scoef3 = vdupq_n_s16(-18);
		
		int16x8_t high_u = vmulq_s16(signed_high_r, scoef1); //Multiply
		high_u = vmlaq_s16(high_u, signed_high_g, scoef2); //Multiply-add to accumulator
		high_u = vmlaq_s16(high_u, signed_high_b, scoef3); //Multiply-add to accumulator
		int16x8_t low_u = vmulq_s16(signed_low_r, scoef1); //Multiply
		low_u = vmlaq_s16(low_u, signed_low_g, scoef2); //Multiply-add to accumulator
		low_u = vmlaq_s16(low_u, signed_low_b, scoef3); //Multiply-add to accumulator
		high_u = vaddq_s16(high_u, vdupq_n_s16(128)); //Add
		low_u = vaddq_s16(low_u, vdupq_n_s16(128)); //Add
		//Join two smaller vectors into a single larger vector
		//Unsigned saturating shift right narrow
		int8x16_t u = vcombine_s8(vqshrn_n_s16(low_u, 8), vqshrn_n_s16(high_u, 8));
		u = vaddq_s8(u, vdupq_n_s8(128)); //Add
		yuv_x3x16_tmp.val[1] = vreinterpretq_u8_s8(u); //-> Component U
	
		//Joining the 3 components
		vst3q_u8(yuv_ptr, yuv_x3x16_tmp); //Store multiple 3-element structures from three registers
		yuv_ptr += 3*16; //Move to the next block of registers
	}
	//write the file YUV
    fwrite(buffer_out,totalBytes,1,write_ptr);  
	
	//Close files
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
		rgb2yuv(pathRGBFile, pathYUVFile);
		t = clock() - t;
		printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	}

	return 0;
}

