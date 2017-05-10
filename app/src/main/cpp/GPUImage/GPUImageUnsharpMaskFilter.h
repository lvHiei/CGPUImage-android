/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEUNSHARPMASKFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEUNSHARPMASKFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImagePureUnsharpMaskFilter.h"
#include "GPUImageGaussianBlurFilter.h"

class GPUImageUnsharpMaskFilter : public GPUImageFilterGroup{
public:
    GPUImageUnsharpMaskFilter();
    virtual ~GPUImageUnsharpMaskFilter();

    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);

    virtual bool release();


protected:
    GPUImageGaussianBlurFilter* m_pBlurFilter;
    GPUImagePureUnsharpMaskFilter* m_pUnsharpFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEUNSHARPMASKFILTER_H
