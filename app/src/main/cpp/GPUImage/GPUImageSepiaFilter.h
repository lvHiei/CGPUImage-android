/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGESEPIAFILTER_H
#define CGPUIMAGE_GPUIMAGESEPIAFILTER_H


#include "GPUImageColorMatrixFilter.h"

/**
 * Simple sepia tone filter
 */
class GPUImageSepiaFilter : public GPUImageColorMatrixFilter{
public:
    GPUImageSepiaFilter();
};


#endif //CGPUIMAGE_GPUIMAGESEPIAFILTER_H
