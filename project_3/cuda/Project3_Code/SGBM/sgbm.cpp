#include "sgbm.h"
#include "mainwindow.h"     // for global var
#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <cuda.h>
#include "cuda_runtime.h"

extern "C++"
{
void cost_computation(int *Lr, int *initCost, uint8_t m_u8Directions, uint8_t m_u8DEBUGLeftNeighbor,
                                 uint16_t m_u16height_after_census, uint16_t m_u16width_after_census,
                                 uint16_t m_u16TotalDisp, uint8_t m_u16P1, uint8_t m_u16P2);

void compute_hamming(uint64_t *ct1, uint64_t *ct2, int *accumulatedCost,
                                uint64_t m_u16yMin, uint64_t m_u16yMax, uint64_t m_u16xMin, uint64_t m_u16xMax,
                                uint64_t m_u16TotalDisp, uint64_t m_u16width_after_census, uint64_t m_s16MinDisp);

void cost_aggregation(int *aggregatedCost, int *Lr, uint16_t m_u16height_after_census, uint16_t m_u16width_after_census,
                      uint16_t m_u16TotalDisp, uint16_t m_u8Directions);

}

StereoFPGA::StereoFPGA() : StereoAlgo ()
{
    m_u8Directions = 4;
    m_eStereoAlgo = eStereoAlgoType_FPGA;
}

StereoFPGA::~StereoFPGA()
{    if (nullptr != m_ActiveAggrCost)
    {
        delete [] m_ActiveAggrCost;
        m_ActiveAggrCost = nullptr;
    }
}

void StereoFPGA::SetNumOfDirections(uint8_t u8NewDirect)
{
    if(4 >= u8NewDirect)
    {
        m_u8Directions =  u8NewDirect;
    }
}

void StereoFPGA::ComputeAlgo(cv::Mat LeftImg, cv::Mat RightImg, cv::Mat *DepthImg)
{
    start_time = omp_get_wtime();

    //Compute some extra parameters based on the parameters from the GUI
    m_u16TotalDisp = abs(m_s16MaxDisp - m_s16MinDisp);
    m_fFactor = 1;
    //m_fFactor = 256/m_u16TotalDisp;
    m_u8BlockSize_half =(m_u8BlockSize / 2); // This performs a "floor" rounding

    //##################################################################################
    //                             Calculate Imgage Size
    //##################################################################################

    // Get image size to define size of memory allocation
    unsigned short height  = LeftImg.rows;
    unsigned short width  = LeftImg.cols;

    // Size of the required data structures after census transform without padding
    m_u16height_after_census  = height-(m_u8BlockSize-1);
    m_u16width_after_census  = width-(m_u8BlockSize-1);


    // Set usable dimentions of the image with valid information (region of interest) after SGBM computation
    m_u16yMin = 0;
    m_u16yMax = m_u16height_after_census;

    if(m_s16MaxDisp < 0 )
    {
        m_u16xMin = 0;
    }
    else
    {
        m_u16xMin = m_s16MaxDisp;
    }
    if (m_s16MinDisp > 0)
    {
        m_u16xMax = m_u16width_after_census;
    }
    else
    {
        m_u16xMax = m_u16width_after_census+m_s16MinDisp;
    }

    //##################################################################################
    //         Memory Allocation of different Stages of the algorithm
    //##################################################################################

    //Memory for the census-transformed data
    uint64_t *ct1 = new uint64_t[m_u16height_after_census*m_u16width_after_census];
    if (nullptr == ct1) {
        printf("Memory allocation failed for ct1..! \n");
        return;
    }

    uint64_t *ct2 = new uint64_t[m_u16height_after_census*m_u16width_after_census];
    if (nullptr == ct2) {
        printf("Memory allocation failed for ct2..! \n");
        return;
    }

    // Memory to store cost of size: (m_u16height_after_census) * (m_u16width_after_census) * (number of disparities)
    int u32SizeOfInitCost = (m_u16height_after_census)*(m_u16width_after_census)*m_u16TotalDisp;
    m_ActiveInitCost = new int[u32SizeOfInitCost];

    //##################################################################################
    //                                 SGBM Algorithm
    //##################################################################################



    //##################################################################################
    //                                  Census Transform
    //##################################################################################
    compute_census_transform(LeftImg, ct1);
    compute_census_transform(RightImg, ct2);


    //#######################################################################################
    //                      Hamming Distance as cost initialization
    //#######################################################################################
    compute_hamming(ct1, ct2, m_ActiveInitCost, m_u16yMin, m_u16yMax, m_u16xMin, m_u16xMax, m_u16TotalDisp,
                    m_u16width_after_census, m_s16MinDisp);

    //##############################################################################################
    //                                      Cost Computation
    //##############################################################################################
    cv::Mat disparitySGBM(m_u16height_after_census, m_u16width_after_census, CV_8U);

    uint32_t u32SizeOfLrCost = m_u8Directions*m_u16height_after_census*m_u16width_after_census*m_u16TotalDisp;
    m_ActiveLrCost = new int[u32SizeOfLrCost];
    m_ActiveAggrCost = new int[m_u16height_after_census * m_u16width_after_census *m_u16TotalDisp];

    compute_SGM(m_ActiveInitCost, &disparitySGBM);

    // Copy result to be shown in the GUI
    disparitySGBM.copyTo(*DepthImg);

    run_time = omp_get_wtime() - start_time;
    printf("%lf seconds\n", run_time);

    // Free Memory
    delete [] ct1;
    delete [] ct2;
    delete [] m_ActiveInitCost;
    delete [] m_ActiveLrCost;
    delete [] m_ActiveAggrCost;
}


