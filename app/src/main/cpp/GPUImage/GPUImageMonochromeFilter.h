/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMONOCHROMEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMONOCHROMEFILTER_H


#include "GPUImageFilter.h"

class GPUImageMonochromeFilter : public GPUImageFilter {
public:
    GPUImageMonochromeFilter();
    virtual ~GPUImageMonochromeFilter();

    void setIntensity(float intensity);
    void setIntensity(int percent);

    void setColorRed(float red, float green, float blue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_fIntensity;

    GLfloat m_pColor[3];

    GLint m_iIntensityUniformLocation;
    GLint m_iColorUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMONOCHROMEFILTER_H
