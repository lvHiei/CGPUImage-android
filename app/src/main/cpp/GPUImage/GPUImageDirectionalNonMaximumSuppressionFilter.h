/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALNONMAXIMUMSUPPRESSIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALNONMAXIMUMSUPPRESSIONFILTER_H


#include "GPUImageFilter.h"

class GPUImageDirectionalNonMaximumSuppressionFilter : public GPUImageFilter {
public:
    GPUImageDirectionalNonMaximumSuppressionFilter();
    virtual ~GPUImageDirectionalNonMaximumSuppressionFilter();

    void setTexelWidth(float width);
    void setTexelHeight(float height);

    void setUpperThreshold(float upperThreshold);
    void setLowerThreshold(float lowerThreshold);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

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

    // These thresholds set cutoffs for the intensities that definitely get registered (upper threshold) and those that definitely don't (lower threshold)
    GLfloat m_fUpperThreshold;
    GLfloat m_fLowerThreshold;

    GLint m_iUpperThresholdUniformLocation;
    GLint m_iLowerThresholdUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALNONMAXIMUMSUPPRESSIONFILTER_H
