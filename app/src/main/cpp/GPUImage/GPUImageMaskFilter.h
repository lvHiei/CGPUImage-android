/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMASKFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMASKFILTER_H


#include "GPUImageImageFilter.h"

class GPUImageMaskFilter : public GPUImageImageFilter{
public:
    GPUImageMaskFilter();
    virtual ~GPUImageMaskFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMASKFILTER_H
