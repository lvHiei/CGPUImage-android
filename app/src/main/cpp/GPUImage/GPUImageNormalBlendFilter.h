/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGENORMALBLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGENORMALBLENDFILTER_H


#include "GPUImageImageFilter.h"

/*
 This equation is a simplification of the general blending equation. It assumes the destination color is opaque, and therefore drops the destination color's alpha term.

 D = C1 * C1a + C2 * C2a * (1 - C1a)
 where D is the resultant color, C1 is the color of the first element, C1a is the alpha of the first element, C2 is the second element color, C2a is the alpha of the second element. The destination alpha is calculated with:

 Da = C1a + C2a * (1 - C1a)
 The resultant color is premultiplied with the alpha. To restore the color to the unmultiplied values, just divide by Da, the resultant alpha.

 http://stackoverflow.com/questions/1724946/blend-mode-on-a-transparent-and-semi-transparent-background

 For some reason Photoshop behaves
 D = C1 + C2 * C2a * (1 - C1a)
 */

class GPUImageNormalBlendFilter : public GPUImageImageFilter{
public:
    GPUImageNormalBlendFilter();
    virtual ~GPUImageNormalBlendFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGENORMALBLENDFILTER_H
