/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMissEtikateFilter.h"
#include "../util/FileUtil.h"


GPUImageMissEtikateFilter::GPUImageMissEtikateFilter():
        GPUImageLookupFilter()
{
    m_fIntensity = 0.5f;
}

GPUImageMissEtikateFilter::~GPUImageMissEtikateFilter()
{
    this->release();
}

bool GPUImageMissEtikateFilter::loadImage()
{
    // this is decode the image of lookup_miss_etikate.png.
    // in the example we just use the rgba data stored in
    // the file lookup_miss_etikate.rgba.

    const char* filename = "lookup_miss_etikate.rgba";

    m_uPicWidth = 512;
    m_uPicHeight = 512;
    uint32_t fileLen = FileUtil::getFileSize(filename);
    if(fileLen > 0){
        m_pPicDataRGBA = (uint8_t *) malloc(fileLen * sizeof(uint8_t));
        if(!m_pPicDataRGBA){
            return false;
        }

        FileUtil::loadFile(filename, m_pPicDataRGBA, fileLen);
    }

    return true;
}