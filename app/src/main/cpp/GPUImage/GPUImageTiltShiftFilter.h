/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETILTSHIFTFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETILTSHIFTFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageGaussianBlurFilter.h"
#include "GPUImagePureTiltShiftFilter.h"

class GPUImageTiltShiftFilter : public GPUImageFilterGroup{
public:
    GPUImageTiltShiftFilter();
    virtual ~GPUImageTiltShiftFilter();

    virtual bool release();

    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);

    void setTopFocusLevel(float newValue);
    void setBottomFocusLevel(float newValue);
    void setFocusFallOffRate(float newValue);

    void setBlurRadiusInPixels(float newValue);

protected:
    GPUImageGaussianBlurFilter* m_pBlurFilter;
    GPUImagePureTiltShiftFilter* m_pTiltShiftFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETILTSHIFTFILTER_H
