/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESMOOTHTOONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESMOOTHTOONFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageGaussianBlurFilter.h"
#include "GPUImageToonFilter.h"

/** This uses a similar process as the GPUImageToonFilter, only it precedes the toon effect with a Gaussian blur to smooth out noise.
 */

class GPUImageSmoothToonFilter : public GPUImageFilterGroup{
public:
    GPUImageSmoothToonFilter();
    virtual ~GPUImageSmoothToonFilter();


    void setBlurRadiusInPixels(float newValue);
    void setTexelWidth(float newValue);
    void setTexelHeight(float newValue);
    void setThreshold(float newValue);
    void setQuantizationLevels(float newValue);

    virtual bool release();

protected:
    GPUImageGaussianBlurFilter* m_pBlurFilter;
    GPUImageToonFilter* m_pToonFilter;


protected:

    /// The image width and height factors tweak the appearance of the edges. By default, they match the filter size in pixels
    GLfloat m_fTexelWidth;

    /// The image width and height factors tweak the appearance of the edges. By default, they match the filter size in pixels
    GLfloat m_fTexelHeight;

    /// The radius of the underlying Gaussian blur. The default is 2.0.
    GLfloat m_fBlurRadiusInPixels;

    /// The threshold at which to apply the edges, default of 0.2
    GLfloat m_fThreshold;

    /// The levels of quantization for the posterization of colors within the scene, with a default of 10.0
    GLfloat m_fQuantizationLevels;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESMOOTHTOONFILTER_H
