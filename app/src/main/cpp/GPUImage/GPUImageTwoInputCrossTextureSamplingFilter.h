/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTCROSSTEXTURESAMPLINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTCROSSTEXTURESAMPLINGFILTER_H


#include "GPUImageTwoInputFilter.h"

class GPUImageTwoInputCrossTextureSamplingFilter : public GPUImageTwoInputFilter{
public:
    GPUImageTwoInputCrossTextureSamplingFilter(const char* fragment);
    GPUImageTwoInputCrossTextureSamplingFilter(const char* vertex, const char* fragment);
    virtual ~GPUImageTwoInputCrossTextureSamplingFilter();

    void setTexelWidth(float texelWidth);
    void setTexelHeight(float texelHeight);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateTexelWidthHeight();
    void intenalInit();

protected:
    GLfloat m_fTexelWidth;
    GLfloat m_fTexelHeight;

    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTCROSSTEXTURESAMPLINGFILTER_H
