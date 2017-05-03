/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_ANDROID_GPUIMAGEDILATIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEDILATIONFILTER_H


#include "GPUImageTwoPassTextureSamplingFilter.h"

// For each pixel, this sets it to the maximum value of the red channel in a rectangular neighborhood extending out dilationRadius pixels from the center.
// This extends out bright features, and is most commonly used with black-and-white thresholded images.
class GPUImageDilationFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageDilationFilter();
    GPUImageDilationFilter(int radius);
    virtual ~GPUImageDilationFilter();

protected:
    // Acceptable values for dilationRadius, which sets the distance in pixels to sample out from the center, are 1, 2, 3, and 4.
    GLint m_iDilationRadius;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEDILATIONFILTER_H
