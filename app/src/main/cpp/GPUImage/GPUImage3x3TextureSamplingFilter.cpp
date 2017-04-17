/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImage3x3TextureSamplingFilter.h"

// 顶点着色器
extern const char _3x3TextureSampling_vertex_shader[]=
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
    : GPUImageFilter(_3x3TextureSampling_vertex_shader, fragment)
{
    updateTexelWidthHeight();

    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;
}


GPUImage3x3TextureSamplingFilter::~GPUImage3x3TextureSamplingFilter()
{
    this->release();
}

bool GPUImage3x3TextureSamplingFilter::release()
{

    return true;
}


bool GPUImage3x3TextureSamplingFilter::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uProgram, "texelHeight");

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

void GPUImage3x3TextureSamplingFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImage3x3TextureSamplingFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}


void GPUImage3x3TextureSamplingFilter::updateTexelWidthHeight()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fTexelWidth = 1.0 / m_iTextureWidth;
    m_fTexelHeight = 1.0 / m_iTextureHeight;
}

