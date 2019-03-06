/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTwoInputCrossTextureSamplingFilter.h"


// 顶点着色器
extern const char _twoInputNearbyTexelSamplling_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;
    attribute vec4 inputTextureCoordinate2;

    uniform float texelWidth;
    uniform float texelHeight;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;
    varying vec2 topTextureCoordinate;
    varying vec2 bottomTextureCoordinate;

    varying vec2 textureCoordinate2;
    varying vec2 leftTextureCoordinate2;
    varying vec2 rightTextureCoordinate2;
    varying vec2 topTextureCoordinate2;
    varying vec2 bottomTextureCoordinate2;

    void main()
    {
        gl_Position = position;

        vec2 widthStep = vec2(texelWidth, 0.0);
        vec2 heightStep = vec2(0.0, texelHeight);

        textureCoordinate = inputTextureCoordinate.xy;
        leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;
        rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;
        topTextureCoordinate = inputTextureCoordinate.xy - heightStep;
        bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;

        textureCoordinate2 = inputTextureCoordinate2.xy;
        leftTextureCoordinate2 = inputTextureCoordinate2.xy - widthStep;
        rightTextureCoordinate2 = inputTextureCoordinate2.xy + widthStep;
        topTextureCoordinate2 = inputTextureCoordinate2.xy - heightStep;
        bottomTextureCoordinate2 = inputTextureCoordinate2.xy + heightStep;
    }
);


GPUImageTwoInputCrossTextureSamplingFilter::GPUImageTwoInputCrossTextureSamplingFilter(const char *fragment)
    : GPUImageTwoInputFilter(_twoInputNearbyTexelSamplling_vertex_shader, fragment)
{
    intenalInit();
}

GPUImageTwoInputCrossTextureSamplingFilter::GPUImageTwoInputCrossTextureSamplingFilter(const char *vertex, const char *fragment)
    : GPUImageTwoInputFilter(vertex, fragment)
{
    intenalInit();
}

GPUImageTwoInputCrossTextureSamplingFilter::~GPUImageTwoInputCrossTextureSamplingFilter()
{

}

void GPUImageTwoInputCrossTextureSamplingFilter::setTexelWidth(float texelWidth)
{
    m_fTexelWidth = texelWidth;
}

void GPUImageTwoInputCrossTextureSamplingFilter::setTexelHeight(float texelHeight)
{
    m_fTexelHeight = texelHeight;
}

bool GPUImageTwoInputCrossTextureSamplingFilter::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uProgram, "texelHeight");
    return GPUImageTwoInputFilter::createProgramExtra();
}

bool GPUImageTwoInputCrossTextureSamplingFilter::beforeDrawExtra()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);
    return GPUImageTwoInputFilter::beforeDrawExtra();
}

void GPUImageTwoInputCrossTextureSamplingFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageTwoInputCrossTextureSamplingFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}

void GPUImageTwoInputCrossTextureSamplingFilter::updateTexelWidthHeight()
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


void GPUImageTwoInputCrossTextureSamplingFilter::intenalInit()
{
    updateTexelWidthHeight();

    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;
}




