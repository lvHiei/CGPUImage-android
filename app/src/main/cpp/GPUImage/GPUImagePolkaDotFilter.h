/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPOLKADOTFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPOLKADOTFILTER_H


#include "GPUImagePixellateFilter.h"

class GPUImagePolkaDotFilter : public GPUImagePixellateFilter{
public:
    GPUImagePolkaDotFilter();
    virtual ~GPUImagePolkaDotFilter();

    void setDotScaling(float dotScaling);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_fDotScaling;

    GLint m_iDotScalingUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPOLKADOTFILTER_H
