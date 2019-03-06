/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColourFASTSamplingOperation.h"

// 顶点着色器
extern const char _colourFASTSamplingOperation_vertex_shader[] = SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;
    attribute vec4 inputTextureCoordinate2;

    uniform float texelWidth;
    uniform float texelHeight;

    varying vec2 textureCoordinate;
    varying vec2 pointATextureCoordinate;
    varying vec2 pointBTextureCoordinate;
    varying vec2 pointCTextureCoordinate;
    varying vec2 pointDTextureCoordinate;
    varying vec2 pointETextureCoordinate;
    varying vec2 pointFTextureCoordinate;
    varying vec2 pointGTextureCoordinate;
    varying vec2 pointHTextureCoordinate;

    void main()
    {
        gl_Position = position;

        float tripleTexelWidth = 3.0 * texelWidth;
        float tripleTexelHeight = 3.0 * texelHeight;

        textureCoordinate = inputTextureCoordinate.xy;

        pointATextureCoordinate = vec2(textureCoordinate.x + tripleTexelWidth, textureCoordinate.y + texelHeight);
        pointBTextureCoordinate = vec2(textureCoordinate.x + texelWidth, textureCoordinate.y + tripleTexelHeight);
        pointCTextureCoordinate = vec2(textureCoordinate.x - texelWidth, textureCoordinate.y + tripleTexelHeight);
        pointDTextureCoordinate = vec2(textureCoordinate.x - tripleTexelWidth, textureCoordinate.y + texelHeight);
        pointETextureCoordinate = vec2(textureCoordinate.x - tripleTexelWidth, textureCoordinate.y - texelHeight);
        pointFTextureCoordinate = vec2(textureCoordinate.x - texelWidth, textureCoordinate.y - tripleTexelHeight);
        pointGTextureCoordinate = vec2(textureCoordinate.x + texelWidth, textureCoordinate.y - tripleTexelHeight);
        pointHTextureCoordinate = vec2(textureCoordinate.x + tripleTexelWidth, textureCoordinate.y - texelHeight);
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _colourFASTSamplingOperation_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 textureCoordinate;
    varying vec2 pointATextureCoordinate;
    varying vec2 pointBTextureCoordinate;
    varying vec2 pointCTextureCoordinate;
    varying vec2 pointDTextureCoordinate;
    varying vec2 pointETextureCoordinate;
    varying vec2 pointFTextureCoordinate;
    varying vec2 pointGTextureCoordinate;
    varying vec2 pointHTextureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;
    const float PITwo = 6.2832;
    const float PI = 3.1416;
    void main()
    {
        vec3 centerColor = texture2D(inputImageTexture, textureCoordinate).rgb;

        vec3 pointAColor = texture2D(inputImageTexture, pointATextureCoordinate).rgb;
        vec3 pointBColor = texture2D(inputImageTexture, pointBTextureCoordinate).rgb;
        vec3 pointCColor = texture2D(inputImageTexture, pointCTextureCoordinate).rgb;
        vec3 pointDColor = texture2D(inputImageTexture, pointDTextureCoordinate).rgb;
        vec3 pointEColor = texture2D(inputImageTexture, pointETextureCoordinate).rgb;
        vec3 pointFColor = texture2D(inputImageTexture, pointFTextureCoordinate).rgb;
        vec3 pointGColor = texture2D(inputImageTexture, pointGTextureCoordinate).rgb;
        vec3 pointHColor = texture2D(inputImageTexture, pointHTextureCoordinate).rgb;

        vec3 colorComparison = ((pointAColor + pointBColor + pointCColor + pointDColor + pointEColor + pointFColor + pointGColor + pointHColor) * 0.125) - centerColor;

        // Direction calculation drawn from Appendix B of Seth Hall's Ph.D. thesis

        vec3 dirX = (pointAColor*0.94868) + (pointBColor*0.316227) - (pointCColor*0.316227) - (pointDColor*0.94868) - (pointEColor*0.94868) - (pointFColor*0.316227) + (pointGColor*0.316227) + (pointHColor*0.94868);
        vec3 dirY = (pointAColor*0.316227) + (pointBColor*0.94868) + (pointCColor*0.94868) + (pointDColor*0.316227) - (pointEColor*0.316227) - (pointFColor*0.94868) - (pointGColor*0.94868) - (pointHColor*0.316227);
        vec3 absoluteDifference = abs(colorComparison);
        float componentLength = length(colorComparison);
        float avgX = dot(absoluteDifference, dirX) / componentLength;
        float avgY = dot(absoluteDifference, dirY) / componentLength;
        float angle = atan(avgY, avgX);

        vec3 normalizedColorComparison = (colorComparison + 1.0) * 0.5;

        gl_FragColor = vec4(normalizedColorComparison, (angle+PI)/PITwo);
    }
);

