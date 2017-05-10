/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSmoothToonFilter.h"


GPUImageSmoothToonFilter::GPUImageSmoothToonFilter()
    : GPUImageFilterGroup(),
      m_pBlurFilter(NULL),
      m_pToonFilter(NULL)
{

    m_pBlurFilter = new GPUImageGaussianBlurFilter();

    m_pToonFilter = new GPUImageToonFilter();

    addFilter(m_pBlurFilter);
    addFilter(m_pToonFilter);

    m_fBlurRadiusInPixels = 2.0f;
    m_fThreshold = 0.2f;
    m_fQuantizationLevels = 10.0f;
}

GPUImageSmoothToonFilter::~GPUImageSmoothToonFilter()
{
    this->release();
}

void GPUImageSmoothToonFilter::setBlurRadiusInPixels(float newValue)
{
    m_fBlurRadiusInPixels = newValue;
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(newValue);
    }
}

void GPUImageSmoothToonFilter::setTexelWidth(float newValue)
{
    m_fTexelWidth = newValue;

    if(m_pToonFilter){
        m_pToonFilter->setTexelWidth(newValue);
    }
}

void GPUImageSmoothToonFilter::setTexelHeight(float newValue)
{
    m_fTexelHeight = newValue;

    if(m_pToonFilter){
        m_pToonFilter->setTexelHeight(newValue);
    }
}

void GPUImageSmoothToonFilter::setThreshold(float newValue)
{
    m_fThreshold = newValue;

    if(m_pToonFilter){
        m_pToonFilter->setThreshold(newValue);
    }
}

void GPUImageSmoothToonFilter::setQuantizationLevels(float newValue)
{
    m_fQuantizationLevels = newValue;

    if(m_pToonFilter){
        m_pToonFilter->setQuantizationLevels(newValue);
    }
}

bool GPUImageSmoothToonFilter::release()
{
    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    if(m_pToonFilter){
        delete m_pToonFilter;
        m_pToonFilter = NULL;
    }

    return GPUImageFilterGroup::release();
}

