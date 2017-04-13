/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEWHITEBALANCEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEWHITEBALANCEFILTER_H


#include "GPUImageFilter.h"

/**
 * Created by Alaric Cole
 * Allows adjustment of color temperature in terms of what an image was effectively shot in. This means higher Kelvin values will warm the image, while lower values will cool it.

 */

class GPUImageWhiteBalanceFilter : public GPUImageFilter{
public:
    GPUImageWhiteBalanceFilter();
    virtual ~GPUImageWhiteBalanceFilter();

    void setTemperature(float temperature);
    void setTint(float tint);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:

    //choose color temperature, in degrees Kelvin
    GLfloat m_fTemperature;

    //adjust tint to compensate
    GLfloat m_fTint;

    GLint m_iTemperatureUniformLocation;
    GLint m_iTintUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEWHITEBALANCEFILTER_H
