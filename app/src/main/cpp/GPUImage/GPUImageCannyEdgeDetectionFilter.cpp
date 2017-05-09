/**
 * Created by mj on 17-5-9.
 */

#include "GPUImageCannyEdgeDetectionFilter.h"


GPUImageCannyEdgeDetectionFilter::GPUImageCannyEdgeDetectionFilter()
    : GPUImageFilterGroup(),
      m_pLuminanceFilter(NULL),
      m_pBlurFilter(NULL),
      m_pEdgeDetectionFilter(NULL),
      m_pNonMaximumSuppressionFilter(NULL),
      m_pWeakPixelInclusionFilter(NULL)
{

    m_pLuminanceFilter = new GPUImageGreyscaleFilter();

    m_pBlurFilter = new GPUImageSingleComponentGaussianBlurFilter();

    m_pEdgeDetectionFilter = new GPUImageDirectionalSobelEdgeDetectionFilter();

    m_pNonMaximumSuppressionFilter = new GPUImageDirectionalNonMaximumSuppressionFilter();

    m_pWeakPixelInclusionFilter = new GPUImageWeakPixelInclusionFilter();

    addFilter(m_pLuminanceFilter);
    addFilter(m_pBlurFilter);
    addFilter(m_pEdgeDetectionFilter);
    addFilter(m_pNonMaximumSuppressionFilter);
    addFilter(m_pWeakPixelInclusionFilter);
}

GPUImageCannyEdgeDetectionFilter::~GPUImageCannyEdgeDetectionFilter()
{
    this->release();
}

void GPUImageCannyEdgeDetectionFilter::setTexelWidth(GLfloat texelWidth)
{
    if(m_pEdgeDetectionFilter){
        m_pEdgeDetectionFilter->setTexelWidth(texelWidth);
    }
}

void GPUImageCannyEdgeDetectionFilter::setTexelHeight(GLfloat texelHeight)
{
    if(m_pEdgeDetectionFilter){
        m_pEdgeDetectionFilter->setTexelHeight(texelHeight);
    }
}

void GPUImageCannyEdgeDetectionFilter::setBlurRadiusInPixels(GLfloat blurRadiusInPixels)
{
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(blurRadiusInPixels);
    }
}

void GPUImageCannyEdgeDetectionFilter::setBlurTexelSpacingMultiplier(
        GLfloat blurTexelSpacingMultiplier)
{
    if(m_pBlurFilter){
        m_pBlurFilter->setTexelSpacingMultiplier(blurTexelSpacingMultiplier);
    }
}

void GPUImageCannyEdgeDetectionFilter::setUpperThreshold(GLfloat upperThreshold) {
    if(m_pNonMaximumSuppressionFilter){
        m_pNonMaximumSuppressionFilter->setUpperThreshold(upperThreshold);
    }
}

void GPUImageCannyEdgeDetectionFilter::setLowerThreshold(GLfloat lowerThreshold)
{
    if(m_pNonMaximumSuppressionFilter){
        m_pNonMaximumSuppressionFilter->setLowerThreshold(lowerThreshold);
    }
}

bool GPUImageCannyEdgeDetectionFilter::release()
{
    if(m_pLuminanceFilter){
        delete m_pLuminanceFilter;
        m_pLuminanceFilter = NULL;
    }

    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    if(m_pEdgeDetectionFilter){
        delete m_pEdgeDetectionFilter;
        m_pEdgeDetectionFilter = NULL;
    }

    if(m_pNonMaximumSuppressionFilter){
        delete m_pNonMaximumSuppressionFilter;
        m_pNonMaximumSuppressionFilter = NULL;
    }

    if(m_pWeakPixelInclusionFilter){
        delete m_pWeakPixelInclusionFilter;
        m_pWeakPixelInclusionFilter = NULL;
    }
}