#else

// 片元着色器
extern const char _colourFASTSamplingOperation_fragment_shader[] = SHADER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;
    varying vec2 pointATextureCoordinate;
    varying vec2 pointBTextureCoordinate;
    varying vec2 pointCTextureCoordinate;
    varying vec2 pointDTextureCoordinate;
    varying vec2 pointETextureCoordinate;
    varying vec2 pointFTextureCoordinate;
    varying vec2 pointGTextureCoordinate;
    varying vec2 pointHTextureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;
    const float PITwo = 6.2832;
    const float PI = 3.1416;
    void main()
    {
     vec3 centerColor = texture2D(inputImageTexture, textureCoordinate).rgb;

     vec3 pointAColor = texture2D(inputImageTexture, pointATextureCoordinate).rgb;
     vec3 pointBColor = texture2D(inputImageTexture, pointBTextureCoordinate).rgb;
     vec3 pointCColor = texture2D(inputImageTexture, pointCTextureCoordinate).rgb;
     vec3 pointDColor = texture2D(inputImageTexture, pointDTextureCoordinate).rgb;
     vec3 pointEColor = texture2D(inputImageTexture, pointETextureCoordinate).rgb;
     vec3 pointFColor = texture2D(inputImageTexture, pointFTextureCoordinate).rgb;
     vec3 pointGColor = texture2D(inputImageTexture, pointGTextureCoordinate).rgb;
     vec3 pointHColor = texture2D(inputImageTexture, pointHTextureCoordinate).rgb;

     vec3 colorComparison = ((pointAColor + pointBColor + pointCColor + pointDColor + pointEColor + pointFColor + pointGColor + pointHColor) * 0.125) - centerColor;

     // Direction calculation drawn from Appendix B of Seth Hall's Ph.D. thesis

     vec3 dirX = (pointAColor*0.94868) + (pointBColor*0.316227) - (pointCColor*0.316227) - (pointDColor*0.94868) - (pointEColor*0.94868) - (pointFColor*0.316227) + (pointGColor*0.316227) + (pointHColor*0.94868);
     vec3 dirY = (pointAColor*0.316227) + (pointBColor*0.94868) + (pointCColor*0.94868) + (pointDColor*0.316227) - (pointEColor*0.316227) - (pointFColor*0.94868) - (pointGColor*0.94868) - (pointHColor*0.316227);
     vec3 absoluteDifference = abs(colorComparison);
     float componentLength = length(colorComparison);
     float avgX = dot(absoluteDifference, dirX) / componentLength;
     float avgY = dot(absoluteDifference, dirY) / componentLength;
     float angle = atan(avgY, avgX);

     vec3 normalizedColorComparison = (colorComparison + 1.0) * 0.5;

     gl_FragColor = vec4(normalizedColorComparison, (angle+PI)/PITwo);
    }
);

#endif





GPUImageColourFASTSamplingOperation::GPUImageColourFASTSamplingOperation()
        : GPUImageTwoInputFilter(_colourFASTSamplingOperation_vertex_shader, _colourFASTSamplingOperation_fragment_shader)
{
    updateTexelWidthHeight();
    m_iTexelWidthUniformLocation = -1;
    m_iTexelHeightUniformLocation = -1;

}

GPUImageColourFASTSamplingOperation::~GPUImageColourFASTSamplingOperation()
{

}

bool GPUImageColourFASTSamplingOperation::createProgramExtra()
{
    m_iTexelWidthUniformLocation = glGetUniformLocation(m_uProgram, "texelWidth");
    m_iTexelHeightUniformLocation = glGetUniformLocation(m_uProgram, "texelHeight");

    return true;
}

bool GPUImageColourFASTSamplingOperation::beforeDrawExtra()
{
    glUniform1f(m_iTexelWidthUniformLocation, m_fTexelWidth);
    glUniform1f(m_iTexelHeightUniformLocation, m_fTexelHeight);

    return true;
}

void GPUImageColourFASTSamplingOperation::setTexelWidth(float width)
{
    m_fTexelWidth = width;
}

void GPUImageColourFASTSamplingOperation::setTexelHeight(float height)
{
    m_fTexelHeight = height;
}


void GPUImageColourFASTSamplingOperation::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageColourFASTSamplingOperation::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}

void GPUImageColourFASTSamplingOperation::updateTexelWidthHeight()
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

