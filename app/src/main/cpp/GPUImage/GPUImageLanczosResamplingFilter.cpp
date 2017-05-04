/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLanczosResamplingFilter.h"


// 顶点着色器
extern const char _lanczosResapling_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepLeftTextureCoordinate;\n"
"varying vec2 twoStepsLeftTextureCoordinate;\n"
"varying vec2 threeStepsLeftTextureCoordinate;\n"
"varying vec2 fourStepsLeftTextureCoordinate;\n"
"varying vec2 oneStepRightTextureCoordinate;\n"
"varying vec2 twoStepsRightTextureCoordinate;\n"
"varying vec2 threeStepsRightTextureCoordinate;\n"
"varying vec2 fourStepsRightTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 firstOffset = vec2(texelWidthOffset, texelHeightOffset);\n"
"    vec2 secondOffset = vec2(2.0 * texelWidthOffset, 2.0 * texelHeightOffset);\n"
"    vec2 thirdOffset = vec2(3.0 * texelWidthOffset, 3.0 * texelHeightOffset);\n"
"    vec2 fourthOffset = vec2(4.0 * texelWidthOffset, 4.0 * texelHeightOffset);\n"
"\n"
"    centerTextureCoordinate = inputTextureCoordinate;\n"
"    oneStepLeftTextureCoordinate = inputTextureCoordinate - firstOffset;\n"
"    twoStepsLeftTextureCoordinate = inputTextureCoordinate - secondOffset;\n"
"    threeStepsLeftTextureCoordinate = inputTextureCoordinate - thirdOffset;\n"
"    fourStepsLeftTextureCoordinate = inputTextureCoordinate - fourthOffset;\n"
"    oneStepRightTextureCoordinate = inputTextureCoordinate + firstOffset;\n"
"    twoStepsRightTextureCoordinate = inputTextureCoordinate + secondOffset;\n"
"    threeStepsRightTextureCoordinate = inputTextureCoordinate + thirdOffset;\n"
"    fourStepsRightTextureCoordinate = inputTextureCoordinate + fourthOffset;\n"
"}"
;


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _lanczosResapling_fragment_shader[]=
"precision highp float;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepLeftTextureCoordinate;\n"
"varying vec2 twoStepsLeftTextureCoordinate;\n"
"varying vec2 threeStepsLeftTextureCoordinate;\n"
"varying vec2 fourStepsLeftTextureCoordinate;\n"
"varying vec2 oneStepRightTextureCoordinate;\n"
"varying vec2 twoStepsRightTextureCoordinate;\n"
"varying vec2 threeStepsRightTextureCoordinate;\n"
"varying vec2 fourStepsRightTextureCoordinate;\n"
"\n"
"// sinc(x) * sinc(x/a) = (a * sin(pi * x) * sin(pi * x / a)) / (pi^2 * x^2)\n"
"// Assuming a Lanczos constant of 2.0, and scaling values to max out at x = +/- 1.5\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 fragmentColor = texture2D(inputImageTexture, centerTextureCoordinate) * 0.38026;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepLeftTextureCoordinate) * 0.27667;\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepRightTextureCoordinate) * 0.27667;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsLeftTextureCoordinate) * 0.08074;\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsRightTextureCoordinate) * 0.08074;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsLeftTextureCoordinate) * -0.02612;\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsRightTextureCoordinate) * -0.02612;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsLeftTextureCoordinate) * -0.02143;\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsRightTextureCoordinate) * -0.02143;\n"
"\n"
"    gl_FragColor = fragmentColor;\n"
"}"
;

#else

// 片元着色器
extern const char _lanczosResapling_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepLeftTextureCoordinate;\n"
"varying vec2 twoStepsLeftTextureCoordinate;\n"
"varying vec2 threeStepsLeftTextureCoordinate;\n"
"varying vec2 fourStepsLeftTextureCoordinate;\n"
"varying vec2 oneStepRightTextureCoordinate;\n"
"varying vec2 twoStepsRightTextureCoordinate;\n"
"varying vec2 threeStepsRightTextureCoordinate;\n"
"varying vec2 fourStepsRightTextureCoordinate;\n"
"\n"
"// sinc(x) * sinc(x/a) = (a * sin(pi * x) * sin(pi * x / a)) / (pi^2 * x^2)\n"
"// Assuming a Lanczos constant of 2.0, and scaling values to max out at x = +/- 1.5\n"
"\n"
"void main()\n"
"{\n"
"    vec4 fragmentColor = texture2D(inputImageTexture, centerTextureCoordinate) * 0.38026;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepLeftTextureCoordinate) * 0.27667;\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepRightTextureCoordinate) * 0.27667;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsLeftTextureCoordinate) * 0.08074;\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsRightTextureCoordinate) * 0.08074;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsLeftTextureCoordinate) * -0.02612;\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsRightTextureCoordinate) * -0.02612;\n"
"\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsLeftTextureCoordinate) * -0.02143;\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsRightTextureCoordinate) * -0.02143;\n"
"\n"
"    gl_FragColor = fragmentColor;\n"
"}"
;

#endif




GPUImageLanczosResamplingFilter::GPUImageLanczosResamplingFilter()
    : GPUImageTwoPassTextureSamplingFilter(_lanczosResapling_vertex_shader, _lanczosResapling_fragment_shader, _lanczosResapling_vertex_shader, _lanczosResapling_fragment_shader)
{

}

GPUImageLanczosResamplingFilter::~GPUImageLanczosResamplingFilter() {

}

void GPUImageLanczosResamplingFilter::setTextureSize(int width, int height)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureSize(width, height);
    updateTexelSize();
}

void GPUImageLanczosResamplingFilter::setTextureRotation(Rotation rotation)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureRotation(rotation);
    updateTexelSize();
}

void GPUImageLanczosResamplingFilter::setImageSize(float width, float height)
{
    m_pOriginalImageSize[0] = width;
    m_pOriginalImageSize[1] = height;
}


void GPUImageLanczosResamplingFilter::updateTexelSize()
{
    if(0 == m_pOriginalImageSize[0]){
        m_pOriginalImageSize[0] = 1280;
    }

    if(0 == m_pOriginalImageSize[1]){
        m_pOriginalImageSize[1] = 720;
    }

    // The first pass through the framebuffer may rotate the inbound image, so need to account for that by changing up the kernel ordering for that pass
    if(isRotationSwapWidthAndHeight()
       // the first framebuffer will not rotate, the last framebuffer will rotate
       && false
            ){
        m_fVerticalPassTexelWidthOffset = m_f_verticalTexelSpacing / m_pOriginalImageSize[1];
        m_fVerticalPassTexelHeightOffset = 0.0f;
    }else{
        m_fVerticalPassTexelWidthOffset = 0.0f;
        m_fVerticalPassTexelHeightOffset = m_f_verticalTexelSpacing / m_pOriginalImageSize[1];
    }

    m_fHorizontalPassTexelWidthOffset = m_f_horizontalTexelSpacing / m_pOriginalImageSize[0];
    m_fHorizontalPassTexelHeightOffset = 0.0f;
}