//##################################################################################
//       Private Methods
//##################################################################################

void StereoFPGA::compute_census_transform(cv::Mat img, uint64_t *ct)
{
    //##################################################################################
    //       Census Transform
    //##################################################################################

    // Notes:
    //Limits are set so that only valid pixels from the images are considered -> no padding is required
    //The uint64_t data structure is used to manage large BlockSize. However for a BlockSize of up to 5x5 pixels uint32_t should be sufficient
    for (int i=m_u8BlockSize_half; i<img.rows-m_u8BlockSize_half; i++) {
        for (int j=m_u8BlockSize_half; j<img.cols-m_u8BlockSize_half; j++) {
            uint64_t temp=0;
            for (int ki=i-m_u8BlockSize_half; ki<=i+m_u8BlockSize_half; ki++) {
                for (int kj=j-m_u8BlockSize_half; kj<=j+m_u8BlockSize_half; kj++) {
                    unsigned char ref;
                    ref = img.at<unsigned char>(ki,kj);
                    if (ki!=i || kj!=j) {
                        temp = temp << 1;
                        if (ref < img.at<unsigned char>(i,j) ) {
                            temp = temp | 1;
                        }
                    }
                }
            }
            ct[(i-m_u8BlockSize_half)*(img.cols-m_u8BlockSize_half*2)+j-m_u8BlockSize_half] = temp;
        }
    }
} // end compute_census_transform()

void StereoFPGA::init_Lr(int *Lr, int *initCost) {
    int sizeOfCpd = m_u16height_after_census*m_u16width_after_census*m_u16TotalDisp;
    for (int r=0; r<m_u8Directions; r++) {
        for (int i=0; i<sizeOfCpd; i++) {
            Lr[r*sizeOfCpd+i] = initCost[i];
        }
    }
} // end init_Lr()

int StereoFPGA::compute_SGM(int *initCost, cv::Mat *disparitySGBM)
{

    //##################################################################################
    //          SGBM Algorithm
    //##################################################################################
    // Initialize Lr(p,d) to C(p,d)
    init_Lr(m_ActiveLrCost, initCost);

    int* cuda_m_ActiveLrCost;
    int* cuda_initCost;

    cudaMalloc((void **)&cuda_m_ActiveLrCost, sizeof(int));
    cudaMalloc((void **)&cuda_initCost, sizeof(int));

    cudaMemcpy(cuda_m_ActiveLrCost, m_ActiveLrCost, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(cuda_initCost, initCost, sizeof(int), cudaMemcpyHostToDevice);

    // Compute cost along different directions
    cost_computation(cuda_m_ActiveLrCost, cuda_initCost, m_u8Directions, m_u8DEBUGLeftNeighbor,
                     m_u16height_after_census, m_u16width_after_census, m_u16TotalDisp,
                     m_u16P1, m_u16P2);

    cudaDeviceSynchronize();

    cudaMemcpy(m_ActiveLrCost, cuda_m_ActiveLrCost, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(initCost, cuda_initCost, sizeof(int), cudaMemcpyHostToDevice);

    cudaFree(cuda_m_ActiveLrCost);
    cudaFree(cuda_initCost);

    // Cost aggregation
    cost_aggregation(m_ActiveAggrCost, m_ActiveLrCost, m_u16height_after_census, m_u16width_after_census, m_u16TotalDisp,
                     m_u8Directions);

    // Disparity computation
    StereoFPGA::calc_disp(m_ActiveAggrCost, disparitySGBM);

    return 0;
}

void saveDisparityMap(int *disparity, cv::Mat *disparityMap, float_t m_fFactor) {
    int width = disparityMap->cols;

    for (int i = 0; i < disparityMap->rows; ++i) {
        for (int j = 0; j < width; ++j) {
            if(255 == disparity[i*width+j])
            {
                disparityMap->at<unsigned char>(i, j) = (unsigned char) (disparity[i*width+j]);
            }
            else
            {
                disparityMap->at<unsigned char>(i, j) = (unsigned char) (disparity[i*width+j]*m_fFactor);
            }
        }
    }

} // end saveDisparityMap

void StereoFPGA::calc_disp(int *Cost, cv::Mat *disparityBM)
{
    //#######################################################################################
    //          SGBM Disparity Computation
    //#######################################################################################
    int *bm_output = new int[m_u16height_after_census * m_u16width_after_census];

    for (int i=0; i<m_u16height_after_census; i++) {
        for (int j=0; j<m_u16width_after_census; j++) {
            int *costPtr = Cost + (i*m_u16width_after_census+j)*m_u16TotalDisp;
            int minCost = costPtr[0];
            int SecondBest = INT_MAX;
            int mind = 0;
            for (int d=1; d<m_u16TotalDisp; d++) {
                if (costPtr[d] < minCost) {
                    SecondBest = minCost;
                    minCost = costPtr[d];
                    mind = d;
                }
                else if (costPtr[d] < SecondBest)
                {
                    SecondBest = costPtr[d];
                }
            }
            //#######################################################################################
            //          Uniqueness Ratio
            //#######################################################################################
            if(minCost <= SecondBest - (SecondBest * m_u8UniqueRatio/128))
            {
                bm_output[i*m_u16width_after_census+j] = mind;//out_disp;
            }
            else
            {
                bm_output[i*m_u16width_after_census+j] = 255;
            }
        }
    }

    // Convert data from int to OpenC cv::Mat in order to be displayed
    saveDisparityMap(bm_output, disparityBM, m_fFactor);

    delete []  bm_output;
}
