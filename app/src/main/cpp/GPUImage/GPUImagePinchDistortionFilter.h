/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPINCHDISTORTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPINCHDISTORTIONFILTER_H


#include "GPUImageFilter.h"

/** Creates a pinch distortion of the image
 */
class GPUImagePinchDistortionFilter : public GPUImageFilter{
public:
    GPUImagePinchDistortionFilter();
    virtual ~GPUImagePinchDistortionFilter();

    void setCenter(float x, float y);
    void setRadius(float radius);
    void setScale(float scale);

    void setRadius(int percent);
    void setScale(int percent);

    void setAspectRatio(float aspectRatio);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** The center about which to apply the distortion, with a default of (0.5, 0.5)
     */
    GLfloat m_pCenter[2];

    /** The radius of the distortion, ranging from 0.0 to 2.0, with a default of 1.0
     */
    GLfloat m_fRadius;

    /** The amount of distortion to apply, from -2.0 to 2.0, with a default of 0.5
     */
    GLfloat m_fScale;

    GLfloat m_fAspectRatio;

    GLint m_iCenterUnifornLocation;
    GLint m_iRadiusUnifornLocation;
    GLint m_iScaleUnifornLocation;
    GLint m_iAspectUnifornLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPINCHDISTORTIONFILTER_H
