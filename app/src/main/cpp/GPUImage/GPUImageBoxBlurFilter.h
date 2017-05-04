/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEBOXBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEBOXBLURFILTER_H


#include "GPUImageGaussianBlurFilter.h"

/** A hardware-accelerated box blur of an image
 */
class GPUImageBoxBlurFilter : public GPUImageGaussianBlurFilter{
public:
    GPUImageBoxBlurFilter();
    virtual ~GPUImageBoxBlurFilter();

protected:
    virtual void genVertexShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);
    virtual void genFragmentShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);

};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEBOXBLURFILTER_H
