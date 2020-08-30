// CUDA-C includes
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>

__device__ int find_minLri(int *Lrpr, uint16_t m_u16TotalDisp) {
    int minLri = INT_MAX;
    for (int i=0; i<m_u16TotalDisp; i++) {
        if (minLri > Lrpr[i]) {
            minLri = Lrpr[i];
        }
    }
    return minLri;
} // end find_minLri()

__device__ int find_min(int a, int b, int c, int d) {
    int minimum = a;
    if (minimum > b)
        minimum = b;
    if (minimum > c)
        minimum = c;
    if (minimum > d)
        minimum = d;
    return minimum;
} // end find_min()

__global__ void cost_computation(int *Lr, int *initCost, uint8_t m_u8Directions, uint8_t m_u8DEBUGLeftNeighbor,
                                 uint16_t m_u16height_after_census, uint16_t m_u16width_after_census,
                                 uint16_t m_u16TotalDisp, uint8_t m_u16P1, uint8_t m_u16P2) {
    //#######################################################################################
    //          SGBM Cost Computation
    //#######################################################################################

    int r = blockIdx.x * blockDim.x + threadIdx.x;

    // Computing cost along 5 directions only. (i,j-1) (i-1,j-1) (i-1,j) (i-1,j+1) (i,j+1)
    __shared__ int iDisp, jDisp;

    if (r < m_u8Directions) {
    //for (int r=0; r<m_u8Directions; r++) {
        if (r==0) {
            iDisp = 0; jDisp = 0-m_u8DEBUGLeftNeighbor;
        }
        else if (r==1) {
            iDisp = -1; jDisp = -1;
        }
        else if (r==2) {
            iDisp = -1; jDisp = 0;
        }
        else if (r==3) {
            iDisp = -1; jDisp = 1;
        }
        else if (r==4) {
            iDisp = 0; jDisp = 1;
        }
        //if (i < m_u16height_after_census) {
        for (int i=0; i<m_u16height_after_census; i++) {
            //if (i < m_u16width_after_census) {
            for (int j=0; j<m_u16width_after_census; j++) {
                // Compute p-r
                int iNorm = i + iDisp; //height
                int jNorm = j + jDisp; //width
                int *Lrpr = Lr+((r*m_u16height_after_census+iNorm)*m_u16width_after_census+jNorm)*m_u16TotalDisp;

                //#######################################################################################
                //         Find min_k{Lr(p-r,k)}
                //#######################################################################################
                //if (d < m_u16TotalDisp) {
                for (int d=0; d<m_u16TotalDisp; d++) {
                    int Cpd = initCost[(i*m_u16width_after_census+j)*m_u16TotalDisp+d];

                    int tmp;
                    if ( (((r==0)||(r==1))&&(jNorm<0)) || (((r==1)||(r==2)||(r==3))&&(i==0)) || ((r==3)&&(j==m_u16width_after_census-1)))
                    {
                        tmp = Cpd;
                    } else {
                        int minLri = find_minLri(Lrpr, m_u16TotalDisp);
                        int Lrpdm1, Lrpdp1;
                        if (d==0)
                            Lrpdm1 = INT_MAX-m_u16P1;
                        else
                            Lrpdm1 = Lrpr[d-1];
                        if (d==m_u16TotalDisp-1)
                            Lrpdp1 = INT_MAX-m_u16P1;
                        else
                            Lrpdp1 = Lrpr[d+1];

                        int v1 = find_min(Lrpr[d], Lrpdm1+m_u16P1, Lrpdp1+m_u16P1, minLri+m_u16P2);

                        tmp = Cpd + v1 - minLri;
                    }
                    Lr[((r*m_u16height_after_census+i)*m_u16width_after_census+j)*m_u16TotalDisp+d] = tmp;
                }
            }
        }
    }
} // end cost_computation()

__device__ int compute_hamming_distance (uint64_t a, uint64_t b)
{
    //#######################################################################################
    //Hamming Distance as cost initialization
    //#######################################################################################
    uint64_t tmp;
    int sum = 0;

    tmp = a^b;
    for(int i=0;i<64;i++){
        if(tmp&0x1<<i){
            sum ++;
        }
    }
    return sum;
} // end compute_hamming_distance()



__global__ void compute_hamming(uint64_t *ct1, uint64_t *ct2, int *accumulatedCost,
                                uint64_t m_u16yMin, uint64_t m_u16yMax, uint64_t m_u16xMin, uint64_t m_u16xMax,
                                uint64_t m_u16TotalDisp, uint64_t m_u16width_after_census, uint64_t m_s16MinDisp)
{
    //#######################################################################################
    //Hamming Distance as cost initialization
    //#######################################################################################

    int d = blockIdx.x * blockDim.x + threadIdx.x;

    for (int i=m_u16yMin; i<m_u16yMax; i++) {
        for (int j=m_u16xMin; j<m_u16xMax; j++) {
            //for (int d=0; d<m_u16TotalDisp; d++) {
            if (d < m_u16TotalDisp) {
                int dist = compute_hamming_distance(ct1[i*m_u16width_after_census+j], ct2[i*m_u16width_after_census+j-(d+m_s16MinDisp)]);
                int Loop = (i*m_u16width_after_census+j)*m_u16TotalDisp + d;
                accumulatedCost[Loop] = dist;
            }
        }
    }
} // end compute_cost()


__global__ void cost_aggregation(int *aggregatedCost, int *Lr, uint16_t m_u16height_after_census,
                                 uint16_t m_u16width_after_census, uint16_t m_u16TotalDisp, uint16_t m_u8Directions)
{
    //#######################################################################################
    //          SGBM Cost Aggregation
    //#######################################################################################
    for (int i=0; i<m_u16height_after_census; i++)
    {
        for (int j=0; j<m_u16width_after_census; j++)
        {
            for (int d=0; d<m_u16TotalDisp; d++)
            {
                int *ptr = aggregatedCost + (i*m_u16width_after_census+j)*m_u16TotalDisp+d;
                ptr[0] = 0;

                for (int r=0; r<m_u8Directions; r++)
                {
                    ptr[0] += Lr[((r*m_u16height_after_census+i)*m_u16width_after_census+j)*m_u16TotalDisp+d];
                }
            }
        }
    }
}// end cost_aggregation()
