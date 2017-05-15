/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageSingleComponentGaussianBlurFilter.h"


GPUImageSingleComponentGaussianBlurFilter::GPUImageSingleComponentGaussianBlurFilter()
    : GPUImageGaussianBlurFilter()
{
    initWithBlurSigma(4, 2.0);
}

GPUImageSingleComponentGaussianBlurFilter::GPUImageSingleComponentGaussianBlurFilter(
        float blurRadiusInPixels)
    : GPUImageGaussianBlurFilter(blurRadiusInPixels)
{
    m_fBlurRadiusInPexels = round(blurRadiusInPixels);

    int calculatedSampleRadius = 0;
    if(m_fBlurRadiusInPexels >= 1.0f){
        // Calculate the number of pixels to sample from by setting a bottom limit for the contribution of the outermost pixel
        float minimumWeightToFindEdgeOfSamplingArea = 1.0/256.0;
        calculatedSampleRadius = floor(sqrt(-2.0 * pow(m_fBlurRadiusInPexels, 2.0) * log(minimumWeightToFindEdgeOfSamplingArea * sqrt(2.0 * M_PI * pow(m_fBlurRadiusInPexels, 2.0))) ));
        calculatedSampleRadius += calculatedSampleRadius % 2; // There's nothing to gain from handling odd radius sizes, due to the optimizations I use
    }

    initWithBlurSigma(calculatedSampleRadius, m_fBlurRadiusInPexels);
}


GPUImageSingleComponentGaussianBlurFilter::~GPUImageSingleComponentGaussianBlurFilter()
{

}

void GPUImageSingleComponentGaussianBlurFilter::genVertexShaderForOptimizedBlurOfRadius(
        int blurRadius, float sigma)
{
    if(blurRadius < 1){
        GPUImageGaussianBlurFilter::genVertexShaderForOptimizedBlurOfRadius(blurRadius, sigma);
        return;
    }

    // First, generate the normal Gaussian weights for a given sigma
    GLfloat *standardGaussianWeights = (GLfloat *) malloc((blurRadius + 1) * sizeof(GLfloat));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));

        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    // Next, normalize these weights to prevent the clipping of the Gaussian curve at the end of the discrete samples from reducing luminance
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }

    // From these weights we calculate the offsets to read interpolated values from
    int curOffset = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = curOffset > 7 ? 7 : curOffset;
    GLfloat *optimizedGaussianOffsets = (GLfloat *) malloc(numberOfOptimizedOffsets * sizeof(GLfloat));

    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        GLfloat firstWeight = standardGaussianWeights[currentOptimizedOffset*2 + 1];
        GLfloat secondWeight = standardGaussianWeights[currentOptimizedOffset*2 + 2];

        GLfloat optimizedWeight = firstWeight + secondWeight;

        optimizedGaussianOffsets[currentOptimizedOffset] = (firstWeight * (currentOptimizedOffset*2 + 1) + secondWeight * (currentOptimizedOffset*2 + 2)) / optimizedWeight;
    }

    char tempShader[20480] = {0};
    const char* part1 =
    "attribute vec4 position;\n"
    "attribute vec4 inputTextureCoordinate;\n"
    "\n"
    "uniform float texelWidthOffset;\n"
    "uniform float texelHeightOffset;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = position;\n"
    "\n"
    "    vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n"
    ;


    sprintf(tempShader + strlen(tempShader), part1, 1 + (numberOfOptimizedOffsets * 2));

    // Inner offset loop
    sprintf(tempShader + strlen(tempShader), "blurCoordinates[0] = inputTextureCoordinate.xy;\n");
    const char* part2 =
    "   blurCoordinates[%d] = inputTextureCoordinate.xy + singleStepOffset * %f;\n"
    "   blurCoordinates[%d] = inputTextureCoordinate.xy - singleStepOffset * %f;\n"
    ;
    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        sprintf(tempShader + strlen(tempShader), part2, (currentOptimizedOffset * 2) + 1, optimizedGaussianOffsets[currentOptimizedOffset], (currentOptimizedOffset * 2) + 2, optimizedGaussianOffsets[currentOptimizedOffset]);
    }

    // Footer
    sprintf(tempShader + strlen(tempShader), "}\n");

    free(optimizedGaussianOffsets);
    free(standardGaussianWeights);


    resetFirstVertexShader(tempShader);
    resetSecondVertexShader(tempShader);
}

