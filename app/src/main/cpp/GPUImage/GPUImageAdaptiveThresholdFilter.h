/**
 * Created by lvHiei on 17-5-8.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H

#include "GPUImageGreyscaleFilter.h"
#include "GPUImageBoxBlurFilter.h"
#include "GPUImageTwoInputFilter.h"
#include "GPUImageFilterGroup.h"

class GPUImageAdaptiveThresholdFilter : public GPUImageFilterGroup{
public:
    GPUImageAdaptiveThresholdFilter();
    virtual ~GPUImageAdaptiveThresholdFilter();

    virtual bool createProgram();
    virtual bool release();

    void setBlurRadiusInPixels(float blurRadiusInPixels);

protected:
    /** A multiplier for the background averaging blur radius in pixels,
     *  with a default of 4
    */
    GLfloat m_fBlurRadiusInPixels;

protected:
    GPUImageGreyscaleFilter* m_pGreyScaleFilter;
    GPUImageBoxBlurFilter* m_pBoxBlurFilter;
    GPUImageTwoInputFilter* m_pAdaptiveThresholdFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H
