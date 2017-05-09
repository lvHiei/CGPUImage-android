/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANSELECTIVEBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANSELECTIVEBLURFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageGaussianBlurFilter.h"
#include "GPUImageSelectiveFocusFilter.h"


/** A Gaussian blur that preserves focus within a circular region
 */

class GPUImageGaussianSelectiveBlurFilter : public GPUImageFilterGroup{
public:
    GPUImageGaussianSelectiveBlurFilter();
    virtual ~GPUImageGaussianSelectiveBlurFilter();

    void setExcludeCircleRadius(float newValue);
    void setExcludeCirclePoint(float x, float y);
    void setExcludeBlurSize(float newValue);
    void setBlurRadiusInPixels(float newValue);
    void setAspectRatio(float newValue);

    virtual bool release();
    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);

protected:
    GPUImageGaussianBlurFilter* m_pBlurFilter;
    GPUImageSelectiveFocusFilter* m_pSelectiveFocusFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANSELECTIVEBLURFILTER_H
