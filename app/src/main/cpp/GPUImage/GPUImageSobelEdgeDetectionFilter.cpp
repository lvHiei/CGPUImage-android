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
extern const char _sobelEdgeDetection_fragment_shader[]=
"precision mediump float;\n"
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
"uniform sampler2D inputImageTexture;\n"
"uniform float edgeStrength;\n"
"\n"
"void main()\n"
"{\n"
"    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"\n"
"    float mag = length(vec2(h, v)) * edgeStrength;\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;


#else


// 片元着色器
extern const char _sobelEdgeDetection_fragment_shader[]=
"precision mediump float;\n"
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
"uniform sampler2D inputImageTexture;\n"
"uniform float edgeStrength;\n"
"\n"
"void main()\n"
"{\n"
"    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"\n"
"    float mag = length(vec2(h, v)) * edgeStrength;\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;


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

