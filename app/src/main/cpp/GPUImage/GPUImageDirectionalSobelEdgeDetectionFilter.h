/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALSOBELEDGEDETECTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALSOBELEDGEDETECTIONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

class GPUImageDirectionalSobelEdgeDetectionFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageDirectionalSobelEdgeDetectionFilter();
    virtual ~GPUImageDirectionalSobelEdgeDetectionFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEDIRECTIONALSOBELEDGEDETECTIONFILTER_H
