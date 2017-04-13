/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPOLARPIXELLATEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPOLARPIXELLATEFILTER_H


#include "GPUImageFilter.h"

class GPUImagePolarPixellateFilter : public GPUImageFilter{
public:
    GPUImagePolarPixellateFilter();
    virtual ~GPUImagePolarPixellateFilter();

    void setPixelSize(float x, float y);
    void setCenter(float x, float y);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_pCenter[2];
    GLfloat m_pPixelSzie[2];

    GLint m_iCenterUniformLocation;
    GLint m_iPixelSzieUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPOLARPIXELLATEFILTER_H
