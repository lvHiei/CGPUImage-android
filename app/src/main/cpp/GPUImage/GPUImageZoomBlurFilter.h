/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEZOOMBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEZOOMBLURFILTER_H


#include "GPUImageFilter.h"

class GPUImageZoomBlurFilter : public GPUImageFilter{
public:
    GPUImageZoomBlurFilter();
    virtual ~GPUImageZoomBlurFilter();

    void setBlurSize(float blursize);
    void setBlurCenter(float x, float y);


protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** A multiplier for the blur size, ranging from 0.0 on up, with a default of 1.0
     */
    GLfloat m_fBlurSize;

    /** The normalized center of the blur. (0.5, 0.5) by default
     */
    GLfloat m_pBlurCenter[2];


    GLint m_iBlurSizeUniformLocation;
    GLint m_iBlurCenterUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEZOOMBLURFILTER_H
