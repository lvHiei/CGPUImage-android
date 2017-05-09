/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColourFASTFeatureDetector.h"


GPUImageColourFASTFeatureDetector::GPUImageColourFASTFeatureDetector()
    : GPUImageFilterGroup(),
      m_pBlurFilter(NULL),
      m_pColourFASTSamplingOperation(NULL)
{

    m_pBlurFilter = new GPUImageBoxBlurFilter();
    m_pColourFASTSamplingOperation = new GPUImageColourFASTSamplingOperation();


    addFilter(m_pBlurFilter);
    addFilter(m_pColourFASTSamplingOperation);
}


GPUImageColourFASTFeatureDetector::~GPUImageColourFASTFeatureDetector()
{
    this->release();
}

bool GPUImageColourFASTFeatureDetector::release()
{
    if(m_pBlurFilter){
        delete m_pBlurFilter;
        m_pBlurFilter = NULL;
    }

    if(m_pColourFASTSamplingOperation){
        delete m_pColourFASTSamplingOperation;
        m_pColourFASTSamplingOperation = NULL;
    }

    return GPUImageFilterGroup::release();
}

void GPUImageColourFASTFeatureDetector::setBlurRadiusInPixels(GLfloat blurRadiusInPixels)
{
    if(m_pBlurFilter){
        m_pBlurFilter->setBlurRadiusInPixels(blurRadiusInPixels);
    }
}

