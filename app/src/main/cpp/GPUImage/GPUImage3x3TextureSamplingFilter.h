/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGE3X3TEXTURESAMPLINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGE3X3TEXTURESAMPLINGFILTER_H


#include "GPUImageFilter.h"

class GPUImage3x3TextureSamplingFilter : public GPUImageFilter{
public:
    GPUImage3x3TextureSamplingFilter(const char* fragment);
    virtual ~GPUImage3x3TextureSamplingFilter();

    virtual bool release();

public:
    void setTexelWidth(float texelWidth);
    void setTexelHeight(float texelHeight);



public:
    virtual bool createProgramExtra();

protected:
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateTexelWidthHeight();

protected:
    // The texel width and height determines how far out to sample from this texel.
    // By default, this is the normalized width of a pixel, but this can be overridden for different effects.
    GLfloat m_fTexelWidth;
    GLfloat m_fTexelHeight;

    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGE3X3TEXTURESAMPLINGFILTER_H
