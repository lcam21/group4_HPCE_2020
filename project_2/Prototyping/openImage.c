//g++ DisplayImage.cpp -o DisplayImage `pkg-config --cflags opencv4 --libs opencv4`


#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    Mat img_out;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cvtColor(image, img_out, CV_BGR2YUV);

    FileStorage file("some_name.yuv", FileStorage::WRITE);
    file << "matName" << someMatrixOfAnyType;

    waitKey(0);

    return 0;
}
