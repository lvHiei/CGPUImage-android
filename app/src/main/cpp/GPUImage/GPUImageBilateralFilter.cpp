/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBilateralFilter.h"


// 顶点着色器
extern const char _bilateral_vertex_shader[]= SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    const int GAUSSIAN_SAMPLES = 9;

    uniform float texelWidthOffset;
    uniform float texelHeightOffset;

    varying vec2 textureCoordinate;
    varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

    void main()
    {
        gl_Position = position;
        textureCoordinate = inputTextureCoordinate.xy;

        // Calculate the positions for the blur
        int multiplier = 0;
        vec2 blurStep;
        vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);

        for (int i = 0; i < GAUSSIAN_SAMPLES; i++)
        {
            multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
            // Blur in x (horizontal)
            blurStep = float(multiplier) * singleStepOffset;
            blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;
        }
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _bilateral_fragment_shader[]= SHADER_STR(
    uniform sampler2D inputImageTexture;

    const lowp int GAUSSIAN_SAMPLES = 9;

    varying highp vec2 textureCoordinate;
    varying highp vec2 blurCoordinates[GAUSSIAN_SAMPLES];

    uniform mediump float distanceNormalizationFactor;

    void main()
    {
        lowp vec4 centralColor;
        lowp float gaussianWeightTotal;
        lowp vec4 sum;
        lowp vec4 sampleColor;
        lowp float distanceFromCentralColor;
        lowp float gaussianWeight;

        centralColor = texture2D(inputImageTexture, blurCoordinates[4]);
        gaussianWeightTotal = 0.18;
        sum = centralColor * 0.18;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[0]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[1]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[2]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[3]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[5]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[6]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[7]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        sampleColor = texture2D(inputImageTexture, blurCoordinates[8]);
        distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
        gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
        gaussianWeightTotal += gaussianWeight;
        sum += sampleColor * gaussianWeight;

        gl_FragColor = sum / gaussianWeightTotal;
    }
);

#else


// 片元着色器
extern const char _bilateral_fragment_shader[]= SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;

 const int GAUSSIAN_SAMPLES = 9;

 varying vec2 textureCoordinate;
 varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

 uniform float distanceNormalizationFactor;

 void main()
 {
     vec4 centralColor;
     float gaussianWeightTotal;
     vec4 sum;
     vec4 sampleColor;
     float distanceFromCentralColor;
     float gaussianWeight;

     centralColor = texture2D(inputImageTexture, blurCoordinates[4]);
     gaussianWeightTotal = 0.18;
     sum = centralColor * 0.18;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[0]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[1]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[2]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[3]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[5]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[6]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[7]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     sampleColor = texture2D(inputImageTexture, blurCoordinates[8]);
     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
     gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
     gaussianWeightTotal += gaussianWeight;
     sum += sampleColor * gaussianWeight;

     gl_FragColor = sum / gaussianWeightTotal;
 }
);

#endif




GPUImageBilateralFilter::GPUImageBilateralFilter()
    : GPUImageGaussianBlurFilter()
{
    initFilter();
}


GPUImageBilateralFilter::GPUImageBilateralFilter(float blurRadiusInPixels)
    : GPUImageGaussianBlurFilter(blurRadiusInPixels)
{
    initFilter();
}


void GPUImageBilateralFilter::initFilter()
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


void GPUImageBilateralFilter::recreateFilter()
{
    this->~GPUImageBilateralFilter();
    new(this)GPUImageBilateralFilter(m_fBlurRadiusInPexels);
}

