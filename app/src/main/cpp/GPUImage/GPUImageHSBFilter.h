/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEHSBFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEHSBFILTER_H


#include "GPUImageColorMatrixFilter.h"

class GPUImageHSBFilter : public GPUImageColorMatrixFilter{
public:
    GPUImageHSBFilter();
    virtual ~GPUImageHSBFilter();

    void reset();
    void rotateHue(float h);
    void adjustSaturation(float s);
    void adjustBrightness(float b);

protected:
    float m_pMatrix[16];

protected:
    void updateColorMatrix();

protected:
    void matrixmult(float* a, float* b, float* c);
    void identmat(float* matrix);
    void xformpnt(float* matrix, float x, float y, float z, float* tx, float* ty, float* tz);
    void cscalemat(float* mat, float rscale, float gscale, float bscale);\
    void saturatemat(float* mat, float sat);
    void xrotatemat(float* mat, float rs, float rc);
    void yrotatemat(float* mat, float rs, float rc);
    void zrotatemat(float* mat, float rs, float rc);
    void zshearmat(float* mat, float dx, float dy);
    void huerotatemat(float* mat, float rot);
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEHSBFILTER_H
