/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePoissonBlendFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _poissonBlend_fragment_shader[]=SHADER_STR(
    precision mediump float;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;
    varying vec2 topTextureCoordinate;
    varying vec2 bottomTextureCoordinate;

    varying vec2 textureCoordinate2;
    varying vec2 leftTextureCoordinate2;
    varying vec2 rightTextureCoordinate2;
    varying vec2 topTextureCoordinate2;
    varying vec2 bottomTextureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    uniform lowp float mixturePercent;

    void main()
    {
        vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
        vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;
        vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
        vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
        vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;

        vec4 centerColor2 = texture2D(inputImageTexture2, textureCoordinate2);
        vec3 bottomColor2 = texture2D(inputImageTexture2, bottomTextureCoordinate2).rgb;
        vec3 leftColor2 = texture2D(inputImageTexture2, leftTextureCoordinate2).rgb;
        vec3 rightColor2 = texture2D(inputImageTexture2, rightTextureCoordinate2).rgb;
        vec3 topColor2 = texture2D(inputImageTexture2, topTextureCoordinate2).rgb;

        vec3 meanColor = (bottomColor + leftColor + rightColor + topColor) / 4.0;
        vec3 diffColor = centerColor.rgb - meanColor;

        vec3 meanColor2 = (bottomColor2 + leftColor2 + rightColor2 + topColor2) / 4.0;
        vec3 diffColor2 = centerColor2.rgb - meanColor2;

        vec3 gradColor = (meanColor + diffColor2);

        gl_FragColor = vec4(mix(centerColor.rgb, gradColor, centerColor2.a * mixturePercent), centerColor.a);
    }
);


#else


// 片元着色器
extern const char _poissonBlend_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;
 varying vec2 topTextureCoordinate;
 varying vec2 bottomTextureCoordinate;

 varying vec2 textureCoordinate2;
 varying vec2 leftTextureCoordinate2;
 varying vec2 rightTextureCoordinate2;
 varying vec2 topTextureCoordinate2;
 varying vec2 bottomTextureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 uniform float mixturePercent;

 void main()
 {
     vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
     vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;
     vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
     vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
     vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;

     vec4 centerColor2 = texture2D(inputImageTexture2, textureCoordinate2);
     vec3 bottomColor2 = texture2D(inputImageTexture2, bottomTextureCoordinate2).rgb;
     vec3 leftColor2 = texture2D(inputImageTexture2, leftTextureCoordinate2).rgb;
     vec3 rightColor2 = texture2D(inputImageTexture2, rightTextureCoordinate2).rgb;
     vec3 topColor2 = texture2D(inputImageTexture2, topTextureCoordinate2).rgb;

     vec3 meanColor = (bottomColor + leftColor + rightColor + topColor) / 4.0;
     vec3 diffColor = centerColor.rgb - meanColor;

     vec3 meanColor2 = (bottomColor2 + leftColor2 + rightColor2 + topColor2) / 4.0;
     vec3 diffColor2 = centerColor2.rgb - meanColor2;

     vec3 gradColor = (meanColor + diffColor2);

     gl_FragColor = vec4(mix(centerColor.rgb, gradColor, centerColor2.a * mixturePercent), centerColor.a);
 }
);


#endif



GPUImagePoissonBlendFilter::GPUImagePoissonBlendFilter()
    : GPUImageTwoInputCrossTextureSamplingFilter(_poissonBlend_fragment_shader)
{
    m_fMix = 1.0f;

    m_iMixUniformLocation = -1;
}

GPUImagePoissonBlendFilter::~GPUImagePoissonBlendFilter()
{

}

void GPUImagePoissonBlendFilter::setMix(float mix)
{
    m_fMix = mix;
}

void GPUImagePoissonBlendFilter::setMix(int percent)
{
    float max = 1.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setMix(value);
}

bool GPUImagePoissonBlendFilter::createProgramExtra()
{
    m_iMixUniformLocation = glGetUniformLocation(m_uProgram, "mixturePercent");
    return GPUImageTwoInputCrossTextureSamplingFilter::createProgramExtra();
}

bool GPUImagePoissonBlendFilter::beforeDrawExtra()
{
    glUniform1f(m_iMixUniformLocation, m_fMix);
    return GPUImageTwoInputCrossTextureSamplingFilter::beforeDrawExtra();
}


