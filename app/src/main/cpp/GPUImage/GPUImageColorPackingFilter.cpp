/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorPackingFilter.h"

// 顶点着色器
extern const char _colorPacking_vertex_shader[] = SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    uniform float texelWidth;
    uniform float texelHeight;

    varying vec2 upperLeftInputTextureCoordinate;
    varying vec2 upperRightInputTextureCoordinate;
    varying vec2 lowerLeftInputTextureCoordinate;
    varying vec2 lowerRightInputTextureCoordinate;

    void main()
    {
        gl_Position = position;

        upperLeftInputTextureCoordinate = inputTextureCoordinate.xy + vec2(-texelWidth, -texelHeight);
        upperRightInputTextureCoordinate = inputTextureCoordinate.xy + vec2(texelWidth, -texelHeight);
        lowerLeftInputTextureCoordinate = inputTextureCoordinate.xy + vec2(-texelWidth, texelHeight);
        lowerRightInputTextureCoordinate = inputTextureCoordinate.xy + vec2(texelWidth, texelHeight);
    }
);


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _colorPacking_fragment_shader[] = SHADER_STR(
    precision lowp float;

    uniform sampler2D inputImageTexture;

    uniform mediump mat3 convolutionMatrix;

    varying highp vec2 outputTextureCoordinate;

    varying highp vec2 upperLeftInputTextureCoordinate;
    varying highp vec2 upperRightInputTextureCoordinate;
    varying highp vec2 lowerLeftInputTextureCoordinate;
    varying highp vec2 lowerRightInputTextureCoordinate;

    void main()
    {
        float upperLeftIntensity = texture2D(inputImageTexture, upperLeftInputTextureCoordinate).r;
        float upperRightIntensity = texture2D(inputImageTexture, upperRightInputTextureCoordinate).r;
        float lowerLeftIntensity = texture2D(inputImageTexture, lowerLeftInputTextureCoordinate).r;
        float lowerRightIntensity = texture2D(inputImageTexture, lowerRightInputTextureCoordinate).r;

        gl_FragColor = vec4(upperLeftIntensity, upperRightIntensity, lowerLeftIntensity, lowerRightIntensity);
    }
);


#else

// 片元着色器
extern const char _colorPacking_fragment_shader[]=SHADER_STR(
    precision mediump float;
    uniform sampler2D inputImageTexture;

    uniform mat3 convolutionMatrix;

    varying vec2 outputTextureCoordinate;

    varying vec2 upperLeftInputTextureCoordinate;
    varying vec2 upperRightInputTextureCoordinate;
    varying vec2 lowerLeftInputTextureCoordinate;
    varying vec2 lowerRightInputTextureCoordinate;

    void main()
    {
     float upperLeftIntensity = texture2D(inputImageTexture, upperLeftInputTextureCoordinate).r;
     float upperRightIntensity = texture2D(inputImageTexture, upperRightInputTextureCoordinate).r;
     float lowerLeftIntensity = texture2D(inputImageTexture, lowerLeftInputTextureCoordinate).r;
     float lowerRightIntensity = texture2D(inputImageTexture, lowerRightInputTextureCoordinate).r;

     gl_FragColor = vec4(upperLeftIntensity, upperRightIntensity, lowerLeftIntensity, lowerRightIntensity);
    }
);


#endif


GPUImageColorPackingFilter::GPUImageColorPackingFilter()
    : GPUImageFilter(_colorPacking_vertex_shader, _colorPacking_fragment_shader)
{
    updateTexelWidthHeight();

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


void GPUImageColorPackingFilter::setTextureSize(int width, int height) {
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageColorPackingFilter::setTextureRotation(Rotation rotation) {
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}

void GPUImageColorPackingFilter::updateTexelWidthHeight()
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

