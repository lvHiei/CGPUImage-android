/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWTINTFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWTINTFILTER_H


#include "GPUImageFilter.h"

class GPUImageHighlightShadowTintFilter : public GPUImageFilter{
public:
    GPUImageHighlightShadowTintFilter();
    virtual ~GPUImageHighlightShadowTintFilter();

    void setShadowTintIntensity(float intensity);
    void setHighlightTintIntensity(float intensity);

    void setShadowTintIntensity(int percent);
    void setHighlightTintIntensity(int percent);

    void setShadowTintColorRed(float red, float green, float blue, float alpha);
    void setHighlightTintColorRed(float red, float green, float blue, float alpha);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    // The shadowTint and highlightTint colors specify what colors replace the dark and light areas of the image, respectively.
    // The defaults for shadows are black, highlighs white.
    GLfloat m_fShadowTintIntensity;
    GLfloat m_fHighlightTintIntensity;

    GLfloat m_pShadowTintColor[4];
    GLfloat m_pHighlightTintColor[4];

    GLint m_iShadowTintIntensityUniformLocation;
    GLint m_iHighlightTintIntensityUniformLocation;
    GLint m_iShadowTintColorUniformLocation;
    GLint m_iHighlightTintColorUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWTINTFILTER_H
