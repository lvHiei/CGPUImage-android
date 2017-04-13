/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGERGBFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGERGBFILTER_H


#include "GPUImageFilter.h"

class GPUImageRGBFilter : public GPUImageFilter{
public:
    GPUImageRGBFilter();
    virtual ~GPUImageRGBFilter();

    void setRed(float red);
    void setGreen(float green);
    void setBlue(float blue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_fRed;
    GLfloat m_fGreen;
    GLfloat m_fBlue;

    GLint m_iRedUniformLocation;
    GLint m_iGreenUniformLocation;
    GLint m_iBlueUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGERGBFILTER_H
