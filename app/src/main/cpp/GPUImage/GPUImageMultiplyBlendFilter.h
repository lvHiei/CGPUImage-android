/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMULTIPLYBLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMULTIPLYBLENDFILTER_H


#include "GPUImageImageFilter.h"

class GPUImageMultiplyBlendFilter : public GPUImageImageFilter{
public:
    GPUImageMultiplyBlendFilter();
    virtual ~GPUImageMultiplyBlendFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMULTIPLYBLENDFILTER_H
