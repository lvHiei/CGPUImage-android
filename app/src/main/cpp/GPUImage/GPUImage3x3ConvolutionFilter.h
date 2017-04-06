/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGE3X3CONVOLUTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGE3X3CONVOLUTIONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

/** Runs a 3x3 convolution kernel against the image
 */
class GPUImage3x3ConvolutionFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImage3x3ConvolutionFilter();
    virtual ~GPUImage3x3ConvolutionFilter();

public:
    void setConvolutionKernel(float* convolutionKernel);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:
    /** Convolution kernel to run against the image

     The convolution kernel is a 3x3 matrix of values to apply to the pixel and its 8 surrounding pixels.
     The matrix is specified in row-major order, with the top left pixel being one.one and the bottom right three.three
     If the values in the matrix don't add up to 1.0, the image could be brightened or darkened.
     */
    float m_pConvolutionKernel[9];

    GLint m_iConvolutionUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGE3X3CONVOLUTIONFILTER_H
