/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePoissonBlendFilter.h"


// 片元着色器
extern const char _poissonBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 bottomTextureCoordinate;\n"
"\n"
"varying vec2 textureCoordinate2;\n"
"varying vec2 leftTextureCoordinate2;\n"
"varying vec2 rightTextureCoordinate2;\n"
"varying vec2 topTextureCoordinate2;\n"
"varying vec2 bottomTextureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform float mixturePercent;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"    vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"    vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"\n"
"    vec4 centerColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"    vec3 bottomColor2 = texture2D(inputImageTexture2, bottomTextureCoordinate2).rgb;\n"
"    vec3 leftColor2 = texture2D(inputImageTexture2, leftTextureCoordinate2).rgb;\n"
"    vec3 rightColor2 = texture2D(inputImageTexture2, rightTextureCoordinate2).rgb;\n"
"    vec3 topColor2 = texture2D(inputImageTexture2, topTextureCoordinate2).rgb;\n"
"\n"
"    vec3 meanColor = (bottomColor + leftColor + rightColor + topColor) / 4.0;\n"
"    vec3 diffColor = centerColor.rgb - meanColor;\n"
"\n"
"    vec3 meanColor2 = (bottomColor2 + leftColor2 + rightColor2 + topColor2) / 4.0;\n"
"    vec3 diffColor2 = centerColor2.rgb - meanColor2;\n"
"\n"
"    vec3 gradColor = (meanColor + diffColor2);\n"
"\n"
"    gl_FragColor = vec4(mix(centerColor.rgb, gradColor, centerColor2.a * mixturePercent), centerColor.a);\n"
"}"
;


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


