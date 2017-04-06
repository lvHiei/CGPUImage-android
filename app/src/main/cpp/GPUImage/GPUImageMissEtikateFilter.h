/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMISSETIKATEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMISSETIKATEFILTER_H


#include "GPUImageLookupFilter.h"

/** A photo filter based on Photoshop action by Miss Etikate:
    http://miss-etikate.deviantart.com/art/Photoshop-Action-15-120151961
 */

// Note: If you want to use this effect you have to add lookup_miss_etikate.png
//       from Resources folder to your application bundle.

class GPUImageMissEtikateFilter : public GPUImageLookupFilter{
public:
    GPUImageMissEtikateFilter();
    virtual ~GPUImageMissEtikateFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMISSETIKATEFILTER_H
