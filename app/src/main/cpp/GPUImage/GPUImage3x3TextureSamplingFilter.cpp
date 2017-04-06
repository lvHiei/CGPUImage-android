/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImage3x3TextureSamplingFilter.h"

// 顶点着色器
const char _3x3TextureSampling_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidth;\n"
"uniform float texelHeight;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 widthStep = vec2(texelWidth, 0.0);\n"
"    vec2 heightStep = vec2(0.0, texelHeight);\n"
"    vec2 widthHeightStep = vec2(texelWidth, texelHeight);\n"
"    vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);\n"
"\n"
"    textureCoordinate = inputTextureCoordinate.xy;\n"
"    leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;\n"
"    rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;\n"
"\n"
"    topTextureCoordinate = inputTextureCoordinate.xy - heightStep;\n"
"    topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;\n"
"    topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;\n"
"\n"
"    bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;\n"
"    bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;\n"
"    bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;\n"
"}"
;


GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter(const char *fragment)
{
    int fragLen = strlen(fragment) + 1;
    m_pFragmentShader = (char *) malloc(fragLen * sizeof(char));

    strcpy(m_pFragmentShader, fragment);

    m_fTexelWidth = 1.0 / 1280;
    m_fTexelWidth = 1.0 / 720;
}


GPUImage3x3TextureSamplingFilter::~GPUImage3x3TextureSamplingFilter()
{
    this->release();
}

bool GPUImage3x3TextureSamplingFilter::release()
{
    if(NULL != m_pFragmentShader){
        free(m_pFragmentShader);
        m_pFragmentShader = NULL;
    }
    return true;
}


bool GPUImage3x3TextureSamplingFilter::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetAttribLocation(m_uProgram, "texelHeight");

    return true;
}

bool GPUImage3x3TextureSamplingFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_3x3TextureSampling_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _3x3TextureSampling_vertex_shader);
    length = expLen;
    return true;
}

bool GPUImage3x3TextureSamplingFilter::createFragmentShader(char *fragment, int &length)
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

bool GPUImage3x3TextureSamplingFilter::beforeDrawExtra()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);
    return true;
}

bool GPUImage3x3TextureSamplingFilter::onDrawExtra()
{
    return true;
}

void GPUImage3x3TextureSamplingFilter::setTexelWidth(float texelWidth)
{
    m_fTexelWidth = texelWidth;
}

void GPUImage3x3TextureSamplingFilter::setTexelHeight(float texelHeight)
{
    m_fTexelHeight = texelHeight;
}