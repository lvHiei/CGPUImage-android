/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHighlightShadowFilter.h"

// 片元着色器
const char _highlightShadow_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform float shadows;\n"
"uniform float highlights;\n"
"\n"
"const vec3 luminanceWeighting = vec3(0.3, 0.3, 0.3);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 source = texture2D(inputImageTexture, textureCoordinate);\n"
"    float luminance = dot(source.rgb, luminanceWeighting);\n"
"\n"
"    float shadow = clamp((pow(luminance, 1.0/(shadows+1.0)) + (-0.76)*pow(luminance, 2.0/(shadows+1.0))) - luminance, 0.0, 1.0);\n"
"    float highlight = clamp((1.0 - (pow(1.0-luminance, 1.0/(2.0-highlights)) + (-0.8)*pow(1.0-luminance, 2.0/(2.0-highlights)))) - luminance, -1.0, 0.0);\n"
"    vec3 result = vec3(0.0, 0.0, 0.0) + ((luminance + shadow + highlight) - 0.0) * ((source.rgb - vec3(0.0, 0.0, 0.0))/(luminance - 0.0));\n"
"\n"
"    gl_FragColor = vec4(result.rgb, source.a);\n"
"}"
;


GPUImageHighlightShadowFilter::GPUImageHighlightShadowFilter()
    : GPUImageFilter(_highlightShadow_fragment_shader)
{
    m_fShadows = 0.0f;
    m_fHighlights = 1.0f;

    m_iShadowsUniformLocation = -1;
    m_iHighlightsUniformLocation = -1;
}

GPUImageHighlightShadowFilter::~GPUImageHighlightShadowFilter()
{

}

void GPUImageHighlightShadowFilter::setShadows(float shadows)
{
    m_fShadows = shadows;
}

void GPUImageHighlightShadowFilter::setHighlights(float highlights)
{
    m_fHighlights = highlights;
}

void GPUImageHighlightShadowFilter::setShadows(int percent)
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
    setShadows(value);
}

void GPUImageHighlightShadowFilter::setHighlights(int percent)
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
    setHighlights(value);
}

bool GPUImageHighlightShadowFilter::createProgramExtra()
{
    m_iShadowsUniformLocation = glGetUniformLocation(m_uProgram, "shadows");
    m_iHighlightsUniformLocation = glGetUniformLocation(m_uProgram, "highlights");
    return true;
}

bool GPUImageHighlightShadowFilter::beforeDrawExtra()
{
    glUniform1f(m_iHighlightsUniformLocation, m_fHighlights);
    glUniform1f(m_iShadowsUniformLocation, m_fShadows);

    return true;
}

