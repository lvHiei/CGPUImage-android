/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEFALSECOLORFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEFALSECOLORFILTER_H


#include "GPUImageFilter.h"

class GPUImageFalseColorFilter : public GPUImageFilter {
public:
    GPUImageFalseColorFilter();
    virtual ~GPUImageFalseColorFilter();

    void setFirstColorRed(float red, float green, float blue);
    void setSecondColorRed(float red, float green, float blue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // The first and second colors specify what colors replace the dark and light areas of the image, respectively.
    // The defaults are (0.0, 0.0, 0.5) amd (1.0, 0.0, 0.0).
    GLfloat m_pFirstColor[3];
    GLfloat m_pSecondColor[3];

    GLint m_iFirstColorUniformLocation;
    GLint m_iSecondColorUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEFALSECOLORFILTER_H
