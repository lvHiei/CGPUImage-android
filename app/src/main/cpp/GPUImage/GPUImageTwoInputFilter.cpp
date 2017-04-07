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
{
    int fragLen = strlen(fragment) + 1;
    m_pFragmentShader = (char *) malloc(fragLen * sizeof(char));

    strcpy(m_pFragmentShader, fragment);

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
    if(NULL != m_pFragmentShader){
        free(m_pFragmentShader);
        m_pFragmentShader = NULL;
    }

    return true;
}

bool GPUImageTwoInputFilter::createProgramExtra()
{
    m_iTexture2IdLocation = glGetUniformLocation(m_uProgram, "inputImageTexture2");
    m_iTexture2IdCoordinateLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate2");

    return true;
}

bool GPUImageTwoInputFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_twoInput_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _twoInput_vertex_shader);
    length = expLen;
    return true;
}

bool GPUImageTwoInputFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(m_pFragmentShader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

//    sprintf(fragment, m_pFragmentShader);
    strcpy(fragment, m_pFragmentShader);
    length = expLen;
    return true;
}

bool GPUImageTwoInputFilter::beforeDrawExtra()
{
    float* textureCoord = TextureRotateUtil::getTextureCoordinate(0, false, false);
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