/**
 * Created by mj on 17-5-9.
 */

#include "GPUImageRGBOpeningFilter.h"

GPUImageRGBOpeningFilter::GPUImageRGBOpeningFilter()
        : GPUImageFilterGroup(),
          m_pErosionFilter(NULL),
          m_pDilationFilter(NULL)
{
    initWithRadius(1);
}

GPUImageRGBOpeningFilter::GPUImageRGBOpeningFilter(int radius)
        : GPUImageFilterGroup(),
          m_pErosionFilter(NULL),
          m_pDilationFilter(NULL)
{
    initWithRadius(radius);
}

GPUImageRGBOpeningFilter::~GPUImageRGBOpeningFilter()
{
    this->release();
}

bool GPUImageRGBOpeningFilter::release()
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

void GPUImageRGBOpeningFilter::initWithRadius(int radius)
{
    m_pErosionFilter = new GPUImageRGBErosionFilter(radius);

    m_pDilationFilter = new GPUImageRGBDilationFilter(radius);

    addFilter(m_pErosionFilter);
    addFilter(m_pDilationFilter);
}

