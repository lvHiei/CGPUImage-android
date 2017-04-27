/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDGEDETECTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDGEDETECTIONFILTER_H


#include "GPUImageSobelEdgeDetectionFilter.h"

class GPUImageThresholdEdgeDetectionFilter : public GPUImageSobelEdgeDetectionFilter{
public:
    GPUImageThresholdEdgeDetectionFilter();
    GPUImageThresholdEdgeDetectionFilter(const char* fragment);
    virtual ~GPUImageThresholdEdgeDetectionFilter();

public:
    void setThreshold(float threshold);
    void setThreshold(int percent);

protected:
    virtual bool secondCreateProgramExtra();
    virtual bool secondBeforeDraw();


protected:

    /** Any edge above this threshold will be black, and anything below white.
     *  Ranges from 0.0 to 1.0, with 0.8 as the default
    */
    GLfloat m_fThreshold;

    GLint m_iThresholdUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDGEDETECTIONFILTER_H


