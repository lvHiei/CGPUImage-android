/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageiOSBlurFilter.h"


GPUImageiOSBlurFilter::GPUImageiOSBlurFilter()
    : GPUImageFilterGroup(),
      m_pSaturationFilter(NULL),
      m_pBlurFilter(NULL),
      m_pLuminanceRangeFilter(NULL)

{
    m_pSaturationFilter = new GPUImageSaturationFilter();

    m_pBlurFilter = new GPUImageGaussianBlurFilter();

    m_pLuminanceRangeFilter = new GPUImageLuminanceRangeFilter();


    addFilter(m_pSaturationFilter);
    addFilter(m_pBlurFilter);
    addFilter(m_pLuminanceRangeFilter);

    m_fBlurRadiusInPixels = 12.0f;
    m_fSaturation = 0.8f;
    m_fDownsampling = 4.0f;
    m_fRangeReductionFactor = 0.6f;
}

GPUImageiOSBlurFilter::~GPUImageiOSBlurFilter()
{
    this->release();
}

void GPUImageiOSBlurFilter::setBlurRadiusInPixels(float newValue)
{
    m_fBlurRadiusInPixels = newValue;
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(newValue);
    }
}

void GPUImageiOSBlurFilter::setSaturation(float newValue)
{
    m_fSaturation = newValue;
    if(m_pSaturationFilter){
        m_pSaturationFilter->setSaturation(newValue);
    }
}

void GPUImageiOSBlurFilter::setDownsampling(float newValue)
{
    m_fDownsampling = newValue;
}

void GPUImageiOSBlurFilter::setRangeReductionFactor(float newValue)
{
    m_fRangeReductionFactor = newValue;

    if(m_pLuminanceRangeFilter){
        m_pLuminanceRangeFilter->setRangeReductionFactor(newValue);
    }
}


bool GPUImageiOSBlurFilter::release()
{
    if(m_pSaturationFilter){
        delete m_pSaturationFilter;
        m_pSaturationFilter = NULL;
    }

    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    if(m_pLuminanceRangeFilter){
        delete m_pLuminanceRangeFilter;
        m_pLuminanceRangeFilter = NULL;
    }

    return GPUImageFilterGroup::release();
}

