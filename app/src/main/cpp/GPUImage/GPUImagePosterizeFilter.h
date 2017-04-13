/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPOSTERIZEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPOSTERIZEFILTER_H


#include "GPUImageFilter.h"

/** This reduces the color dynamic range into the number of steps specified,
 *  leading to a cartoon-like simple shading of the image.
 */
class GPUImagePosterizeFilter : public GPUImageFilter{
public:
    GPUImagePosterizeFilter();
    virtual ~GPUImagePosterizeFilter();

    void setColorLevels(int colorLevels);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** The number of color levels to reduce the image space to.
     *  This ranges from 1 to 256, with a default of 10.
     */
    GLuint m_iColorLevels;

    GLint m_iColorLevelsUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPOSTERIZEFILTER_H
