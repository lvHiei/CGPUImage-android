/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEHUEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEHUEFILTER_H


#include "GPUImageFilter.h"

class GPUImageHueFilter : public GPUImageFilter{
public:
    GPUImageHueFilter();
    virtual ~GPUImageHueFilter();

    void setHue(float hue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:
    GLfloat m_fHue;

    GLint m_iHueUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEHUEFILTER_H
