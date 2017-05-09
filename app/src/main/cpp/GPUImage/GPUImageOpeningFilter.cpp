/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageOpeningFilter.h"

GPUImageOpeningFilter::GPUImageOpeningFilter()
        : GPUImageFilterGroup(),
          m_pErosionFilter(NULL),
          m_pDilationFilter(NULL)
{
    initWithRadius(1);
}


GPUImageOpeningFilter::GPUImageOpeningFilter(int radius)
        : GPUImageFilterGroup(),
          m_pErosionFilter(NULL),
          m_pDilationFilter(NULL)
{
    initWithRadius(radius);
}


GPUImageOpeningFilter::~GPUImageOpeningFilter()
{
    this->release();
}


void GPUImageOpeningFilter::initWithRadius(int radius)
{
    m_pErosionFilter = new GPUImageErosionFilter(radius);
    m_pDilationFilter = new GPUImageDilationFilter(radius);

    addFilter(m_pErosionFilter);
    addFilter(m_pDilationFilter);
}


void GPUImageOpeningFilter::setHorizontalTexelSpacing(GLfloat horizontalTexelSpacing)
{
    if(m_pErosionFilter){
        m_pErosionFilter->setHorizontalTexelSpacing(horizontalTexelSpacing);
    }

    if(m_pDilationFilter){
        m_pDilationFilter->setHorizontalTexelSpacing(horizontalTexelSpacing);
    }
}

void GPUImageOpeningFilter::setVerticalTexelSpacing(GLfloat verticalTexelSpacing)
{
    if(m_pErosionFilter){
        m_pErosionFilter->setVerticalTexelSpacing(verticalTexelSpacing);
    }

    if(m_pDilationFilter){
        m_pDilationFilter->setVerticalTexelSpacing(verticalTexelSpacing);
    }
}

bool GPUImageOpeningFilter::release()
{
    if(m_pErosionFilter){
        delete m_pErosionFilter;
        m_pErosionFilter = NULL;
    }

    if(m_pDilationFilter){
        delete m_pDilationFilter;
        m_pDilationFilter = NULL;
    }

    return true;
}


