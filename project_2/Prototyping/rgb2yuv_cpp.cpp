//g++ rgb2yuv_cpp.cpp -o rgb2yuv_cpp `pkg-config --cflags opencv4 --libs opencv4`


#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void matwrite(const string& filename, const Mat& mat) {
    ofstream fs(filename, fstream::binary);
	unsigned char *input = (unsigned char*)(mat.data);

    // Header
    int type = mat.type();
    int channels = mat.channels();
    //fs.write((char*)&mat.rows, sizeof(int));    // rows
    //fs.write((char*)&mat.cols, sizeof(int));    // cols
    //fs.write((char*)&type, sizeof(int));        // type
    //fs.write((char*)&channels, sizeof(int));    // channels

    // Data
	
	int i,j;
	for(int i = 0;i < mat.rows ;i++){
        for(int j = 0;j < mat.cols ;j++){
			input[j + i] = mat.data;
        }
    }
	
	fs.write(input
    
	for (int r = 0; r < mat.rows; ++r) {
	int rowsz = CV_ELEM_SIZE(type) * mat.cols;
		fs.write(mat.ptr<char>(r), rowsz);
	}
    
}

Mat matread(const string& filename) {
    ifstream fs(filename, fstream::binary);

    // Header
    int rows = 640;
    int cols = 480;
    int type = CV_8UC3;
    int channels = 3;

    fs.read((char*)&rows, sizeof(int));         // rows
    fs.read((char*)&cols, sizeof(int));         // cols
    fs.read((char*)&type, sizeof(int));         // type
    fs.read((char*)&channels, sizeof(int));     // channels
    
    // Data
    Mat M(640, 480, type);
    fs.read((char*)M.data, CV_ELEM_SIZE(type) * rows * cols);
    return M;
}

int main() {

int IMAGE_WIDTH = 640;
int IMAGE_HEIGHT = 480;
Mat img, img_out;

FILE *fp = NULL;
char *imagedata = NULL;
char *input = NULL;
int framesize = IMAGE_WIDTH * IMAGE_HEIGHT;

//Open rgb image.
fp = fopen("image.rgb", "rb");

//Memory allocation for bayer image data buffer.
imagedata = (char*) malloc (sizeof(char) * framesize);
input = (char*) malloc (sizeof(char) * framesize);

//Read image data and store in buffer.
fread(imagedata, sizeof(char), framesize, fp);

//Create Opencv mat structure for image dimension. For 8 bit bayer, type should be CV_8UC1.
img.create(IMAGE_HEIGHT, IMAGE_WIDTH, CV_16UC3);

//Copy RGB image to Mat
memcpy(img.data, imagedata, framesize);

free(imagedata);

fclose(fp);

//Perform demosaicing process
cvtColor(img, img_out, COLOR_RGB2YUV); 

//Open yuv image.
fp = fopen("outputCPP.yuv", "wb");

//Copy Mat data to char
memcpy(input, img_out.data, framesize);

fputs(input, fp);SS

return 0;
}













