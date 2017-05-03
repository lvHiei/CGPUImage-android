/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELANCZOSRESAMPLINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELANCZOSRESAMPLINGFILTER_H


#include "GPUImageTwoPassTextureSamplingFilter.h"

class GPUImageLanczosResamplingFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageLanczosResamplingFilter();
    virtual ~GPUImageLanczosResamplingFilter();

    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

    void setImageSize(float width, float height);

protected:
    void updateTexelSize();

protected:
    GLint m_pOriginalImageSize[2];
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELANCZOSRESAMPLINGFILTER_H
