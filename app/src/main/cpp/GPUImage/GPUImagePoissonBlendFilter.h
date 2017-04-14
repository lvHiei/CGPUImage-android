/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPOISSONBLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPOISSONBLENDFILTER_H


#include "GPUImageTwoInputCrossTextureSamplingFilter.h"

class GPUImagePoissonBlendFilter : public GPUImageTwoInputCrossTextureSamplingFilter{
public:
    GPUImagePoissonBlendFilter();
    virtual ~GPUImagePoissonBlendFilter();

    void setMix(float mix);
    void setMix(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:
    // Mix ranges from 0.0 (only image 1) to 1.0 (only image 2 gradients), with 1.0 as the normal level
    GLfloat m_fMix;


    /**
     * todo this is not implement
     */
    // The number of times to propagate the gradients.
    // Crank this up to 100 or even 1000 if you want to get anywhere near convergence.  Yes, this will be slow.
    GLuint m_uNumIterations;


    GLint m_iMixUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPOISSONBLENDFILTER_H
