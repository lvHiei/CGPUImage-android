/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESOFTELEGANCEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESOFTELEGANCEFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageLookupFilter.h"
#include "GPUImageGaussianBlurFilter.h"
#include "GPUImageAlphaBlendFilter.h"

/** A photo filter based on Soft Elegance Photoshop action
    http://h-d-stock.deviantart.com/art/H-D-A-soft-elegance-70107603
 */

// Note: If you want to use this effect you have to add
//       lookup_soft_elegance_1.png and lookup_soft_elegance_2.png
//       from Resources folder to your application bundle.


class GPUImageSoftEleganceFilter : public GPUImageFilterGroup{
public:
    GPUImageSoftEleganceFilter();
    virtual ~GPUImageSoftEleganceFilter();

    virtual bool release();

    virtual bool createProgram();

protected:
    GPUImageLookupFilter* m_pFirstLookUpFilter;
    GPUImageGaussianBlurFilter* m_pGaussianBlurFilter;
    GPUImageAlphaBlendFilter* m_pAlphaBlendFilter;
    GPUImageLookupFilter* m_pSecondLookUpFilter;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESOFTELEGANCEFILTER_H
