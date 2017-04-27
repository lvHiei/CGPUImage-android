/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPREWITTEDGEDETECTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPREWITTEDGEDETECTIONFILTER_H


#include "GPUImageSobelEdgeDetectionFilter.h"

class GPUImagePrewittEdgeDetectionFilter : public GPUImageSobelEdgeDetectionFilter {
public:
    GPUImagePrewittEdgeDetectionFilter();
    virtual ~GPUImagePrewittEdgeDetectionFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPREWITTEDGEDETECTIONFILTER_H
