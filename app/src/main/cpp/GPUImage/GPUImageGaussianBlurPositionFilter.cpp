/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGaussianBlurPositionFilter.h"



// 顶点着色器
extern const char _gaussianBlurPosition_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"const int GAUSSIAN_SAMPLES = 9;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"    textureCoordinate = inputTextureCoordinate.xy;\n"
"\n"
"    // Calculate the positions for the blur\n"
"    int multiplier = 0;\n"
"    vec2 blurStep;\n"
"    vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n"
"\n"
"    for (int i = 0; i < GAUSSIAN_SAMPLES; i++) {\n"
"        multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));\n"
"        // Blur in x (horizontal)\n"
"        blurStep = float(multiplier) * singleStepOffset;\n"
"        blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;\n"
"    }\n"
"}"
;

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _gaussianBlurPosition_fragment_shader[]=
"uniform sampler2D inputImageTexture;\n"
"\n"
"const lowp int GAUSSIAN_SAMPLES = 9;\n"
"\n"
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n"
"\n"
"uniform highp float aspectRatio;\n"
"uniform lowp vec2 blurCenter;\n"
"uniform highp float blurRadius;\n"
"\n"
"void main() {\n"
"    highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp float dist = distance(blurCenter, textureCoordinateToUse);\n"
"\n"
"    if (dist < blurRadius)\n"
"    {\n"
"        lowp vec4 sum = vec4(0.0);\n"
"\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[0]) * 0.05;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[1]) * 0.09;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[2]) * 0.12;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[3]) * 0.15;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[4]) * 0.18;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[5]) * 0.15;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[6]) * 0.12;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[7]) * 0.09;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[8]) * 0.05;\n"
"\n"
"        gl_FragColor = sum;\n"
"    }\n"
"    else\n"
"    {\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    }\n"
"}"
;

#else

// 片元着色器
extern const char _gaussianBlurPosition_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"const int GAUSSIAN_SAMPLES = 9;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n"
"\n"
"uniform float aspectRatio;\n"
"uniform vec2 blurCenter;\n"
"uniform float blurRadius;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    float dist = distance(blurCenter, textureCoordinateToUse);\n"
"\n"
"    if (dist < blurRadius)\n"
"    {\n"
"        vec4 sum = vec4(0.0);\n"
"\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[0]) * 0.05;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[1]) * 0.09;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[2]) * 0.12;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[3]) * 0.15;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[4]) * 0.18;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[5]) * 0.15;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[6]) * 0.12;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[7]) * 0.09;\n"
"        sum += texture2D(inputImageTexture, blurCoordinates[8]) * 0.05;\n"
"\n"
"        gl_FragColor = sum;\n"
"    }\n"
"    else\n"
"    {\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    }\n"
"}"
;

#endif





GPUImageGaussianBlurPositionFilter::GPUImageGaussianBlurPositionFilter()
    : GPUImageTwoPassTextureSamplingFilter(_gaussianBlurPosition_vertex_shader, _gaussianBlurPosition_fragment_shader, _gaussianBlurPosition_vertex_shader, _gaussianBlurPosition_fragment_shader)
{
    m_fBlurSize = 1.0f;
    m_fBlurRadius = 40.0f/320.0f;
//    m_fBlurRadius = 0.75f;
//    m_fBlurRadius = 1.0f;

    m_pBlurCenter[0] = 0.5f;
    m_pBlurCenter[1] = 0.5f;

    m_iBlurCenterUniformLocation = -1;
    m_iBlurRadiusUniformLocation = -1;
    m_iBlurSizeUniformLocation = -1;
    m_iAspectRatioUniformLocation = -1;
}

GPUImageGaussianBlurPositionFilter::~GPUImageGaussianBlurPositionFilter()
{

}

void GPUImageGaussianBlurPositionFilter::setAspectRatio(float aspectRatio)
{
    m_fAspectRatio = aspectRatio;
}

void GPUImageGaussianBlurPositionFilter::setBlurSize(float blurSize)
{
    m_fBlurSize = blurSize;
    m_f_verticalTexelSpacing = m_fBlurSize;
    m_f_horizontalTexelSpacing = m_fBlurSize;
}

void GPUImageGaussianBlurPositionFilter::setBlurCenter(float x, float y)
{
    m_pBlurCenter[0] = x;
    m_pBlurCenter[1] = y;
}

void GPUImageGaussianBlurPositionFilter::setBlurRadius(float radius)
{
    m_fBlurRadius = radius;
}

void GPUImageGaussianBlurPositionFilter::setTextureSize(int width, int height)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureSize(width, height);
    updateAspectRatio();
}

void GPUImageGaussianBlurPositionFilter::setTextureRotation(Rotation rotation)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureRotation(rotation);
    updateAspectRatio();
}

void GPUImageGaussianBlurPositionFilter::updateAspectRatio()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fAspectRatio = isRotationSwapWidthAndHeight() ?
                     1.0 * m_iTextureHeight / m_iTextureWidth :
                     1.0 * m_iTextureWidth / m_iTextureHeight;
}


bool GPUImageGaussianBlurPositionFilter::secondCreateProgramExtra()
{
    m_iAspectRatioUniformLocation = glGetUniformLocation(m_uSecondProgram, "aspectRatio");
    m_iBlurCenterUniformLocation = glGetUniformLocation(m_uSecondProgram, "blurCenter");
    m_iBlurRadiusUniformLocation = glGetUniformLocation(m_uSecondProgram, "blurRadius");
    return GPUImageTwoPassTextureSamplingFilter::secondCreateProgramExtra();
}

bool GPUImageGaussianBlurPositionFilter::secondBeforeDraw()
{
    glUniform1f(m_iAspectRatioUniformLocation, m_fAspectRatio);
    glUniform1f(m_iBlurRadiusUniformLocation, m_fBlurRadius);
    glUniform2fv(m_iBlurCenterUniformLocation, 1, m_pBlurCenter);
    return GPUImageTwoPassTextureSamplingFilter::secondBeforeDraw();
}

