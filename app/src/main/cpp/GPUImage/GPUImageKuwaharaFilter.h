/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEKUWAHARAFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEKUWAHARAFILTER_H


#include "GPUImageFilter.h"

/** Kuwahara image abstraction, drawn from the work of Kyprianidis, et. al.
 * in their publication "Anisotropic Kuwahara Filtering on the GPU" within the GPU Pro collection. This produces an oil-painting-like image,
 * but it is extremely computationally expensive, so it can take seconds to render a frame on an iPad 2. This might be best used for still images.
 */

class GPUImageKuwaharaFilter : public GPUImageFilter{
public:
    GPUImageKuwaharaFilter();
    virtual ~GPUImageKuwaharaFilter();

    void setRadius(uint32_t radius);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    /// The radius to sample from when creating the brush-stroke effect, with a default of 3. The larger the radius, the slower the filter.
    GLuint m_uRadius;

    GLint m_iRadiusUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEKUWAHARAFILTER_H
