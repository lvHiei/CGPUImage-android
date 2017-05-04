/**
* Created by lvHiei on 17-4-10.
* This is a project of GPUImage implemented with c++, you can
* use it free. if you find some bug please send me a email.
* My Email is majun_1523@163.com.
*/

#include "GPUImageLaplacianFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _laplacian_fragment_shader[]=
"precision highp float;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform mediump mat3 convolutionMatrix;\n"
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
"void main()\n"
"{\n"
"    mediump vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"    mediump vec3 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;\n"
"    mediump vec3 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;\n"
"    mediump vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    mediump vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    mediump vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"    mediump vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"    mediump vec3 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;\n"
"    mediump vec3 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;\n"
"\n"
"    mediump vec3 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];\n"
"    resultColor += leftColor * convolutionMatrix[1][0] + centerColor.rgb * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];\n"
"    resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];\n"
"\n"
"    // Normalize the results to allow for negative gradients in the 0.0-1.0 colorspace\n"
"    resultColor = resultColor + 0.5;\n"
"\n"
"    gl_FragColor = vec4(resultColor, centerColor.a);\n"
"}"
;


#else

// 片元着色器
extern const char _laplacian_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform mat3 convolutionMatrix;\n"
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
"void main()\n"
"{\n"
"    vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"    vec3 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;\n"
"    vec3 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;\n"
"    vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"    vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"    vec3 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;\n"
"    vec3 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;\n"
"\n"
"    vec3 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];\n"
"    resultColor += leftColor * convolutionMatrix[1][0] + centerColor.rgb * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];\n"
"    resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];\n"
"\n"
"    // Normalize the results to allow for negative gradients in the 0.0-1.0 colorspace\n"
"    resultColor = resultColor + 0.5;\n"
"\n"
"    gl_FragColor = vec4(resultColor, centerColor.a);\n"
"}"
;


#endif



GPUImageLaplacianFilter::GPUImageLaplacianFilter()
    : GPUImage3x3ConvolutionFilter(_laplacian_fragment_shader)
{
    int idx = 0;
    m_pConvolutionKernel[idx++] = 0.5f;
    m_pConvolutionKernel[idx++] = 1.0f;
    m_pConvolutionKernel[idx++] = 0.5f;

    m_pConvolutionKernel[idx++] = 1.0f;
    m_pConvolutionKernel[idx++] = -6.0f;
    m_pConvolutionKernel[idx++] = 1.0f;

    m_pConvolutionKernel[idx++] = 0.5f;
    m_pConvolutionKernel[idx++] = 1.0f;
    m_pConvolutionKernel[idx++] = 0.5f;
}

GPUImageLaplacianFilter::~GPUImageLaplacianFilter()
{

}

