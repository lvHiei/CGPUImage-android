/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEFILTER_H


#include "GPUImageFilter.h"

class GPUImagePixellateFilter : public GPUImageFilter{
public:
    GPUImagePixellateFilter();
    virtual ~GPUImagePixellateFilter();

    void setAspectRatio(float aspectRatio);
    void setFractionalWidthOfAPixel(float fraction);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // The fractional width of the image to use as a size for the pixels in the resulting image.
    // Values below one pixel width in the source image are ignored.
    GLfloat m_fFractionalWidthOfAPixel;

    GLfloat m_fAsepctRatio;

    GLint m_iFragUniformLocation;
    GLint m_iAsepectRatioUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEFILTER_H
