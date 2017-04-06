/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGECOLORMATRIXFILTER_H
#define CGPUIMAGE_GPUIMAGECOLORMATRIXFILTER_H


#include "GPUImageFilter.h"

/**
 *  Transforms the colors of an image by applying a matrix to them
 */
class GPUImageColorMatrixFilter : public GPUImageFilter{
public:
    GPUImageColorMatrixFilter();
    virtual ~GPUImageColorMatrixFilter();

public:

    void setIntensity(int percent);

public:
    virtual bool createProgramExtra();
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();


protected:
    GLint m_iColorMatrixLocation;
    GLint m_iIntensityLocation;

    /**
     * A 4x4 matrix used to transform each color in an image
     */
    float m_pColorMatrix[16];

    /**
     * The degree to which the new transformed color replaces the original color for each pixel
     */
    float m_fIntensity;
};


#endif //CGPUIMAGE_GPUIMAGECOLORMATRIXFILTER_H