void GPUImageSingleComponentGaussianBlurFilter::genFragmentShaderForOptimizedBlurOfRadius(
        int blurRadius, float sigma)
{
    if(blurRadius < 1){
        GPUImageGaussianBlurFilter::genFragmentShaderForOptimizedBlurOfRadius(blurRadius, sigma);
        return;
    }

    // First, generate the normal Gaussian weights for a given sigma
    GLfloat *standardGaussianWeights = (GLfloat *) malloc((blurRadius + 1) * sizeof(GLfloat));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));

        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    // Next, normalize these weights to prevent the clipping of the Gaussian curve at the end of the discrete samples from reducing luminance
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }

    // From these weights we calculate the offsets to read interpolated values from
    int  trueNumberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = trueNumberOfOptimizedOffsets > 7 ? 7 : trueNumberOfOptimizedOffsets;

    char tempShader[20480] = {0};
    // Header
#ifdef __GLSL_SUPPORT_HIGHP__
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "uniform highp float texelWidthOffset;\n"
    "uniform highp float texelHeightOffset;\n"
    "\n"
    "varying highp vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp float sum = 0.0;\n"
    ;
#else
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "uniform float texelWidthOffset;\n"
    "uniform float texelHeightOffset;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    float sum = 0.0;\n"
    ;
#endif

    sprintf(tempShader + strlen(tempShader), part1, 1 + (numberOfOptimizedOffsets * 2));

    // Inner texture loop
    sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0]).r * %f;\n", standardGaussianWeights[0]);

    for (int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < numberOfOptimizedOffsets; currentBlurCoordinateIndex++)
    {
        GLfloat firstWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 1];
        GLfloat secondWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 2];
        GLfloat optimizedWeight = firstWeight + secondWeight;

        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]).r * %f;\n", (currentBlurCoordinateIndex * 2) + 1, optimizedWeight);
        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]).r * %f;\n", (currentBlurCoordinateIndex * 2) + 2, optimizedWeight);
    }

    // If the number of required samples exceeds the amount we can pass in via varyings, we have to do dependent texture reads in the fragment shader
    if (trueNumberOfOptimizedOffsets > numberOfOptimizedOffsets)
    {
#ifdef __GLSL_SUPPORT_HIGHP__
        sprintf(tempShader + strlen(tempShader), "highp vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n");
#else
        sprintf(tempShader + strlen(tempShader), "vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n");
#endif

        for (int currentOverlowTextureRead = numberOfOptimizedOffsets; currentOverlowTextureRead < trueNumberOfOptimizedOffsets; currentOverlowTextureRead++)
        {
            GLfloat firstWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 1];
            GLfloat secondWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 2];

            GLfloat optimizedWeight = firstWeight + secondWeight;
            GLfloat optimizedOffset = (firstWeight * (currentOverlowTextureRead * 2 + 1) + secondWeight * (currentOverlowTextureRead * 2 + 2)) / optimizedWeight;

            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffset * %f).r * %f;\n", optimizedOffset, optimizedWeight);
            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffset * %f).r * %f;\n", optimizedOffset, optimizedWeight);
        }
    }

    // Footer
    const char* part2 =
    "   gl_FragColor = vec4(sum, sum, sum, 1.0);\n"
    "}\n"
    ;

    strcpy(tempShader + strlen(tempShader), part2);

    free(standardGaussianWeights);

    resetFirstFragmentShader(tempShader);
    resetSecondFragmentShader(tempShader);
}


void GPUImageSingleComponentGaussianBlurFilter::recreateFilter()
{
    this->~GPUImageSingleComponentGaussianBlurFilter();
    new(this)GPUImageSingleComponentGaussianBlurFilter(m_fBlurRadiusInPexels);
}

