/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEVIGNETTEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEVIGNETTEFILTER_H


#include "GPUImageFilter.h"


/** Performs a vignetting effect, fading out the image at the edges
 */
class GPUImageVignetteFilter : public GPUImageFilter{
public:
    GPUImageVignetteFilter();
    virtual ~GPUImageVignetteFilter();

    void setVignetteCenter(float x, float y);
    void setVignetteColor(float red, float green, float blue);
    void setVignetteStart(float start);
    void setVignetteEnd(float end);


protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    // the center for the vignette in tex coords (defaults to 0.5, 0.5)
    GLfloat m_pVignetteCenter[2];

    // The color to use for the Vignette (defaults to black)
    GLfloat m_pVignetteColor[3];

    // The normalized distance from the center where the vignette effect starts. Default of 0.5.
    GLfloat m_fVignetteStart;

    // The normalized distance from the center where the vignette effect ends. Default of 0.75.
    GLfloat m_fVignetteEnd;

    GLint m_iVignetteCenterUniformLocation;
    GLint m_iVignetteColorUniformLocation;
    GLint m_iVignetteStartUniformLocation;
    GLint m_iVignetteEndUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEVIGNETTEFILTER_H
