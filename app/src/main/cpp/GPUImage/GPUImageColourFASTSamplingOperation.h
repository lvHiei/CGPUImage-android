/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTSAMPLINGOPERATION_H
#define CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTSAMPLINGOPERATION_H


#include "GPUImageTwoInputFilter.h"

// This is the feature extraction phase of the ColourFAST feature detector, as described in:
//
// A. Ensor and S. Hall. ColourFAST: GPU-based feature point detection and tracking on mobile devices. 28th International Conference of Image and Vision Computing, New Zealand, 2013, p. 124-129.
//
// Seth Hall, "GPU accelerated feature algorithms for mobile devices", PhD thesis, School of Computing and Mathematical Sciences, Auckland University of Technology 2014.
// http://aut.researchgateway.ac.nz/handle/10292/7991


/**
 * added by lvHiei
 * this filter in GPUImage extends GPUImageTwoInputFilter, but in the shader the
 * second image is not used, so it can extends GPUImageFilter
 */
class GPUImageColourFASTSamplingOperation : public GPUImageTwoInputFilter{
public:
    GPUImageColourFASTSamplingOperation();
    virtual ~GPUImageColourFASTSamplingOperation();

    void setTexelWidth(float width);
    void setTexelHeight(float height);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_fTexelWidth;
    GLfloat m_fTexelHeight;

    GLint m_iTexelWidthUniformLocation;
    GLint m_iTexelHeightUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTSAMPLINGOPERATION_H
