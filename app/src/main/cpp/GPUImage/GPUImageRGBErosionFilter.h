/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGERGBEROSIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGERGBEROSIONFILTER_H


#include "GPUImageTwoPassTextureSamplingFilter.h"


// For each pixel, this sets it to the minimum value of each color channel in a rectangular neighborhood extending out dilationRadius pixels from the center.
// This extends out dark features, and can be used for abstraction of color images.

class GPUImageRGBErosionFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageRGBErosionFilter();
    GPUImageRGBErosionFilter(int radius);
    virtual ~GPUImageRGBErosionFilter();

protected:

    // Acceptable values for erosionRadius, which sets the distance in pixels to sample out from the center, are 1, 2, 3, and 4.
    GLint m_iErosionRadius;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGERGBEROSIONFILTER_H
