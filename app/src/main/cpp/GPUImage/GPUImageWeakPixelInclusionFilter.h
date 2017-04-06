/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEWEAKPIXELINCLUSIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEWEAKPIXELINCLUSIONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

class GPUImageWeakPixelInclusionFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageWeakPixelInclusionFilter();
    virtual ~GPUImageWeakPixelInclusionFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEWEAKPIXELINCLUSIONFILTER_H
