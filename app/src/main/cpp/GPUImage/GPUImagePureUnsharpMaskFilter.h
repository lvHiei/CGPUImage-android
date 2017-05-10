/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPUREUNSHARPMASKFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPUREUNSHARPMASKFILTER_H


#include "GPUImageTwoInputFilter.h"

class GPUImagePureUnsharpMaskFilter : public GPUImageTwoInputFilter{
public:
    GPUImagePureUnsharpMaskFilter();
    virtual ~GPUImagePureUnsharpMaskFilter();

    void setIntensity(float intensity);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:
    GLfloat m_fIntensity;

    GLint m_iIntensityUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPUREUNSHARPMASKFILTER_H
