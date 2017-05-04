/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESINGLECOMPONENTGAUSSIANBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESINGLECOMPONENTGAUSSIANBLURFILTER_H


#include "GPUImageGaussianBlurFilter.h"

// This filter merely performs the standard Gaussian blur on the red color channel (assuming a luminance image)
class GPUImageSingleComponentGaussianBlurFilter : public GPUImageGaussianBlurFilter{
public:
    GPUImageSingleComponentGaussianBlurFilter();
    virtual ~GPUImageSingleComponentGaussianBlurFilter();

protected:
    virtual void genVertexShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);
    virtual void genFragmentShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);

};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESINGLECOMPONENTGAUSSIANBLURFILTER_H
