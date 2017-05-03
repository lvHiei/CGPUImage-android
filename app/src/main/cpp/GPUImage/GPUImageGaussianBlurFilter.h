/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURFILTER_H


#include "GPUImageTwoPassTextureSamplingFilter.h"

class GPUImageGaussianBlurFilter : public GPUImageTwoPassTextureSamplingFilter{
public:
    GPUImageGaussianBlurFilter();
    GPUImageGaussianBlurFilter(float blurRadiusInPixels);
    virtual ~GPUImageGaussianBlurFilter();

public:
    void setTexelSpacingMultiplier(float mutiplier);
    void setBlurRadiusAsFractionOfImageWidth(float blurRadiusAsFractionOfImageWidth);
    void setBlurRadiusAsFractionOfImageHeight(float blurRadiusAsFractionOfImageHeight);

protected:
    void genVertexShaderForStandardBlurOfRadius(int blurRadius, float sigma);
    void genFragmentShaderForStandardBlurOfRadius(int blurRadius, float sigma);
    void genVertexShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);
    void genFragmentShaderForOptimizedBlurOfRadius(int blurRadius, float sigma);

    void updateBlurRadiusInPixels();

    void initWithBlurSigma(int blurRadius, float sigma);

    void resetFirstVertexShader(const char* shader);
    void resetFirstFragmentShader(const char* shader);
    void resetSecondVertexShader(const char* shader);
    void resetSecondFragmentShader(const char* shader);

public:
    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

protected:
    GLboolean m_bShouldResizeBlurRadiusWidthImageWidth;

    /** A multiplier for the spacing between texels, ranging from 0.0 on up, with a default of 1.0.
     *  Adjusting this may slightly increase the blur strength, but will introduce artifacts in the result.
     */
    GLfloat m_fTexelSpacingMutiplier;

    /** A radius in pixels to use for the blur, with a default of 2.0.
     *  This adjusts the sigma variable in the Gaussian distribution function.
     */
    GLfloat m_fBlurRadiusInPexels;

    /** Setting these properties will allow the blur radius to scale with the size of the image.
     *  These properties are mutually exclusive; setting either will set the other to 0.
     */
    GLfloat m_fBlurRadiusAsFractionOfImageWidth;
    GLfloat m_fBlurRadiusAsFractionOfImageHeight;

    /// The number of times to sequentially blur the incoming image.
    //  The more passes, the slower the filter.
    GLint m_iBlurPasses;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEGAUSSIANBLURFILTER_H
