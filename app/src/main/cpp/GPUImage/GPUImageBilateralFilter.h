/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEBILATERALFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEBILATERALFILTER_H


#include "GPUImageGaussianBlurFilter.h"

class GPUImageBilateralFilter : public GPUImageGaussianBlurFilter{
public:
    GPUImageBilateralFilter();
    virtual ~GPUImageBilateralFilter();

public:
    void setDistanceNormalizationFactor(float distanceNormalizationFactor);

protected:
    virtual bool firstCreateProgramExtra();
    virtual bool secondCreateProgramExtra();
    virtual bool firstBeforeDraw();
    virtual bool secondBeforeDraw();

protected:
    GLfloat m_fDistanceNormalizationFactor;

    GLint m_iFirstDistanceNormalizationFactorUniformLocation;
    GLint m_iSecondDistanceNormalizationFactorUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEBILATERALFILTER_H
