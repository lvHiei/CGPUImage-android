/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECROSSHATCHFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECROSSHATCHFILTER_H


#include "GPUImageFilter.h"

class GPUImageCrosshatchFilter : public GPUImageFilter{
public:
    GPUImageCrosshatchFilter();
    virtual ~GPUImageCrosshatchFilter();

    void setCrossHatchSpacing(float crossHatchSpacing);
    void setLineWidth(float lineWidth);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    // The fractional width of the image to use as the spacing for the crosshatch. The default is 0.03.
    GLfloat m_fCrossHatchSpacing;

    // A relative width for the crosshatch lines. The default is 0.003.
    GLfloat m_fLineWidth;

    GLint m_iCrossHatchSpacingUniformLocation;
    GLint m_iLineWidthUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECROSSHATCHFILTER_H
