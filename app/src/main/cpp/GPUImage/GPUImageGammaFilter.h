/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEGAMMAFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEGAMMAFILTER_H


#include "GPUImageFilter.h"

class GPUImageGammaFilter : public GPUImageFilter {
public:
    GPUImageGammaFilter();
    virtual ~GPUImageGammaFilter();

    void setGamma(int percent);

public:
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    GLint m_iGammaLocation;

    // Gamma ranges from 0.0 to 3.0, with 1.0 as the normal level
    float m_fGamma;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEGAMMAFILTER_H
