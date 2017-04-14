/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESHARPENFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESHARPENFILTER_H


#include "GPUImageFilter.h"

class GPUImageSharpenFilter : public GPUImageFilter{
public:
    GPUImageSharpenFilter();
    virtual ~GPUImageSharpenFilter();

    void setImageWidthFactor(float width);
    void setImageHeightFactor(float height);

    void setSharpness(float sharpness);
    void setSharpness(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateTexelWidthHeight();

protected:
    GLfloat m_fImageWidthFactor;
    GLfloat m_fImageHeightFactor;

    // Sharpness ranges from -4.0 to 4.0,
    // with 0.0 as the normal level
    GLfloat m_fSharpness;

    GLint m_iImageWidthFactorUniformLocation;
    GLint m_iImageHeightFactorUniformLocation;
    GLint m_iSharpnessUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESHARPENFILTER_H
