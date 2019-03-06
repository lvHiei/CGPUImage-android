/**
 * Created by lvHiei on 17-4-17.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSobelEdgeDetectionFilter.h"


extern const char _base_vertex_shader[];
extern const char _greyScale_fragment_shader[];
extern const char _3x3TextureSampling_vertex_shader[];


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _sobelEdgeDetection_fragment_shader[] = SHADER_STR(
    precision mediump float;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform float edgeStrength;

    void main()
    {
        float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
        float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
        float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
        float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
        float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
        float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

        float mag = length(vec2(h, v)) * edgeStrength;

        gl_FragColor = vec4(vec3(mag), 1.0);
    }
);


#else


// 片元着色器
extern const char _sobelEdgeDetection_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float edgeStrength;

 void main()
 {
     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
     float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

     float mag = length(vec2(h, v)) * edgeStrength;

     gl_FragColor = vec4(vec3(mag), 1.0);
 }
);


#endif



GPUImageSobelEdgeDetectionFilter::GPUImageSobelEdgeDetectionFilter()
    : GPUImageTwoPassFilter(_base_vertex_shader, _greyScale_fragment_shader, _3x3TextureSampling_vertex_shader, _sobelEdgeDetection_fragment_shader)
{
    updateTexelWidthHeight();

    m_fEdgeStrength = 1.0f;

    m_iEdgeStrengthUniformLocation = -1;
    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;
}

GPUImageSobelEdgeDetectionFilter::GPUImageSobelEdgeDetectionFilter(const char *fragment)
    : GPUImageTwoPassFilter(_base_vertex_shader, _greyScale_fragment_shader, _3x3TextureSampling_vertex_shader, fragment)
{
    updateTexelWidthHeight();

    m_fEdgeStrength = 1.0f;

    m_iEdgeStrengthUniformLocation = -1;
    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;
}

GPUImageSobelEdgeDetectionFilter::~GPUImageSobelEdgeDetectionFilter()
{

}

bool GPUImageSobelEdgeDetectionFilter::secondCreateProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uSecondProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uSecondProgram, "texelHeight");
    m_iEdgeStrengthUniformLocation = glGetUniformLocation(m_uSecondProgram, "edgeStrength");

    return GPUImageTwoPassFilter::secondCreateProgramExtra();
}

bool GPUImageSobelEdgeDetectionFilter::secondBeforeDraw()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);
    glUniform1f(m_iEdgeStrengthUniformLocation, m_fEdgeStrength);

    return GPUImageTwoPassFilter::secondBeforeDraw();
}

void GPUImageSobelEdgeDetectionFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageSobelEdgeDetectionFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}


void GPUImageSobelEdgeDetectionFilter::setTexelWidth(float texelWidth)
{
    m_fTexelWidth = texelWidth;
}

void GPUImageSobelEdgeDetectionFilter::setTexelHeight(float texelHeight)
{
    m_fTexelHeight = texelHeight;
}


void GPUImageSobelEdgeDetectionFilter::setEdgeStrength(float edgeStrength)
{
    m_fEdgeStrength = edgeStrength;
}


void GPUImageSobelEdgeDetectionFilter::updateTexelWidthHeight()
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

