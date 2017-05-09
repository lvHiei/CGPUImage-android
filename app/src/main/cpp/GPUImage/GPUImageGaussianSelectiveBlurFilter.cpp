/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGaussianSelectiveBlurFilter.h"
#include "../util/TextureRotateUtil.h"


GPUImageGaussianSelectiveBlurFilter::GPUImageGaussianSelectiveBlurFilter()
    : GPUImageFilterGroup(),
      m_pBlurFilter(NULL),
      m_pSelectiveFocusFilter(NULL)
{
    m_pBlurFilter = new GPUImageGaussianBlurFilter();
    m_pSelectiveFocusFilter = new GPUImageSelectiveFocusFilter();

    addFilter(m_pBlurFilter);
    addFilter(m_pSelectiveFocusFilter);
}

GPUImageGaussianSelectiveBlurFilter::~GPUImageGaussianSelectiveBlurFilter()
{
    this->release();
}

void GPUImageGaussianSelectiveBlurFilter::setExcludeCircleRadius(float newValue)
{
    if(m_pSelectiveFocusFilter){
        m_pSelectiveFocusFilter->setExcludeCircleRadius(newValue);
    }
}

void GPUImageGaussianSelectiveBlurFilter::setExcludeCirclePoint(float x, float y)
{
    if(m_pSelectiveFocusFilter){
        m_pSelectiveFocusFilter->setExcludeCirclePoint(x, y);
    }
}

void GPUImageGaussianSelectiveBlurFilter::setExcludeBlurSize(float newValue)
{
    if(m_pSelectiveFocusFilter){
        m_pSelectiveFocusFilter->setExcludeBlurSize(newValue);
    }
}

void GPUImageGaussianSelectiveBlurFilter::setBlurRadiusInPixels(float newValue)
{
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(newValue);
    }
}

void GPUImageGaussianSelectiveBlurFilter::setAspectRatio(float newValue)
{
    if(m_pSelectiveFocusFilter){
        m_pSelectiveFocusFilter->setAspectRatio(newValue);
    }
}


bool GPUImageGaussianSelectiveBlurFilter::release()
{
    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    if(m_pSelectiveFocusFilter){
        delete m_pSelectiveFocusFilter;
        m_pSelectiveFocusFilter = NULL;
    }

    return GPUImageFilterGroup::release();
}

bool GPUImageGaussianSelectiveBlurFilter::draw(GLuint textureId, int viewWidth, int viewHeight,
                                               GLuint frameBufferId)
{
    if(NULL != m_pSelectiveFocusFilter){
        m_pSelectiveFocusFilter->setTexture2Id(textureId);
        m_pSelectiveFocusFilter->setTexture2Rotation(m_eRotation);
        if(m_uFilterCnt % 2 != 0){
            m_pSelectiveFocusFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(m_eRotation, false, true));
        }else{
            m_pSelectiveFocusFilter->setTexture2Coordinate(m_pTextureCoordinate);
        }
    }

    return GPUImageFilterGroup::draw(textureId, viewWidth, viewHeight, frameBufferId);
}

