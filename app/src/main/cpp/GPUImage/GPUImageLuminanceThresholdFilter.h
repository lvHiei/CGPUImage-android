/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELUMINANCETHRESHOLDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELUMINANCETHRESHOLDFILTER_H


#include "GPUImageFilter.h"

/** Pixels with a luminance above the threshold will appear white, and those below will be black
 */
class GPUImageLuminanceThresholdFilter : public GPUImageFilter{
public:
    GPUImageLuminanceThresholdFilter();
    virtual ~GPUImageLuminanceThresholdFilter();

    void setThreshold(float threshold);
    void setThreshold(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:

    /** Anything above this luminance will be white, and anything below black.
     *  Ranges from 0.0 to 1.0, with 0.5 as the default
     */
    GLfloat m_fThreshold;

    GLint m_iThresholdUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELUMINANCETHRESHOLDFILTER_H
