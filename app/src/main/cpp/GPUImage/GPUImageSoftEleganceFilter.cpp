/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSoftEleganceFilter.h"
#include "../util/TextureRotateUtil.h"


GPUImageSoftEleganceFilter::GPUImageSoftEleganceFilter()
    : GPUImageFilterGroup(),
      m_pFirstLookUpFilter(NULL),
      m_pGaussianBlurFilter(NULL),
      m_pAlphaBlendFilter(NULL),
      m_pSecondLookUpFilter(NULL)
{

    m_pFirstLookUpFilter = new GPUImageLookupFilter("lookup_soft_elegance_1.rgba");

    m_pGaussianBlurFilter = new GPUImageGaussianBlurFilter();

    m_pAlphaBlendFilter = new GPUImageAlphaBlendFilter();

    m_pAlphaBlendFilter->setMix(0.14f);
//    m_pAlphaBlendFilter->setMix(1.0f - 0.14f);

    m_pSecondLookUpFilter = new GPUImageLookupFilter("lookup_soft_elegance_2.rgba");


    addFilter(m_pGaussianBlurFilter);
    addFilter(m_pFirstLookUpFilter);
    addFilter(m_pAlphaBlendFilter);
    addFilter(m_pSecondLookUpFilter);
}

GPUImageSoftEleganceFilter::~GPUImageSoftEleganceFilter()
{
    this->release();
}

bool GPUImageSoftEleganceFilter::release()
{
    if(m_pFirstLookUpFilter){
        delete m_pFirstLookUpFilter;
        m_pFirstLookUpFilter = NULL;
    }

    if(m_pGaussianBlurFilter){
        delete m_pGaussianBlurFilter;
        m_pGaussianBlurFilter = NULL;
    }

    if(m_pAlphaBlendFilter){
        delete m_pAlphaBlendFilter;
        m_pAlphaBlendFilter = NULL;
    }

    if(m_pSecondLookUpFilter){
        delete m_pSecondLookUpFilter;
        m_pSecondLookUpFilter = NULL;
    }

    return GPUImageFilterGroup::release();
}


bool GPUImageSoftEleganceFilter::createProgram()
{
    bool ret =  GPUImageFilterGroup::createProgram();

    if(NULL != m_pAlphaBlendFilter){
        m_pAlphaBlendFilter->setTexture2Id(m_pFrameBufferTextures[0]);
        m_pAlphaBlendFilter->setTexture2Rotation(ROTATION_NORMAL);

        // alpha blend filter is the last filter but one
        GLuint alphaBlendIdx = m_uFilterCnt - 1;

        if(alphaBlendIdx % 2 != 0){
            m_pAlphaBlendFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, true));
        }else{
            m_pAlphaBlendFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, false));
        }
    }

    return ret;
}


