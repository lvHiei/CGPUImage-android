/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBoxBlurFilter.h"


GPUImageBoxBlurFilter::GPUImageBoxBlurFilter()
    : GPUImageGaussianBlurFilter()
{
    m_fBlurRadiusInPexels = 4.0f;

    initWithBlurSigma(4, 0.0);
}

GPUImageBoxBlurFilter::~GPUImageBoxBlurFilter()
{

}

void GPUImageBoxBlurFilter::genVertexShaderForOptimizedBlurOfRadius(int blurRadius, float sigma)
{
    if(blurRadius < 1){
        GPUImageGaussianBlurFilter::genVertexShaderForOptimizedBlurOfRadius(blurRadius, sigma);
        return;
    }

    char tempShader[20480] = {0};


    // From these weights we calculate the offsets to read interpolated values from
    int curOffset = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = curOffset > 7 ? 7 : curOffset;

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
        GLfloat optimizedOffset = (GLfloat)(currentOptimizedOffset * 2) + 1.5;
        sprintf(tempShader + strlen(tempShader), part2, (currentOptimizedOffset * 2) + 1, optimizedOffset, (currentOptimizedOffset * 2) + 2, optimizedOffset);
    }

    // Footer
    sprintf(tempShader + strlen(tempShader), "}\n");

    resetFirstVertexShader(tempShader);
    resetSecondVertexShader(tempShader);
}

void GPUImageBoxBlurFilter::genFragmentShaderForOptimizedBlurOfRadius(int blurRadius, float sigma)
{
    if(blurRadius < 1){
        GPUImageGaussianBlurFilter::genFragmentShaderForOptimizedBlurOfRadius(blurRadius, sigma);
        return;
    }


    int curOffset = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = curOffset > 7 ? 7 : curOffset;
    int trueNumberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);

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
    "    lowp vec4 sum = vec4(0.0);\n"
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
    "    vec4 sum = vec4(0.0);\n"
    ;
#endif

    sprintf(tempShader + strlen(tempShader), part1, 1 + (numberOfOptimizedOffsets * 2));


    GLfloat boxWeight = 1.0 / (GLfloat)((blurRadius * 2) + 1);

    // Inner texture loop
    sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0]) * %f;\n", boxWeight);

    for (int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < numberOfOptimizedOffsets; currentBlurCoordinateIndex++)
    {
        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", (currentBlurCoordinateIndex * 2) + 1, boxWeight * 2.0);
        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", (currentBlurCoordinateIndex * 2) + 2, boxWeight * 2.0);
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
            GLfloat optimizedOffset = (GLfloat)(currentOverlowTextureRead * 2) + 1.5;

            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffset * %f) * %f;\n", optimizedOffset, boxWeight * 2.0);
            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffset * %f) * %f;\n", optimizedOffset, boxWeight * 2.0);
        }
    }

    // Footer
    const char* part2 =
    "   gl_FragColor = sum;\n"
    "}\n"
    ;

    strcpy(tempShader + strlen(tempShader), part2);


    resetFirstFragmentShader(tempShader);
    resetSecondFragmentShader(tempShader);
}

