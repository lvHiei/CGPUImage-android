/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImage3x3ConvolutionFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _3x3Convolution_fragment_shader[]= SHADER_STR(
    precision highp float;

    uniform sampler2D inputImageTexture;

    uniform mediump mat3 convolutionMatrix;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    void main()
    {
        mediump vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;
        mediump vec3 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;
        mediump vec3 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;
        mediump vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
        mediump vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
        mediump vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
        mediump vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;
        mediump vec3 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;
        mediump vec3 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;

        mediump vec3 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];
        resultColor += leftColor * convolutionMatrix[1][0] + centerColor.rgb * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];
        resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];

        gl_FragColor = vec4(resultColor, centerColor.a);
    }
);

#else

// 片元着色器
extern const char _3x3Convolution_fragment_shader[]= SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;

 uniform mat3 convolutionMatrix;

 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 void main()
 {
     vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;
     vec3 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;
     vec3 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;
     vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
     vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
     vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
     vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;
     vec3 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;
     vec3 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;

     vec3 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];
     resultColor += leftColor * convolutionMatrix[1][0] + centerColor.rgb * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];
     resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];

     gl_FragColor = vec4(resultColor, centerColor.a);
 }
);


#endif


GLfloat convolution_init[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
};


GLfloat convolution_example[] = {
        -1.0f, 0.0f, 1.0f,
        -2.0f, 0.0f, 2.0f,
        -1.0f, 0.0f, 1.0f,
};

GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter() :
    GPUImage3x3TextureSamplingFilter(_3x3Convolution_fragment_shader)
{
    memcpy(m_pConvolutionKernel, convolution_example, 9 * sizeof(float));
}


GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter(const char *fragment)
    : GPUImage3x3TextureSamplingFilter(fragment)
{
    memcpy(m_pConvolutionKernel, convolution_example, 9 * sizeof(float));
}


GPUImage3x3ConvolutionFilter::~GPUImage3x3ConvolutionFilter()
{

}

bool GPUImage3x3ConvolutionFilter::createProgramExtra()
{
    m_iConvolutionUniformLocation = glGetUniformLocation(m_uProgram, "convolutionMatrix");
    GPUImage3x3TextureSamplingFilter::createProgramExtra();
    return true;
}

bool GPUImage3x3ConvolutionFilter::beforeDrawExtra()
{
    glUniformMatrix3fv(m_iConvolutionUniformLocation, 1, false, m_pConvolutionKernel);
    GPUImage3x3TextureSamplingFilter::beforeDrawExtra();
    return true;
}

void GPUImage3x3ConvolutionFilter::setConvolutionKernel(float *convolutionKernel)
{
    memcpy(m_pConvolutionKernel, convolutionKernel, 9 * sizeof(float));
}