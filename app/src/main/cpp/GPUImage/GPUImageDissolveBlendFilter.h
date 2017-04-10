/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEDISSOLVEBLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEDISSOLVEBLENDFILTER_H


#include "GPUImageImageFilter.h"

class GPUImageDissolveBlendFilter : public GPUImageImageFilter{
public:
    GPUImageDissolveBlendFilter();
    virtual ~GPUImageDissolveBlendFilter();

    void setMix(int percent);
    void setMix(float mix);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    virtual bool loadImage();

protected:
    // Mix ranges from 0.0 (only image 1) to 1.0 (only image 2), with 0.5 (half of either) as the normal level
    GLfloat m_fMix;

    GLint m_iMixUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEDISSOLVEBLENDFILTER_H
