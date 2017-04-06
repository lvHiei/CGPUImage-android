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
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();


protected:
    // The texel width and height determines how far out to sample from this texel.
    // By default, this is the normalized width of a pixel, but this can be overridden for different effects.
    float m_fTexelWidth;
    float m_fTexelHeight;

    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;

protected:
    char* m_pFragmentShader;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGE3X3TEXTURESAMPLINGFILTER_H
