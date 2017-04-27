/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDSKETCHFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDSKETCHFILTER_H


#include "GPUImageThresholdEdgeDetectionFilter.h"

class GPUImageThresholdSketchFilter : public GPUImageThresholdEdgeDetectionFilter{
public:
    GPUImageThresholdSketchFilter();
    virtual ~GPUImageThresholdSketchFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDSKETCHFILTER_H
