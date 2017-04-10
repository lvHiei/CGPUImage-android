/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWFILTER_H


#include "GPUImageFilter.h"

class GPUImageHighlightShadowFilter : public GPUImageFilter{
public:
    GPUImageHighlightShadowFilter();
    virtual ~GPUImageHighlightShadowFilter();

    void setShadows(float shadows);
    void setHighlights(float highlights);

    void setShadows(int percent);
    void setHighlights(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    /**
     * 0 - 1, increase to lighten shadows.
     * @default 0
     */
    GLfloat m_fShadows;

    /**
     * 0 - 1, decrease to darken highlights.
     * @default 1
     */
    GLfloat m_fHighlights;

    GLint m_iShadowsUniformLocation;
    GLint m_iHighlightsUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEHIGHLIGHTSHADOWFILTER_H
