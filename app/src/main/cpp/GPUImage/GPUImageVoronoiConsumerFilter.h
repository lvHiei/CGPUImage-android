/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEVORONOICONSUMERFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEVORONOICONSUMERFILTER_H


#include "GPUImageImageFilter.h"

class GPUImageVoronoiConsumerFilter : public GPUImageImageFilter{
public:
    GPUImageVoronoiConsumerFilter();
    virtual ~GPUImageVoronoiConsumerFilter();

    void setSizeInPixels(int w, int h);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

    virtual bool loadImage();

protected:
    GLint m_pSizeInPixels[2];

    GLint m_iSizeInPixelsUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEVORONOICONSUMERFILTER_H
