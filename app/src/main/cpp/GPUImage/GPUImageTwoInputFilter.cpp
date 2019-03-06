/**
 * Created by lvHiei on 17-4-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTwoInputFilter.h"
#include "../util/TextureRotateUtil.h"


// 顶点着色器
extern const char _twoInput_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;
    attribute vec4 inputTextureCoordinate2;

    varying vec2 textureCoordinate;
    varying vec2 textureCoordinate2;

    void main()
    {
        gl_Position = position;
        textureCoordinate = inputTextureCoordinate.xy;
        textureCoordinate2 = inputTextureCoordinate2.xy;
    }
);

GPUImageTwoInputFilter::GPUImageTwoInputFilter(const char *fragment)
    : GPUImageFilter(_twoInput_vertex_shader, fragment)
{
    m_uTexture2Id = 0;
    m_iTexture2IdLocation = -1;
    m_iTexture2IdCoordinateLocation = -1;
    m_eTexture2Rotation = ROTATION_NORMAL;

    m_pTexture2Coordinate = NULL;
}

GPUImageTwoInputFilter::GPUImageTwoInputFilter(const char *vertex, const char *fragment)
    : GPUImageFilter(vertex, fragment)
{
    m_uTexture2Id = 0;
    m_iTexture2IdLocation = -1;
    m_iTexture2IdCoordinateLocation = -1;
    m_eTexture2Rotation = ROTATION_NORMAL;
    m_pTexture2Coordinate = NULL;
}

GPUImageTwoInputFilter::~GPUImageTwoInputFilter()
{
    this->release();
}

bool GPUImageTwoInputFilter::release()
{
    if(m_pTexture2Coordinate){
        free(m_pTexture2Coordinate);
        m_pTexture2Coordinate = NULL;
    }
    return true;
}

bool GPUImageTwoInputFilter::createProgramExtra()
{
    m_iTexture2IdLocation = glGetUniformLocation(m_uProgram, "inputImageTexture2");
    m_iTexture2IdCoordinateLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate2");

    return true;
}

bool GPUImageTwoInputFilter::beforeDrawExtra()
{
    float* textureCoord = m_pTexture2Coordinate != NULL ? m_pTexture2Coordinate : TextureRotateUtil::getTextureCoordinate(m_eTexture2Rotation, false, false);
    glVertexAttribPointer(m_iTexture2IdCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoord);
    glEnableVertexAttribArray(m_iTexture2IdCoordinateLocation);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_uTexture2Id);
    glUniform1i(m_iTexture2IdLocation, 1);
    return true;
}

bool GPUImageTwoInputFilter::onDrawExtra()
{
    glDisableVertexAttribArray(m_iTexture2IdCoordinateLocation);
    return true;
}

void GPUImageTwoInputFilter::setTexture2Id(GLuint texture2Id)
{
    m_uTexture2Id = texture2Id;
}


void GPUImageTwoInputFilter::setTexture2Rotation(Rotation rotation)
{
    m_eTexture2Rotation = rotation;
}


void GPUImageTwoInputFilter::setTexture2Coordinate(float *textureCoordinate)
{
    if(!textureCoordinate){
        return;
    }

    if(!m_pTexture2Coordinate){
        m_pTexture2Coordinate = (float *) malloc(sizeof(float) * TEXTURE_COORDINATE_SIZE);
    }

    memcpy(m_pTexture2Coordinate, textureCoordinate, sizeof(float)*TEXTURE_COORDINATE_SIZE);
}

