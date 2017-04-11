/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMOTIONBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMOTIONBLURFILTER_H


#include "GPUImageFilter.h"

class GPUImageMotionBlurFilter : public GPUImageFilter{
public:
    GPUImageMotionBlurFilter();
    virtual ~GPUImageMotionBlurFilter();

    void setBlurSize(float blurSize);
    void setBlurAngle(float blurAngle);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    void resetTexelStep();

protected:

    /** A multiplier for the blur size, ranging from 0.0 on up, with a default of 1.0
    */
    GLfloat m_fBlurSize;

    /** The angular direction of the blur, in degrees. 0 degrees by default
     */
    GLfloat m_fBlurAngle;

    GLint m_iTexelStepUniformLocation;

    GLfloat m_pTexelStep[2];
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMOTIONBLURFILTER_H
