/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTiltShiftFilter.h"
#include "../util/TextureRotateUtil.h"


GPUImageTiltShiftFilter::GPUImageTiltShiftFilter()
    : GPUImageFilterGroup(),
      m_pBlurFilter(NULL),
      m_pTiltShiftFilter(NULL)
{

    m_pBlurFilter = new GPUImageGaussianBlurFilter();

    m_pTiltShiftFilter = new GPUImagePureTiltShiftFilter();


    addFilter(m_pBlurFilter);
    addFilter(m_pTiltShiftFilter);
}

GPUImageTiltShiftFilter::~GPUImageTiltShiftFilter()
{
    this->release();
}

bool GPUImageTiltShiftFilter::release()
{
    if(m_pTiltShiftFilter){
        delete m_pTiltShiftFilter;
        m_pTiltShiftFilter = NULL;
    }

    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    return GPUImageFilterGroup::release();
}

void GPUImageTiltShiftFilter::setTopFocusLevel(float newValue)
{
    if(m_pTiltShiftFilter){
        m_pTiltShiftFilter->setTopFocusLevel(newValue);
    }
}

void GPUImageTiltShiftFilter::setBottomFocusLevel(float newValue)
{
    if(m_pTiltShiftFilter){
        m_pTiltShiftFilter->setBottomFocusLevel(newValue);
    }
}

void GPUImageTiltShiftFilter::setFocusFallOffRate(float newValue)
{
    if(m_pTiltShiftFilter){
        m_pTiltShiftFilter->setFocusFallOffRate(newValue);
    }
}

void GPUImageTiltShiftFilter::setBlurRadiusInPixels(float newValue)
{
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(newValue);
    }
}

bool GPUImageTiltShiftFilter::draw(GLuint textureId, int viewWidth, int viewHeight,
                                   GLuint frameBufferId)
{
    m_pBlurFilter->draw(textureId, m_iTextureWidth, m_iTextureHeight, m_pFrameBuffers[0]);

    if(NULL != m_pTiltShiftFilter){
        m_pTiltShiftFilter->setTexture2Id(m_pFrameBufferTextures[0]);
        m_pTiltShiftFilter->setTexture2Rotation(m_eRotation);
        if(m_uFilterCnt % 2 != 0){
            m_pTiltShiftFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(m_eRotation, false, true));
        }else{
            m_pTiltShiftFilter->setTexture2Coordinate(m_pTextureCoordinate);
        }

        m_pTiltShiftFilter->draw(textureId, viewWidth, viewHeight, frameBufferId);
    }

    return true;
}

