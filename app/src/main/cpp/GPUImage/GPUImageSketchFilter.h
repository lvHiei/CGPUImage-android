/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESKETCHFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESKETCHFILTER_H


#include "GPUImageSobelEdgeDetectionFilter.h"

/** Converts video to look like a sketch.

 This is just the Sobel edge detection filter with the colors inverted.
 */
class GPUImageSketchFilter : public GPUImageSobelEdgeDetectionFilter{
public:
    GPUImageSketchFilter();
    virtual ~GPUImageSketchFilter();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESKETCHFILTER_H
