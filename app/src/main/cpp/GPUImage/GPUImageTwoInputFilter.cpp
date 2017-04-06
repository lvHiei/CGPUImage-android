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

    m_uImageTextureId = 0;
    m_iImageTextureIdLocation = -1;
    m_iImageTextureIdCoordinateLocation = -1;

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

    if(0 != m_uImageTextureId && glIsTexture(m_uTextureId)){
        glDeleteTextures(1, &m_uImageTextureId);
        m_uImageTextureId = 0;
    }

    if(NULL != m_pPicDataRGBA){
        free(m_pPicDataRGBA);
        m_pPicDataRGBA = NULL;
    }

    return true;
}

bool GPUImageTwoInputFilter::loadImage()
{
    m_pPicDataRGBA = NULL;
    m_uPicWidth = 512;
    m_uPicHeight = 512;

    return true;
}

bool GPUImageTwoInputFilter::createProgramExtra()
{
    m_iImageTextureIdLocation = glGetUniformLocation(m_uProgram, "inputImageTexture2");
    m_iImageTextureIdCoordinateLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate2");

    if(0 == m_uImageTextureId){
        this->loadImage();

        glActiveTexture(GL_TEXTURE1);
        glGenTextures(1, &m_uImageTextureId);
        glBindTexture(GL_TEXTURE_2D, m_uImageTextureId);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D( GL_TEXTURE_2D,
                      0,
                      GL_RGBA,
                      m_uPicWidth,
                      m_uPicHeight,
                      0,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      m_pPicDataRGBA);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

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
    glVertexAttribPointer(m_iImageTextureIdCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoord);
    glEnableVertexAttribArray(m_iImageTextureIdCoordinateLocation);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_uImageTextureId);
    glUniform1i(m_iImageTextureIdLocation, 1);
    return true;
}

bool GPUImageTwoInputFilter::onDrawExtra()
{
    glDisableVertexAttribArray(m_iImageTextureIdCoordinateLocation);
    return true;
}