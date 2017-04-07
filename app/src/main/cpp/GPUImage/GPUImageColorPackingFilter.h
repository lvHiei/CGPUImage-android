/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECOLORPACKINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECOLORPACKINGFILTER_H


#include "GPUImageFilter.h"

class GPUImageColorPackingFilter : public GPUImageFilter{
public:
    GPUImageColorPackingFilter();
    virtual ~GPUImageColorPackingFilter();

    void setTexelWidth(float width);
    void setTexelHeight(float height);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_fTexelWidth;
    GLfloat m_fTexelHeight;

    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECOLORPACKINGFILTER_H
