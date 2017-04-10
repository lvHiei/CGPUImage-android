/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELAPLACIANFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELAPLACIANFILTER_H

#include "GPUImage3x3ConvolutionFilter.h"

class GPUImageLaplacianFilter : public GPUImage3x3ConvolutionFilter{
public:
    GPUImageLaplacianFilter();
    virtual ~GPUImageLaplacianFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELAPLACIANFILTER_H
