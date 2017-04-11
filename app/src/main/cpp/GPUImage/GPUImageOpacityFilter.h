/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEOPACITYFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEOPACITYFILTER_H


#include "GPUImageFilter.h"

class GPUImageOpacityFilter : public GPUImageFilter{
public:
    GPUImageOpacityFilter();
    virtual ~GPUImageOpacityFilter();

    void setOpacity(float opacity);
    void setOpacity(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // Opacity ranges from 0.0 to 1.0, with 1.0 as the normal setting
    GLfloat m_fOpacity;

    GLint m_iOpacityUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEOPACITYFILTER_H
