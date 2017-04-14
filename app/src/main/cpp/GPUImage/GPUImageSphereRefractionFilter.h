/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESPHEREREFRACTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESPHEREREFRACTIONFILTER_H


#include "GPUImageFilter.h"

class GPUImageSphereRefractionFilter : public GPUImageFilter{
public:
    GPUImageSphereRefractionFilter();
    virtual ~GPUImageSphereRefractionFilter();

    void setCenter(float x, float y);
    void setRadius(float radius);
    void setRefractiveIndex(float refractiveIndex);
    void setAspectRatio(float aspectRatio);

    void setRadius(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    void updateAspectRatio();

protected:

    /// The center about which to apply the distortion, with a default of (0.5, 0.5)
    GLfloat m_pCenter[2];

    /// The radius of the distortion, ranging from 0.0 to 1.0, with a default of 0.25
    GLfloat m_fRadius;

    /// The index of refraction for the sphere, with a default of 0.71
    GLfloat m_fRefractiveIndex;

    GLfloat m_fAspectRatio;


    GLint m_iCenterUniformLocation;
    GLint m_iRadiusUniformLocation;
    GLint m_iRefractiveIndexUniformLocation;
    GLint m_iAspectRatioUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESPHEREREFRACTIONFILTER_H
