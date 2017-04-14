/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEPOSITIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEPOSITIONFILTER_H


#include "GPUImageFilter.h"

class GPUImagePixellatePositionFilter : public GPUImageFilter{
public:
    GPUImagePixellatePositionFilter();
    virtual ~GPUImagePixellatePositionFilter();

    void setCenter(float x, float y);
    void setRadius(float radius);
    void setRadius(int percent);
    void setFractionalWidthOfAPixel(float fractional);
    void setAspectRatio(float aspectRatio);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateAspectRatio();


protected:
    // The fractional width of the image to use as a size for the pixels in the resulting image.
    // Values below one pixel width in the source image are ignored.
    GLfloat m_fFractionalWidthOfAPixel;

    // the radius (0.0 - 1.0) in which to pixelate,
    // default 1.0
    GLfloat m_fRadius;

    // the center point to start pixelation in texture coordinates, default 0.5, 0.5
    GLfloat m_pCenter[2];

    GLfloat m_fAspectRatio;

    GLint m_iFractionalUniformLocation;
    GLint m_iRadiusUniformLocation;
    GLint m_iAspectRatioUniformLocation;
    GLint m_iCenterUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPIXELLATEPOSITIONFILTER_H
