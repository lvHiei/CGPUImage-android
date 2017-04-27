/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEXYDERIVATIVEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEXYDERIVATIVEFILTER_H


#include "GPUImageSobelEdgeDetectionFilter.h"

// I'm using the Prewitt operator to obtain the derivative, then squaring the X and Y components and placing the product of the two in Z.
// In tests, Prewitt seemed to be tied with Sobel for the best, and it's just a little cheaper to compute.
// This is primarily intended to be used with corner detection filters.

class GPUImageXYDerivativeFilter : public GPUImageSobelEdgeDetectionFilter{
public:
    GPUImageXYDerivativeFilter();
    virtual ~GPUImageXYDerivativeFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEXYDERIVATIVEFILTER_H
