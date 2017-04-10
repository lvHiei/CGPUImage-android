/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEALPHABLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEALPHABLENDFILTER_H


#include "GPUImageTwoInputFilter.h"

class GPUImageAlphaBlendFilter : public GPUImageTwoInputFilter {
public:
    GPUImageAlphaBlendFilter();
    virtual ~GPUImageAlphaBlendFilter();

    void setMix(int percent);
    void setMix(float mix);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // Mix ranges from 0.0 (only image 1) to 1.0 (only image 2), with 1.0 as the normal level
    GLfloat m_fMix;

    GLint m_iMixUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEALPHABLENDFILTER_H
