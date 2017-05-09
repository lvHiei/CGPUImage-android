/**
 * Created by mj on 17-5-9.
 */

#include "GPUImageClosingFilter.h"


GPUImageClosingFilter::GPUImageClosingFilter()
    : GPUImageFilterGroup(),
      m_pErosionFilter(NULL),
      m_pDilationFilter(NULL)
{
    initWithRadius(1);
}


GPUImageClosingFilter::GPUImageClosingFilter(int radius)
        : GPUImageFilterGroup(),
          m_pErosionFilter(NULL),
          m_pDilationFilter(NULL)
{
    initWithRadius(radius);
}


GPUImageClosingFilter::~GPUImageClosingFilter()
{
    this->release();
}


void GPUImageClosingFilter::initWithRadius(int radius)
{
    m_pDilationFilter = new GPUImageDilationFilter(radius);

    m_pErosionFilter = new GPUImageErosionFilter(radius);

    addFilter(m_pDilationFilter);
    addFilter(m_pErosionFilter);
}


void GPUImageClosingFilter::setHorizontalTexelSpacing(GLfloat horizontalTexelSpacing)
{
    if(m_pErosionFilter){
        m_pErosionFilter->setHorizontalTexelSpacing(horizontalTexelSpacing);
    }

    if(m_pDilationFilter){
        m_pDilationFilter->setHorizontalTexelSpacing(horizontalTexelSpacing);
    }
}

void GPUImageClosingFilter::setVerticalTexelSpacing(GLfloat verticalTexelSpacing)
{
    if(m_pErosionFilter){
        m_pErosionFilter->setVerticalTexelSpacing(verticalTexelSpacing);
    }

    if(m_pDilationFilter){
        m_pDilationFilter->setVerticalTexelSpacing(verticalTexelSpacing);
    }
}

bool GPUImageClosingFilter::release()
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

