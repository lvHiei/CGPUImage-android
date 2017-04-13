/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESTRETCHDISTORTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESTRETCHDISTORTIONFILTER_H


#include "GPUImageFilter.h"

/** Creates a stretch distortion of the image
 */
class GPUImageStretchDistortionFilter : public GPUImageFilter{
public:
    GPUImageStretchDistortionFilter();
    virtual ~GPUImageStretchDistortionFilter();

    void setCenter(float x, float y);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** The center about which to apply the distortion, with a default of (0.5, 0.5)
    */
    GLfloat m_pCenter[2];

    GLint m_iCenterUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESTRETCHDISTORTIONFILTER_H
