/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorPackingFilter.h"


// 顶点着色器
const char _colorPacking_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidth;\n"
"uniform float texelHeight;\n"
"\n"
"varying vec2 upperLeftInputTextureCoordinate;\n"
"varying vec2 upperRightInputTextureCoordinate;\n"
"varying vec2 lowerLeftInputTextureCoordinate;\n"
"varying vec2 lowerRightInputTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    upperLeftInputTextureCoordinate = inputTextureCoordinate.xy + vec2(-texelWidth, -texelHeight);\n"
"    upperRightInputTextureCoordinate = inputTextureCoordinate.xy + vec2(texelWidth, -texelHeight);\n"
"    lowerLeftInputTextureCoordinate = inputTextureCoordinate.xy + vec2(-texelWidth, texelHeight);\n"
"    lowerRightInputTextureCoordinate = inputTextureCoordinate.xy + vec2(texelWidth, texelHeight);\n"
"}"
;

// 片元着色器
const char _colorPacking_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform mat3 convolutionMatrix;\n"
"\n"
"varying vec2 outputTextureCoordinate;\n"
"\n"
"varying vec2 upperLeftInputTextureCoordinate;\n"
"varying vec2 upperRightInputTextureCoordinate;\n"
"varying vec2 lowerLeftInputTextureCoordinate;\n"
"varying vec2 lowerRightInputTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    float upperLeftIntensity = texture2D(inputImageTexture, upperLeftInputTextureCoordinate).r;\n"
"    float upperRightIntensity = texture2D(inputImageTexture, upperRightInputTextureCoordinate).r;\n"
"    float lowerLeftIntensity = texture2D(inputImageTexture, lowerLeftInputTextureCoordinate).r;\n"
"    float lowerRightIntensity = texture2D(inputImageTexture, lowerRightInputTextureCoordinate).r;\n"
"\n"
"    gl_FragColor = vec4(upperLeftIntensity, upperRightIntensity, lowerLeftIntensity, lowerRightIntensity);\n"
"}"
;


GPUImageColorPackingFilter::GPUImageColorPackingFilter()
    : GPUImageFilter(_colorPacking_vertex_shader, _colorPacking_fragment_shader)
{
    m_fTexelWidth = 1.0 / 1280;
    m_fTexelHeight = 1.0 / 720;

    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;

}

GPUImageColorPackingFilter::~GPUImageColorPackingFilter()
{

}

bool GPUImageColorPackingFilter::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uProgram, "texelHeight");

    return true;
}

bool GPUImageColorPackingFilter::beforeDrawExtra()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);

    return true;
}

void GPUImageColorPackingFilter::setTexelWidth(float width)
{
    m_fTexelWidth = width;
}

void GPUImageColorPackingFilter::setTexelHeight(float height)
{
    m_fTexelHeight = height;
}