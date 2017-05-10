/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEIOSBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEIOSBLURFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageSaturationFilter.h"
#include "GPUImageGaussianBlurFilter.h"
#include "GPUImageLuminanceRangeFilter.h"

class GPUImageiOSBlurFilter : public GPUImageFilterGroup{
public:
    GPUImageiOSBlurFilter();
    virtual ~GPUImageiOSBlurFilter();

    void setBlurRadiusInPixels(float newValue);
    void setSaturation(float newValue);
    void setDownsampling(float newValue);
    void setRangeReductionFactor(float newValue);

    virtual bool release();


protected:
    GPUImageSaturationFilter* m_pSaturationFilter;
    GPUImageGaussianBlurFilter* m_pBlurFilter;
    GPUImageLuminanceRangeFilter* m_pLuminanceRangeFilter;


protected:
    /** A radius in pixels to use for the blur, with a default of 12.0. This adjusts the sigma variable in the Gaussian distribution function.
    */
    GLfloat m_fBlurRadiusInPixels;

    /** Saturation ranges from 0.0 (fully desaturated) to 2.0 (max saturation), with 0.8 as the normal level
    */
    GLfloat m_fSaturation;

    /** The degree to which to downsample, then upsample the incoming image to minimize computations within the Gaussian blur, default of 4.0
    */
    GLfloat m_fDownsampling;

    /** The degree to reduce the luminance range, from 0.0 to 1.0. Default is 0.6.
    */
    GLfloat m_fRangeReductionFactor;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEIOSBLURFILTER_H
