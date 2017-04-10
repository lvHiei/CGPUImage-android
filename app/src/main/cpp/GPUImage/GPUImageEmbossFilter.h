/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEEMBOSSFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEEMBOSSFILTER_H


#include "GPUImage3x3ConvolutionFilter.h"

class GPUImageEmbossFilter : public GPUImage3x3ConvolutionFilter{
public:
    GPUImageEmbossFilter();
    virtual ~GPUImageEmbossFilter();

    void setIntensity(float intensity);
    void setIntensity(int percent);

protected:
    // The strength of the embossing, from  0.0 to 4.0, with 1.0 as the normal level
    GLfloat m_fIntensity;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEEMBOSSFILTER_H
