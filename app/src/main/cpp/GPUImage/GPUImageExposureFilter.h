/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEEXPOSUREFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEEXPOSUREFILTER_H


#include "GPUImageFilter.h"

class GPUImageExposureFilter : public GPUImageFilter{
public:
    GPUImageExposureFilter();
    virtual ~GPUImageExposureFilter();

    void setExposure(float exposure);
    void setExposure(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    // Exposure ranges from -10.0 to 10.0, with 0.0 as the normal level
    GLfloat m_fExposure;

    GLint m_iExposureUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEEXPOSUREFILTER_H
