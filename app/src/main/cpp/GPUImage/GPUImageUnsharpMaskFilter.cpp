/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageUnsharpMaskFilter.h"
#include "../util/TextureRotateUtil.h"


GPUImageUnsharpMaskFilter::GPUImageUnsharpMaskFilter()
    : GPUImageFilterGroup(),
      m_pBlurFilter(NULL),
      m_pUnsharpFilter(NULL)
{
    m_pBlurFilter = new GPUImageGaussianBlurFilter();

    m_pUnsharpFilter = new GPUImagePureUnsharpMaskFilter();

    addFilter(m_pBlurFilter);
    addFilter(m_pUnsharpFilter);
}

GPUImageUnsharpMaskFilter::~GPUImageUnsharpMaskFilter()
{
    this->release();
}

bool GPUImageUnsharpMaskFilter::draw(GLuint textureId, int viewWidth, int viewHeight,
                                     GLuint frameBufferId)
{
    m_pBlurFilter->draw(textureId, m_iTextureWidth, m_iTextureHeight, m_pFrameBuffers[0]);

    if(NULL != m_pUnsharpFilter){
        m_pUnsharpFilter->setTexture2Id(m_pFrameBufferTextures[0]);
        m_pUnsharpFilter->setTexture2Rotation(m_eRotation);
        if(m_uFilterCnt % 2 != 0){
            m_pUnsharpFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(m_eRotation, false, true));
        }else{
            m_pUnsharpFilter->setTexture2Coordinate(m_pTextureCoordinate);
        }

        m_pUnsharpFilter->draw(textureId, viewWidth, viewHeight, frameBufferId);
    }


    return true;
}

bool GPUImageUnsharpMaskFilter::release()
{
    if(m_pUnsharpFilter){
        delete m_pUnsharpFilter;
        m_pUnsharpFilter = NULL;
    }

    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }
    return GPUImageFilterGroup::release();
}

