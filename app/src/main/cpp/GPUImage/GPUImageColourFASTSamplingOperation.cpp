/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColourFASTSamplingOperation.h"

// 顶点着色器
const char _colourFASTSamplingOperation_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"attribute vec4 inputTextureCoordinate2;\n"
"\n"
"uniform float texelWidth;\n"
"uniform float texelHeight;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 pointATextureCoordinate;\n"
"varying vec2 pointBTextureCoordinate;\n"
"varying vec2 pointCTextureCoordinate;\n"
"varying vec2 pointDTextureCoordinate;\n"
"varying vec2 pointETextureCoordinate;\n"
"varying vec2 pointFTextureCoordinate;\n"
"varying vec2 pointGTextureCoordinate;\n"
"varying vec2 pointHTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    float tripleTexelWidth = 3.0 * texelWidth;\n"
"    float tripleTexelHeight = 3.0 * texelHeight;\n"
"\n"
"    textureCoordinate = inputTextureCoordinate.xy;\n"
"\n"
"    pointATextureCoordinate = vec2(textureCoordinate.x + tripleTexelWidth, textureCoordinate.y + texelHeight);\n"
"    pointBTextureCoordinate = vec2(textureCoordinate.x + texelWidth, textureCoordinate.y + tripleTexelHeight);\n"
"    pointCTextureCoordinate = vec2(textureCoordinate.x - texelWidth, textureCoordinate.y + tripleTexelHeight);\n"
"    pointDTextureCoordinate = vec2(textureCoordinate.x - tripleTexelWidth, textureCoordinate.y + texelHeight);\n"
"    pointETextureCoordinate = vec2(textureCoordinate.x - tripleTexelWidth, textureCoordinate.y - texelHeight);\n"
"    pointFTextureCoordinate = vec2(textureCoordinate.x - texelWidth, textureCoordinate.y - tripleTexelHeight);\n"
"    pointGTextureCoordinate = vec2(textureCoordinate.x + texelWidth, textureCoordinate.y - tripleTexelHeight);\n"
"    pointHTextureCoordinate = vec2(textureCoordinate.x + tripleTexelWidth, textureCoordinate.y - texelHeight);\n"
"}"
;

// 片元着色器
const char _colourFASTSamplingOperation_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 pointATextureCoordinate;\n"
"varying vec2 pointBTextureCoordinate;\n"
"varying vec2 pointCTextureCoordinate;\n"
"varying vec2 pointDTextureCoordinate;\n"
"varying vec2 pointETextureCoordinate;\n"
"varying vec2 pointFTextureCoordinate;\n"
"varying vec2 pointGTextureCoordinate;\n"
"varying vec2 pointHTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"const float PITwo = 6.2832;\n"
"const float PI = 3.1416;\n"
"void main()\n"
"{\n"
"    vec3 centerColor = texture2D(inputImageTexture, textureCoordinate).rgb;\n"
"\n"
"    vec3 pointAColor = texture2D(inputImageTexture, pointATextureCoordinate).rgb;\n"
"    vec3 pointBColor = texture2D(inputImageTexture, pointBTextureCoordinate).rgb;\n"
"    vec3 pointCColor = texture2D(inputImageTexture, pointCTextureCoordinate).rgb;\n"
"    vec3 pointDColor = texture2D(inputImageTexture, pointDTextureCoordinate).rgb;\n"
"    vec3 pointEColor = texture2D(inputImageTexture, pointETextureCoordinate).rgb;\n"
"    vec3 pointFColor = texture2D(inputImageTexture, pointFTextureCoordinate).rgb;\n"
"    vec3 pointGColor = texture2D(inputImageTexture, pointGTextureCoordinate).rgb;\n"
"    vec3 pointHColor = texture2D(inputImageTexture, pointHTextureCoordinate).rgb;\n"
"\n"
"    vec3 colorComparison = ((pointAColor + pointBColor + pointCColor + pointDColor + pointEColor + pointFColor + pointGColor + pointHColor) * 0.125) - centerColor;\n"
"\n"
"    // Direction calculation drawn from Appendix B of Seth Hall's Ph.D. thesis\n"
"\n"
"    vec3 dirX = (pointAColor*0.94868) + (pointBColor*0.316227) - (pointCColor*0.316227) - (pointDColor*0.94868) - (pointEColor*0.94868) - (pointFColor*0.316227) + (pointGColor*0.316227) + (pointHColor*0.94868);\n"
"    vec3 dirY = (pointAColor*0.316227) + (pointBColor*0.94868) + (pointCColor*0.94868) + (pointDColor*0.316227) - (pointEColor*0.316227) - (pointFColor*0.94868) - (pointGColor*0.94868) - (pointHColor*0.316227);\n"
"    vec3 absoluteDifference = abs(colorComparison);\n"
"    float componentLength = length(colorComparison);\n"
"    float avgX = dot(absoluteDifference, dirX) / componentLength;\n"
"    float avgY = dot(absoluteDifference, dirY) / componentLength;\n"
"    float angle = atan(avgY, avgX);\n"
"\n"
"    vec3 normalizedColorComparison = (colorComparison + 1.0) * 0.5;\n"
"\n"
"    gl_FragColor = vec4(normalizedColorComparison, (angle+PI)/PITwo);\n"
"}"
;

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

