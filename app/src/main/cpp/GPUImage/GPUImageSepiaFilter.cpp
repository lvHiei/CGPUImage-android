/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageSepiaFilter.h"

const float sepiaColorMatrix[] = {
        0.3588, 0.7044, 0.1368, 0.0,
        0.2990, 0.5870, 0.1140, 0.0,
        0.2392, 0.4696, 0.0912, 0.0,
        0, 0, 0, 1.0
};


GPUImageSepiaFilter::GPUImageSepiaFilter()
        : GPUImageColorMatrixFilter()
{
    m_fIntensity = 1.0f;
    memcpy(m_pColorMatrix, sepiaColorMatrix, 16*sizeof(float));
}