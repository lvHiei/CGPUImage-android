/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageDirectionalNonMaximumSuppressionFilter.h"

// 片元着色器
extern const char _directionalNonMaximumSuppression_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float texelWidth;\n"
"uniform float texelHeight;\n"
"uniform float upperThreshold;\n"
"uniform float lowerThreshold;\n"
"\n"
"void main()\n"
"{\n"
"    vec3 currentGradientAndDirection = texture2D(inputImageTexture, textureCoordinate).rgb;\n"
"    vec2 gradientDirection = ((currentGradientAndDirection.gb * 2.0) - 1.0) * vec2(texelWidth, texelHeight);\n"
"\n"
"    float firstSampledGradientMagnitude = texture2D(inputImageTexture, textureCoordinate + gradientDirection).r;\n"
"    float secondSampledGradientMagnitude = texture2D(inputImageTexture, textureCoordinate - gradientDirection).r;\n"
"\n"
"    float multiplier = step(firstSampledGradientMagnitude, currentGradientAndDirection.r);\n"
"    multiplier = multiplier * step(secondSampledGradientMagnitude, currentGradientAndDirection.r);\n"
"\n"
"    float thresholdCompliance = smoothstep(lowerThreshold, upperThreshold, currentGradientAndDirection.r);\n"
"    multiplier = multiplier * thresholdCompliance;\n"
"\n"
"    gl_FragColor = vec4(multiplier, multiplier, multiplier, 1.0);\n"
"}"
;



GPUImageDirectionalNonMaximumSuppressionFilter::GPUImageDirectionalNonMaximumSuppressionFilter()
        : GPUImageFilter(_directionalNonMaximumSuppression_fragment_shader)
{

    updateTexelWidthHeight();
    m_fUpperThreshold = 0.5f;
    m_fLowerThreshold = 0.1f;

    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;

    m_iUpperThresholdUniformLocation = -1;
    m_iLowerThresholdUniformLocation = -1;
}

GPUImageDirectionalNonMaximumSuppressionFilter::~GPUImageDirectionalNonMaximumSuppressionFilter()
{

}

bool GPUImageDirectionalNonMaximumSuppressionFilter::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uProgram, "texelHeight");

    m_iUpperThresholdUniformLocation = glGetUniformLocation(m_uProgram, "upperThreshold");
    m_iLowerThresholdUniformLocation = glGetUniformLocation(m_uProgram, "lowerThreshold");

    return true;
}

bool GPUImageDirectionalNonMaximumSuppressionFilter::beforeDrawExtra()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);

    glUniform1f(m_iUpperThresholdUniformLocation, m_fUpperThreshold);
    glUniform1f(m_iLowerThresholdUniformLocation, m_fLowerThreshold);

    return true;
}

void GPUImageDirectionalNonMaximumSuppressionFilter::setTexelWidth(float width)
{
    m_fTexelWidth = width;
}

void GPUImageDirectionalNonMaximumSuppressionFilter::setTexelHeight(float height)
{
    m_fTexelHeight = height;
}

void GPUImageDirectionalNonMaximumSuppressionFilter::setUpperThreshold(float upperThreshold)
{
    m_fUpperThreshold = upperThreshold;
}

void GPUImageDirectionalNonMaximumSuppressionFilter::setLowerThreshold(float lowerThreshold)
{
    m_fLowerThreshold = lowerThreshold;
}


void GPUImageDirectionalNonMaximumSuppressionFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageDirectionalNonMaximumSuppressionFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}

void GPUImageDirectionalNonMaximumSuppressionFilter::updateTexelWidthHeight()
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

