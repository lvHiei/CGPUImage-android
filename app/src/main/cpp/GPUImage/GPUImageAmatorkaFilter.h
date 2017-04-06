/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEAMATORKAFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEAMATORKAFILTER_H


#include "GPUImageLookupFilter.h"

/** A photo filter based on Photoshop action by Amatorka
    http://amatorka.deviantart.com/art/Amatorka-Action-2-121069631
 */

// Note: If you want to use this effect you have to add lookup_amatorka.png
//       from Resources folder to your application bundle.

class GPUImageAmatorkaFilter : public GPUImageLookupFilter{
public:
    GPUImageAmatorkaFilter();
    ~GPUImageAmatorkaFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEAMATORKAFILTER_H
