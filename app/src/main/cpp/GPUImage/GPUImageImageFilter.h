/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEIMAGEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEIMAGEFILTER_H

#include "GPUImageTwoInputFilter.h"

// this is created by lvHiei, just the baseclass of  textureid2 is a picture.
class GPUImageImageFilter : public GPUImageTwoInputFilter{
public:
    GPUImageImageFilter(const char* fragment);
    virtual ~GPUImageImageFilter();

    virtual bool release();

protected:
    virtual bool createProgramExtra();

protected:
    virtual bool loadImage();


protected:
    uint8_t *m_pPicDataRGBA;
    uint32_t m_uPicWidth;
    uint32_t m_uPicHeight;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEIMAGEFILTER_H
