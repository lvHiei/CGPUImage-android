/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELOCALBINARYPATTERNFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELOCALBINARYPATTERNFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

// This is based on "Accelerating image recognition on mobile devices using GPGPU" by Miguel Bordallo Lopez, Henri Nykanen, Jari Hannuksela, Olli Silven and Markku Vehvilainen
// http://www.ee.oulu.fi/~jhannuks/publications/SPIE2011a.pdf

// Right pixel is the most significant bit, traveling clockwise to get to the upper right, which is the least significant
// If the external pixel is greater than or equal to the center, set to 1, otherwise 0
//
// 2 1 0
// 3   7
// 4 5 6

// 01101101
// 76543210

class GPUImageLocalBinaryPatternFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageLocalBinaryPatternFilter();
    virtual ~GPUImageLocalBinaryPatternFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELOCALBINARYPATTERNFILTER_H
