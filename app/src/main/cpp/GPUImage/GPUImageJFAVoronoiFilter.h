/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEJFAVORONOIFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEJFAVORONOIFILTER_H


#include "GPUImageFilter.h"

class GPUImageJFAVoronoiFilter : public GPUImageFilter{
public:
    GPUImageJFAVoronoiFilter();
    virtual ~GPUImageJFAVoronoiFilter();


public:
    void setSizeInPixels(int w, int h);
    void setNumPasses(int numpasses);

public:
    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight);

    virtual bool release();

protected:
    virtual bool createProgramExtra();

protected:
    bool createFrameBuffer();

protected:
    GLfloat m_pSizeInPixels[2];
    GLint m_iNumPasses;

    GLint m_iSampleStepUniformLocation;
    GLint m_iSizeUniformLocation;

protected:
    GLuint m_uFrameBufferId;
    GLuint m_uFrameBufferTextureId;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEJFAVORONOIFILTER_H
