/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGENONMAXIMUMSUPPRESSIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGENONMAXIMUMSUPPRESSIONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

class GPUImageNonMaximumSuppressionFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageNonMaximumSuppressionFilter();
    virtual ~GPUImageNonMaximumSuppressionFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGENONMAXIMUMSUPPRESSIONFILTER_H
