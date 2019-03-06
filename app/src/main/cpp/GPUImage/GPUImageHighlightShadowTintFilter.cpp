/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHighlightShadowTintFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _highlightShadowTint_fragment_shader[] = SHADER_STR(
    precision lowp float;

    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform lowp float shadowTintIntensity;
    uniform lowp float highlightTintIntensity;
    uniform highp vec4 shadowTintColor;
    uniform highp vec4 highlightTintColor;

    const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        highp float luminance = dot(textureColor.rgb, luminanceWeighting);

        highp vec4 shadowResult = mix(textureColor, max(textureColor, vec4( mix(shadowTintColor.rgb, textureColor.rgb, luminance), textureColor.a)), shadowTintIntensity);
        highp vec4 highlightResult = mix(textureColor, min(shadowResult, vec4( mix(shadowResult.rgb, highlightTintColor.rgb, luminance), textureColor.a)), highlightTintIntensity);

        gl_FragColor = vec4( mix(shadowResult.rgb, highlightResult.rgb, luminance), textureColor.a);
    }
);

#else


// 片元着色器
extern const char _highlightShadowTint_fragment_shader[] = SHADER_STR(
 precision mediump float;

 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float shadowTintIntensity;
 uniform float highlightTintIntensity;
 uniform vec3 shadowTintColor;
 uniform vec3 highlightTintColor;

 const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
     float luminance = dot(textureColor.rgb, luminanceWeighting);

     vec4 shadowResult = mix(textureColor, max(textureColor, vec4( mix(shadowTintColor.rgb, textureColor.rgb, luminance), textureColor.a)), shadowTintIntensity);
     vec4 highlightResult = mix(textureColor, min(shadowResult, vec4( mix(shadowResult.rgb, highlightTintColor.rgb, luminance), textureColor.a)), highlightTintIntensity);

     gl_FragColor = vec4( mix(shadowResult.rgb, highlightResult.rgb, luminance), textureColor.a);
 }
);

#endif



GPUImageHighlightShadowTintFilter::GPUImageHighlightShadowTintFilter()
    : GPUImageFilter(_highlightShadowTint_fragment_shader)
{
    m_fShadowTintIntensity = 0.0f;
    m_fHighlightTintIntensity = 0.0f;


    m_iShadowTintColorUniformLocation = -1;
    m_iShadowTintIntensityUniformLocation = -1;
    m_iHighlightTintColorUniformLocation = -1;
    m_iHighlightTintIntensityUniformLocation = -1;

    m_pShadowTintColor[0] = 1.0f;
    m_pShadowTintColor[1] = 0.0f;
    m_pShadowTintColor[2] = 0.0f;
    m_pShadowTintColor[3] = 1.0f;

    m_pHighlightTintColor[0] = 0.0f;
    m_pHighlightTintColor[1] = 0.0f;
    m_pHighlightTintColor[2] = 1.0f;
    m_pHighlightTintColor[3] = 1.0f;
}

GPUImageHighlightShadowTintFilter::~GPUImageHighlightShadowTintFilter()
{

}

void GPUImageHighlightShadowTintFilter::setShadowTintIntensity(float intensity)
{
    m_fShadowTintIntensity = intensity;
}

void GPUImageHighlightShadowTintFilter::setHighlightTintIntensity(float intensity)
{
    m_fHighlightTintIntensity = intensity;
}

void GPUImageHighlightShadowTintFilter::setShadowTintIntensity(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fShadowTintIntensity = 0.0f + incremental * percent;
}

void GPUImageHighlightShadowTintFilter::setHighlightTintIntensity(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fHighlightTintIntensity = 0.0f + incremental * percent;
}

void GPUImageHighlightShadowTintFilter::setShadowTintColorRed(float red, float green, float blue,
                                                              float alpha)
{
    m_pShadowTintColor[0] = red;
    m_pShadowTintColor[1] = green;
    m_pShadowTintColor[2] = blue;
    m_pShadowTintColor[3] = alpha;
}

void GPUImageHighlightShadowTintFilter::setHighlightTintColorRed(float red, float green, float blue,
                                                                 float alpha)
{
    m_pHighlightTintColor[0] = red;
    m_pHighlightTintColor[1] = green;
    m_pHighlightTintColor[2] = blue;
    m_pHighlightTintColor[3] = alpha;
}

bool GPUImageHighlightShadowTintFilter::createProgramExtra()
{
    m_iShadowTintColorUniformLocation = glGetUniformLocation(m_uProgram, "shadowTintColor");
    m_iShadowTintIntensityUniformLocation = glGetUniformLocation(m_uProgram, "shadowTintIntensity");
    m_iHighlightTintColorUniformLocation = glGetUniformLocation(m_uProgram, "highlightTintColor");
    m_iHighlightTintIntensityUniformLocation = glGetUniformLocation(m_uProgram, "highlightTintIntensity");

    return true;
}

bool GPUImageHighlightShadowTintFilter::beforeDrawExtra()
{
    glUniform1f(m_iHighlightTintIntensityUniformLocation, m_fHighlightTintIntensity);
    glUniform1f(m_iShadowTintIntensityUniformLocation, m_fShadowTintIntensity);

    glUniform4fv(m_iShadowTintColorUniformLocation, 1, m_pShadowTintColor);
    glUniform4fv(m_iHighlightTintColorUniformLocation, 1, m_pHighlightTintColor);

    return true;
}

