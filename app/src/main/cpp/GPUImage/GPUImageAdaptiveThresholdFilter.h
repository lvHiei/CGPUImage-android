/**
 * Created by mj on 17-5-8.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H


#include "GPUImageFilterGroup.h"

class GPUImageAdaptiveThresholdFilter : public GPUImageFilterGroup{
public:
    GPUImageAdaptiveThresholdFilter();
    virtual ~GPUImageAdaptiveThresholdFilter();

    virtual bool createProgram();
    virtual bool release();


protected:
    /** A multiplier for the background averaging blur radius in pixels,
     *  with a default of 4
    */
    GLfloat m_fBlurRadiusInPixels;

protected:
    GPUImageFilter* m_pGreyScaleFilter;
    GPUImageFilter* m_pBoxBlurFilter;
    GPUImageFilter* m_pAdaptiveThresholdFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEADAPTIVETHRESHOLDFILTER_H
