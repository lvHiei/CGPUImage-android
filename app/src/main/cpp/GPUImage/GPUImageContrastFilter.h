/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGECONTRASTFILTER_H
#define CGPUIMAGE_GPUIMAGECONTRASTFILTER_H


#include "GPUImageFilter.h"


/**
 * Adjusts the contrast of the image
 */
class GPUImageContrastFilter : public GPUImageFilter{
public:
    GPUImageContrastFilter();
    virtual ~GPUImageContrastFilter();

    /**
     * 设置对比度
     * @param 对比度  1.0--4.0f default 1.0
     */
    void setContrast(int percent);
    void setContrast(float contrast);


protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    GLint m_iContrastLocation;

    /**
     *  Contrast ranges from 0.0 to 4.0 (max contrast), with 1.0 as the normal level
     */
    GLfloat m_fContrast;
};


#endif //CGPUIMAGE_GPUIMAGECONTRASTFILTER_H
