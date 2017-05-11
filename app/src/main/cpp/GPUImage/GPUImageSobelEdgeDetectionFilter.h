/**
 * Created by lvHiei on 17-4-17.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESOBELEDGEDETECTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESOBELEDGEDETECTIONFILTER_H


#include "GPUImageTwoPassFilter.h"

class GPUImageSobelEdgeDetectionFilter : public GPUImageTwoPassFilter{
public:
    GPUImageSobelEdgeDetectionFilter();
    GPUImageSobelEdgeDetectionFilter(const char* fragment);
    virtual ~GPUImageSobelEdgeDetectionFilter();

    void setTexelWidth(float texelWidth);
    void setTexelHeight(float texelHeight);
    void setEdgeStrength(float edgeStrength);

protected:
    virtual bool secondCreateProgramExtra();
    virtual bool secondBeforeDraw();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateTexelWidthHeight();

protected:
    // The texel width and height factors tweak the appearance of the edges.
    // By default, they match the inverse of the filter size in pixels
    GLfloat m_fTexelWidth;
    GLfloat m_fTexelHeight;

    // The filter strength property affects the dynamic range of the filter.
    // High values can make edges more visible, but can lead to saturation. Default of 1.0.
    GLfloat m_fEdgeStrength;


    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;
    GLint m_iEdgeStrengthUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESOBELEDGEDETECTIONFILTER_H
