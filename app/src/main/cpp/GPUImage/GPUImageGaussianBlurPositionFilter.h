/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURPOSITIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURPOSITIONFILTER_H


#include "GPUImageTwoPassTextureSamplingFilter.h"

/** A more generalized 9x9 Gaussian blur filter
 */
class GPUImageGaussianBlurPositionFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageGaussianBlurPositionFilter();
    virtual ~GPUImageGaussianBlurPositionFilter();

public:
    void setAspectRatio(float aspectRatio);

    void setBlurSize(float blurSize);
    void setBlurCenter(float x, float y);
    void setBlurRadius(float radius);

    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateAspectRatio();

    virtual bool secondCreateProgramExtra();
    virtual bool secondBeforeDraw();

protected:

    /** A multiplier for the blur size, ranging from 0.0 on up,
     *  with a default of 1.0
    */
    GLfloat m_fBlurSize;

    /** Center for the blur,
     *  defaults to 0.5, 0.5
     */
    GLfloat m_pBlurCenter[2];

    /** Radius for the blur,
     *  defaults to 1.0
     */
    GLfloat m_fBlurRadius;

    GLfloat m_fAspectRatio;

    GLint m_iBlurSizeUniformLocation;
    GLint m_iBlurCenterUniformLocation;
    GLint m_iBlurRadiusUniformLocation;
    GLint m_iAspectRatioUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURPOSITIONFILTER_H
