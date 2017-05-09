/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTFEATUREDETECTOR_H
#define CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTFEATUREDETECTOR_H


#include "GPUImageFilterGroup.h"
#include "GPUImageBoxBlurFilter.h"
#include "GPUImageColourFASTSamplingOperation.h"

// This generates image-wide feature descriptors using the ColourFAST process, as developed and described in
//
// A. Ensor and S. Hall. ColourFAST: GPU-based feature point detection and tracking on mobile devices. 28th International Conference of Image and Vision Computing, New Zealand, 2013, p. 124-129.
//
// Seth Hall, "GPU accelerated feature algorithms for mobile devices", PhD thesis, School of Computing and Mathematical Sciences, Auckland University of Technology 2014.
// http://aut.researchgateway.ac.nz/handle/10292/7991

class GPUImageColourFASTFeatureDetector : public GPUImageFilterGroup{
public:
    GPUImageColourFASTFeatureDetector();
    virtual ~GPUImageColourFASTFeatureDetector();

    virtual bool release();

    void setBlurRadiusInPixels(GLfloat blurRadiusInPixels);

protected:
    GPUImageBoxBlurFilter* m_pBlurFilter;
    GPUImageColourFASTSamplingOperation* m_pColourFASTSamplingOperation;

protected:
    // The blur radius of the underlying box blur. The default is 3.0.
    GLfloat m_fBlurRadiusInPixels;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECOLOURFASTFEATUREDETECTOR_H
