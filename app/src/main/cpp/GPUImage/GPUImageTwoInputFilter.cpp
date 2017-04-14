/**
 * Created by lvHiei on 17-4-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTwoInputFilter.h"
#include "../util/TextureRotateUtil.h"


// 顶点着色器
const char _twoInput_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"attribute vec4 inputTextureCoordinate2;\n"

"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"

"void main()\n"
"{\n"
"	gl_Position = position;\n"
"	textureCoordinate = inputTextureCoordinate.xy;\n"
"   textureCoordinate2 = inputTextureCoordinate2.xy;\n"
"}\n"
;

GPUImageTwoInputFilter::GPUImageTwoInputFilter(const char *fragment)
    : GPUImageFilter(_twoInput_vertex_shader, fragment)
{

    m_uTexture2Id = 0;
    m_iTexture2IdLocation = -1;
    m_iTexture2IdCoordinateLocation = -1;

}

GPUImageTwoInputFilter::GPUImageTwoInputFilter(const char *vertex, const char *fragment)
    : GPUImageFilter(vertex, fragment)
{
    m_uTexture2Id = 0;
    m_iTexture2IdLocation = -1;
    m_iTexture2IdCoordinateLocation = -1;

}

GPUImageTwoInputFilter::~GPUImageTwoInputFilter()
{
    this->release();
}

bool GPUImageTwoInputFilter::release()
{

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
    float* textureCoord = TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, false);
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