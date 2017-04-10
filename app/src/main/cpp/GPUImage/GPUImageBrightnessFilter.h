/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEBRIGHTNESSFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEBRIGHTNESSFILTER_H


#include "GPUImageFilter.h"

class GPUImageBrightnessFilter : public GPUImageFilter {
public:
    GPUImageBrightnessFilter();
    virtual ~GPUImageBrightnessFilter();

    void setBrightness(int percent);
    void setBrightness(float brightness);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // Brightness ranges from -1.0 to 1.0, with 0.0 as the normal level
    GLfloat m_fBrightness;

    GLint m_iBrightUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEBRIGHTNESSFILTER_H
