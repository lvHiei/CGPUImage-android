/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGEGREYSCALEFILTER_H
#define CGPUIMAGE_GPUIMAGEGREYSCALEFILTER_H


#include "GPUImageFilter.h"

/**
 * Converts an image to grayscale (a slightly faster implementation of the saturation filter, without the ability to vary the color contribution)
 */
class GPUImageGreyscaleFilter : public GPUImageFilter{
public:
    GPUImageGreyscaleFilter();
    virtual ~GPUImageGreyscaleFilter();
};


#endif //CGPUIMAGE_GPUIMAGEGREYSCALEFILTER_H
