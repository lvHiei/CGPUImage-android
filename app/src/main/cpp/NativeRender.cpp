/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "NativeRender.h"
#include "GPUImage/GPUImageGreyscaleFilter.h"
#include "GPUImage/GPUImageContrastFilter.h"
#include "GPUImage/GPUImageSepiaFilter.h"
#include "GPUImage/GPUImageSaturationFilter.h"
#include "GPUImage/GPUImageAmatorkaFilter.h"


//顶点坐标（前四个点）与纹理坐标（后四个点）
float vertex_coordinate[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
};

float textureCoord_front[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

float textureCoord_back[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

};


NativeRender::NativeRender()
{
    m_pFilter = NULL;

    m_bFrontCamera = true;
}

NativeRender::~NativeRender()
{
    if(NULL != m_pFilter)
    {
       delete m_pFilter;
        m_pFilter = NULL;
    }

}

bool NativeRender::createFilter(int filterType)
{
    if(NULL != m_pFilter){
        delete m_pFilter;
    }

    intenalCreateFilter(filterType);

    m_pFilter->setVertexCoordinate(vertex_coordinate);
    if(m_bFrontCamera){
        m_pFilter->setTextureCoordinate(textureCoord_front);
    }else{
        m_pFilter->setTextureCoordinate(textureCoord_back);
    }

    return m_pFilter->createProgram();
}

void NativeRender::intenalCreateFilter(int filterType)
{
//    m_pFilter = new GPUImageFilter();
//    m_pFilter = new GPUImageGreyscaleFilter();
//    m_pFilter = new GPUImageContrastFilter();
//    m_pFilter = new GPUImageSaturationFilter();
//    m_pFilter = new GPUImageSepiaFilter();
    m_pFilter = new GPUImageAmatorkaFilter();
}

bool NativeRender::draw(int textureId, int viewWidth, int viewHeight)
{
    if(!m_pFilter){
        return false;
    }

    LOGI("NativeRender::draw...");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, viewWidth, viewHeight);
    return m_pFilter->draw(textureId, viewWidth, viewHeight);
}

bool NativeRender::setFrontCamera(bool front)
{
    m_bFrontCamera = front;

    if(NULL != m_pFilter){
        if(m_bFrontCamera){
            m_pFilter->setTextureCoordinate(textureCoord_front);
        }else{
            m_pFilter->setTextureCoordinate(textureCoord_back);
        }
    }

    return true;
}