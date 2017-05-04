/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBilateralFilter.h"


// 顶点着色器
extern const char _bilateral_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"const int GAUSSIAN_SAMPLES = 9;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
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
"    for (int i = 0; i < GAUSSIAN_SAMPLES; i++)\n"
"    {\n"
"        multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));\n"
"        // Blur in x (horizontal)\n"
"        blurStep = float(multiplier) * singleStepOffset;\n"
"        blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;\n"
"    }\n"
"}"
;

// 片元着色器
extern const char _bilateral_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"const int GAUSSIAN_SAMPLES = 9;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n"
"\n"
"uniform float distanceNormalizationFactor;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 centralColor;\n"
"    float gaussianWeightTotal;\n"
"    vec4 sum;\n"
"    vec4 sampleColor;\n"
"    float distanceFromCentralColor;\n"
"    float gaussianWeight;\n"
"\n"
"    centralColor = texture2D(inputImageTexture, blurCoordinates[4]);\n"
"    gaussianWeightTotal = 0.18;\n"
"    sum = centralColor * 0.18;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[0]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[1]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[2]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[3]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[5]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[6]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[7]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    sampleColor = texture2D(inputImageTexture, blurCoordinates[8]);\n"
"    distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n"
"    gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);\n"
"    gaussianWeightTotal += gaussianWeight;\n"
"    sum += sampleColor * gaussianWeight;\n"
"\n"
"    gl_FragColor = sum / gaussianWeightTotal;\n"
"}"
;


GPUImageBilateralFilter::GPUImageBilateralFilter()
    : GPUImageGaussianBlurFilter()
{

    m_fTexelSpacingMutiplier = 4.0f;

    m_fDistanceNormalizationFactor = 8.0f;

    m_iFirstDistanceNormalizationFactorUniformLocation = -1;
    m_iSecondDistanceNormalizationFactorUniformLocation = -1;

    resetShader(_bilateral_vertex_shader, _bilateral_fragment_shader, _bilateral_vertex_shader, _bilateral_fragment_shader);
}

GPUImageBilateralFilter::~GPUImageBilateralFilter()
{

}

void GPUImageBilateralFilter::setDistanceNormalizationFactor(float distanceNormalizationFactor)
{
    m_fDistanceNormalizationFactor = distanceNormalizationFactor;
}

bool GPUImageBilateralFilter::firstCreateProgramExtra()
{
    m_iFirstDistanceNormalizationFactorUniformLocation = glGetUniformLocation(m_uProgram, "distanceNormalizationFactor");
    return GPUImageTwoPassTextureSamplingFilter::firstCreateProgramExtra();
}

bool GPUImageBilateralFilter::secondCreateProgramExtra()
{
    m_iSecondDistanceNormalizationFactorUniformLocation = glGetUniformLocation(m_uSecondProgram, "distanceNormalizationFactor");
    return GPUImageTwoPassTextureSamplingFilter::secondCreateProgramExtra();
}

bool GPUImageBilateralFilter::firstBeforeDraw()
{
    glUniform1f(m_iFirstDistanceNormalizationFactorUniformLocation, m_fDistanceNormalizationFactor);
    return GPUImageTwoPassTextureSamplingFilter::firstBeforeDraw();
}

bool GPUImageBilateralFilter::secondBeforeDraw()
{
    glUniform1f(m_iSecondDistanceNormalizationFactorUniformLocation, m_fDistanceNormalizationFactor);
    return GPUImageTwoPassTextureSamplingFilter::secondBeforeDraw();
}

