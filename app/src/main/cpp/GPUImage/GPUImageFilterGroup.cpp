/**
 * Created by lvHiei on 17-5-8.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageFilterGroup.h"
#include "../util/TextureRotateUtil.h"


GPUImageFilterGroup::GPUImageFilterGroup()
{
    m_pFrameBuffers = NULL;
    m_pFrameBufferTextures = NULL;

    m_uFilterCnt = 0;
}

GPUImageFilterGroup::~GPUImageFilterGroup()
{
    this->release();
}

void GPUImageFilterGroup::addFilter(GPUImageFilter *filter)
{
    m_vFilters.push_back(filter);
    m_uFilterCnt = m_vFilters.size();
}

void GPUImageFilterGroup::clear()
{
    m_vFilters.clear();
    m_uFilterCnt = m_vFilters.size();
}

GPUImageFilter *GPUImageFilterGroup::getFilter(int idx)
{
    if(idx >= m_uFilterCnt){
        return NULL;
    }

    return m_vFilters[idx];
}

bool GPUImageFilterGroup::createProgram()
{
    bool ret = true;
    ret = createFrameBuffer();

    if(!ret){
        LOGE("create frame buffer failed");
        return false;
    }

    for(int i = 0; i < m_uFilterCnt; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        ret = ret && filter->createProgram();
    }

    return ret;
}

void GPUImageFilterGroup::setVertexCoordinate(float *vertexCoordinate)
{
    GPUImageFilter::setVertexCoordinate(vertexCoordinate);

    for(int i = 0; i < m_uFilterCnt; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        filter->setVertexCoordinate(vertexCoordinate);
    }
}

void GPUImageFilterGroup::setTextureCoordinate(float *textureCoordinate)
{
    GPUImageFilter::setTextureCoordinate(textureCoordinate);

    for(int i = 0; i < m_uFilterCnt; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        if(i != m_uFilterCnt - 1){
            if(m_uFilterCnt % 2 == 0){
                filter->setTextureCoordinate(TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, true));
            }else{
                filter->setTextureCoordinate(TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, false));
            }
        }else{
            filter->setTextureCoordinate(textureCoordinate);
        }
    }
}

bool GPUImageFilterGroup::draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId)
{
    bool ret = true;

    GLuint lastTextureId = textureId;
    for(int i = 0; i < m_uFilterCnt; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        if(i != m_uFilterCnt - 1){
            ret = ret && filter->draw(lastTextureId, m_iTextureWidth, m_iTextureHeight, m_pFrameBuffers[i]);
            lastTextureId = m_pFrameBufferTextures[i];
        }else{
            ret = ret && filter->draw(lastTextureId, viewWidth, viewHeight, frameBufferId);
        }
    }

    return ret;
}

bool GPUImageFilterGroup::release()
{
//    for(int i = 0; i < m_uFilterCnt; ++i){
//        GPUImageFilter* filter = m_vFilters[i];
//
//        filter->release();
//    }

    clear();
    deleteFrameBuffer();

    return true;
}


void GPUImageFilterGroup::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);

    for(int i = 0; i < m_uFilterCnt - 1; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        filter->setTextureRotation(ROTATION_NORMAL);
    }

    m_vFilters[m_uFilterCnt - 1]->setTextureRotation(rotation);
}


bool GPUImageFilterGroup::createFrameBuffer()
{
    if(m_uFilterCnt <= 1){
        return true;
    }

    uint32_t frameBufferCnt = m_uFilterCnt - 1;

    m_pFrameBuffers = (GLuint *) malloc(frameBufferCnt * sizeof(GLuint));
    m_pFrameBufferTextures = (GLuint *) malloc(frameBufferCnt * sizeof(GLuint));

    glGenFramebuffers(frameBufferCnt, m_pFrameBuffers);
    glGenTextures(frameBufferCnt, m_pFrameBufferTextures);

    bool ret = true;
    for(int i = 0; i < frameBufferCnt; ++i){
        glBindTexture(GL_TEXTURE_2D, m_pFrameBufferTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        glTexParameterf(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, m_pFrameBuffers[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, m_pFrameBufferTextures[i], 0);

        ret = ret && GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    return ret;
}

void GPUImageFilterGroup::deleteFrameBuffer()
{
    if(m_uFilterCnt > 1){
//        LOGI("deleting framebuffers");
        glDeleteFramebuffers(m_uFilterCnt - 1, m_pFrameBuffers);
        glDeleteTextures(m_uFilterCnt - 1, m_pFrameBufferTextures);
    }
}


void GPUImageFilterGroup::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);

    for(int i = 0; i < m_uFilterCnt; ++i){
        GPUImageFilter* filter = m_vFilters[i];
        filter->setTextureSize(width, height);
    }
}

