/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESELECTIVEFOCUSFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESELECTIVEFOCUSFILTER_H


#include "GPUImageTwoInputFilter.h"

class GPUImageSelectiveFocusFilter : public GPUImageTwoInputFilter{
public:
    GPUImageSelectiveFocusFilter();
    virtual ~GPUImageSelectiveFocusFilter();

    void setExcludeCircleRadius(float newValue);
    void setExcludeCirclePoint(float x, float y);
    void setExcludeBlurSize(float newValue);
    void setAspectRatio(float newValue);

    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);


protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    void updateAsepctRatio();

protected:
    /** The radius of the circular area being excluded from the blur
    */
    GLfloat m_fExcludeCircleRadius;

    /** The center of the circular area being excluded from the blur
    */
    GLfloat m_pExcludeCirclePoint[2];

    /** The size of the area between the blurred portion and the clear circle
    */
    GLfloat m_fExcludeBlurSize;

    /** The aspect ratio of the image, used to adjust the circularity of the in-focus region. By default, this matches the image aspect ratio, but you can override this value.
     */
    GLfloat m_fAspectRatio;

    GLint m_iExcludeCircleRadiusUniformLocation;
    GLint m_iExcludeCirclePointUniformLocation;
    GLint m_iExcludeBlurSizeUniformLocation;
    GLint m_iAspectRatioUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESELECTIVEFOCUSFILTER_H
