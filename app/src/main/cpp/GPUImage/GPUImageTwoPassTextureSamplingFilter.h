/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_ANDROID_GPUIMAGETWOPASSTEXTURESAMPLINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETWOPASSTEXTURESAMPLINGFILTER_H


#include "GPUImageTwoPassFilter.h"

class GPUImageTwoPassTextureSamplingFilter : public GPUImageTwoPassFilter {
public:
    GPUImageTwoPassTextureSamplingFilter(const char* firstVetex, const char* firstFragment, const char* secondVetex, const char* secondFragment);
    virtual ~GPUImageTwoPassTextureSamplingFilter();

public:
    void setVerticalTexelSpacing(float spacing);
    void setHorizontalTexelSpacing(float spacing);

    void setVerticalPassTexelWidthOffset(float offset);
    void setVerticalPassTexelHeightOffset(float offset);
    void setHorizontalPassTexelWidthOffset(float offset);
    void setHorizontalPassTexelHeightOffset(float offset);

protected:
    virtual bool firstCreateProgramExtra();
    virtual bool secondCreateProgramExtra();
    virtual bool firstBeforeDraw();
    virtual bool secondBeforeDraw();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateTexelSize();

protected:

    GLfloat m_fVerticalPassTexelWidthOffset;
    GLfloat m_fVerticalPassTexelHeightOffset;
    GLfloat m_fHorizontalPassTexelWidthOffset;
    GLfloat m_fHorizontalPassTexelHeightOffset;

    // This sets the spacing between texels (in pixels) when sampling for the first.
    // By default, this is 1.0
    GLfloat m_f_verticalTexelSpacing;
    GLfloat m_f_horizontalTexelSpacing;

    GLint m_iVerticalPassTexelWidthOffsetUniform;
    GLint m_iVerticalPassTexelHeightOffsetUniform;
    GLint m_iHorizontalPassTexelWidthOffsetUniform;
    GLint m_iHorizontalPassTexelHeightOffsetUniform;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETWOPASSTEXTURESAMPLINGFILTER_H
