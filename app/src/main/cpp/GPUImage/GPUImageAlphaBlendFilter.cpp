/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageAlphaBlendFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _alphaBlend_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform lowp float mixturePercent;\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    lowp vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    gl_FragColor = vec4(mix(textureColor.rgb, textureColor2.rgb, textureColor2.a * mixturePercent), textureColor.a);\n"
"}"
;

#else

// 片元着色器
extern const char _alphaBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform float mixturePercent;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    gl_FragColor = vec4(mix(textureColor.rgb, textureColor2.rgb, textureColor2.a * mixturePercent), textureColor.a);\n"
"}"
;

#endif




GPUImageAlphaBlendFilter::GPUImageAlphaBlendFilter()
    : GPUImageTwoInputFilter(_alphaBlend_fragment_shader)
{
    m_fMix = 0.5f;

    m_iMixUniformLocation = -1;
}


GPUImageAlphaBlendFilter::~GPUImageAlphaBlendFilter()
{

}

bool GPUImageAlphaBlendFilter::createProgramExtra()
{
    GPUImageTwoInputFilter::createProgramExtra();
    m_iMixUniformLocation = glGetUniformLocation(m_uProgram, "mixturePercent");
    return true;
}

bool GPUImageAlphaBlendFilter::beforeDrawExtra()
{
    GPUImageTwoInputFilter::beforeDrawExtra();
    glUniform1f(m_iMixUniformLocation, m_fMix);
    return true;
}

void GPUImageAlphaBlendFilter::setMix(int percent)
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


void GPUImageAlphaBlendFilter::setMix(float mix)
{
    m_fMix = mix;
}

