/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageImageFilter.h"


GPUImageImageFilter::GPUImageImageFilter(const char *fragment)
    : GPUImageTwoInputFilter(fragment)
{
    m_pPicDataRGBA = NULL;
    m_uPicWidth = 0;
    m_uPicHeight = 0;
}

GPUImageImageFilter::~GPUImageImageFilter()
{
    this->release();
}

bool GPUImageImageFilter::release()
{
    if(0 != m_uTexture2Id && glIsTexture(m_uTexture2Id)){
        glDeleteTextures(1, &m_uTexture2Id);
        m_uTexture2Id = 0;
    }

    if(NULL != m_pPicDataRGBA){
        free(m_pPicDataRGBA);
        m_pPicDataRGBA = NULL;
    }

    return true;
}

bool GPUImageImageFilter::createProgramExtra()
{
    GPUImageTwoInputFilter::createProgramExtra();

    if(0 == m_uTexture2Id){
        this->loadImage();

        glActiveTexture(GL_TEXTURE1);
        glGenTextures(1, &m_uTexture2Id);
        glBindTexture(GL_TEXTURE_2D, m_uTexture2Id);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D( GL_TEXTURE_2D,
                      0,
                      GL_RGBA,
                      m_uPicWidth,
                      m_uPicHeight,
                      0,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      m_pPicDataRGBA);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return true;
}

bool GPUImageImageFilter::loadImage()
{
    m_pPicDataRGBA = NULL;
    m_uPicWidth = 512;
    m_uPicHeight = 512;

    return true;
}