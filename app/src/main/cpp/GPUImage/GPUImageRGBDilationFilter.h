/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGERGBDILATIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGERGBDILATIONFILTER_H

#include "GPUImageTwoPassTextureSamplingFilter.h"

// For each pixel, this sets it to the maximum value of each color channel in a rectangular neighborhood extending out dilationRadius pixels from the center.
// This extends out brighter colors, and can be used for abstraction of color images.
class GPUImageRGBDilationFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageRGBDilationFilter();
    GPUImageRGBDilationFilter(int radius);
    virtual ~GPUImageRGBDilationFilter();

protected:
    // Acceptable values for dilationRadius, which sets the distance in pixels to sample out from the center, are 1, 2, 3, and 4.
    GLint m_iDilationRadius;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGERGBDILATIONFILTER_H
