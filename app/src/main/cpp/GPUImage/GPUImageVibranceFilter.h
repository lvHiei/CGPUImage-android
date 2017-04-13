/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEVIBRANCEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEVIBRANCEFILTER_H


#include "GPUImageFilter.h"

class GPUImageVibranceFilter : public GPUImageFilter{
public:
    GPUImageVibranceFilter();
    virtual ~GPUImageVibranceFilter();

    void setVibrance(float vibrance);
    void setVibrance(int  percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    // Modifies the saturation of desaturated colors, leaving saturated colors unmodified.
    // Value -1 to 1 (-1 is minimum vibrance, 0 is no change, and 1 is maximum vibrance)
    GLfloat m_fVibrance;

    GLint m_iVibranceUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEVIBRANCEFILTER_H
