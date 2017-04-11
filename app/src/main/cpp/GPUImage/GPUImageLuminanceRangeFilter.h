/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELUMINANCERANGEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELUMINANCERANGEFILTER_H


#include "GPUImageFilter.h"

class GPUImageLuminanceRangeFilter : public GPUImageFilter{
public:
    GPUImageLuminanceRangeFilter();
    virtual ~GPUImageLuminanceRangeFilter();

    void setRangeReductionFactor(float rangeReductionFactor);
    void setRangeReductionFactor(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** The degree to reduce the luminance range, from 0.0 to 1.0. Default is 0.6.
     */
    GLfloat m_fRangeReductionFactor;

    GLint m_iRangeReductionFactorUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELUMINANCERANGEFILTER_H
