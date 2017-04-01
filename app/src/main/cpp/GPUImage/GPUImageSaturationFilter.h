/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGESATURATIONFILTER_H
#define CGPUIMAGE_GPUIMAGESATURATIONFILTER_H


#include "GPUImageFilter.h"


/**
 *  Adjusts the saturation of an image
 */
class GPUImageSaturationFilter : public GPUImageFilter{
public:
    GPUImageSaturationFilter();
    virtual ~GPUImageSaturationFilter();

    /**
     * 饱和度，0.0--2.0, 默认1.0
     */
    void setSaturation(float saturation);

public:
    virtual bool createProgramExtra();
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    GLint m_iSaturationLocation;

    /**
     * Saturation ranges from 0.0 (fully desaturated) to 2.0 (max saturation), with 1.0 as the normal level
     */
    float m_fSaturation;
};


#endif //CGPUIMAGE_GPUIMAGESATURATIONFILTER_H
