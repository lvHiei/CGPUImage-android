/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPERLINNOISEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPERLINNOISEFILTER_H


#include "GPUImageFilter.h"

class GPUImagePerlinNoiseFilter : public GPUImageFilter{
public:
    GPUImagePerlinNoiseFilter();
    virtual ~GPUImagePerlinNoiseFilter();

    void setColorStart(float red, float green, float blue, float alpha);
    void setColorFinish(float red, float green, float blue, float alpha);

    void setScale(float scale);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_pColorStart[4];
    GLfloat m_pColorFinish[4];

    GLfloat m_fScale;

    GLint m_iColorStartUniformLocation;
    GLint m_iColorFinishUniformLocation;
    GLint m_iScaleUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPERLINNOISEFILTER_H
