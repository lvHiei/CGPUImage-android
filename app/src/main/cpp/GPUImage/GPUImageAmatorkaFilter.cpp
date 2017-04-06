/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageAmatorkaFilter.h"
#include "../util/FileUtil.h"


GPUImageAmatorkaFilter::GPUImageAmatorkaFilter():
    GPUImageLookupFilter()
{
    m_fIntensity = 0.5f;
}

GPUImageAmatorkaFilter::~GPUImageAmatorkaFilter()
{
    this->release();
}

bool GPUImageAmatorkaFilter::loadImage()
{
    // this is decode the image of lookup_amatorka.png.
    // in the example we just use the rgba data stored in
    // the file lookup_amatorka.rgba.

    m_uPicWidth = 512;
    m_uPicHeight = 512;
    uint32_t fileLen = FileUtil::getFileSize("lookup_amatorka.rgba");
    if(fileLen > 0){
        m_pPicDataRGBA = (uint8_t *) malloc(fileLen * sizeof(uint8_t));
        if(!m_pPicDataRGBA){
            return false;
        }

        FileUtil::loadFile("lookup_amatorka.rgba", m_pPicDataRGBA, fileLen);
    }

    return true;
}