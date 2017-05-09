/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGERGBOPENINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGERGBOPENINGFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageRGBErosionFilter.h"
#include "GPUImageRGBDilationFilter.h"

class GPUImageRGBOpeningFilter : public GPUImageFilterGroup{
public:
    GPUImageRGBOpeningFilter();
    GPUImageRGBOpeningFilter(int radius);
    virtual ~GPUImageRGBOpeningFilter();

    virtual bool release();

protected:
    void initWithRadius(int radius);

protected:
    GPUImageRGBErosionFilter* m_pErosionFilter;
    GPUImageRGBDilationFilter* m_pDilationFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGERGBOPENINGFILTER_H
