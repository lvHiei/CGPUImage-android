/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePolkaDotFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _polkaDot_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform highp float fractionalWidthOfPixel;\n"
"uniform highp float aspectRatio;\n"
"uniform highp float dotScaling;\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);\n"
"\n"
"    highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;\n"
"    highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);\n"
"    lowp float checkForPresenceWithinDot = step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);\n"
"\n"
"    lowp vec4 inputColor = texture2D(inputImageTexture, samplePos);\n"
"\n"
"    gl_FragColor = vec4(inputColor.rgb * checkForPresenceWithinDot, inputColor.a);\n"
"}"
;

#else


// 片元着色器
extern const char _polkaDot_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform float fractionalWidthOfPixel;\n"
"uniform float aspectRatio;\n"
"uniform float dotScaling;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);\n"
"\n"
"    vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;\n"
"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);\n"
"    float checkForPresenceWithinDot = step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);\n"
"\n"
"    vec4 inputColor = texture2D(inputImageTexture, samplePos);\n"
"\n"
"    gl_FragColor = vec4(inputColor.rgb * checkForPresenceWithinDot, inputColor.a);\n"
"}"
;

#endif




GPUImagePolkaDotFilter::GPUImagePolkaDotFilter()
    : GPUImagePixellateFilter(_polkaDot_fragment_shader)
{
    m_fDotScaling = 0.90f;

    m_iDotScalingUniformLocation = -1;
}

GPUImagePolkaDotFilter::~GPUImagePolkaDotFilter()
{

}

void GPUImagePolkaDotFilter::setDotScaling(float dotScaling)
{
    m_fDotScaling = dotScaling;
}

bool GPUImagePolkaDotFilter::createProgramExtra()
{
    m_iDotScalingUniformLocation = glGetUniformLocation(m_uProgram, "dotScaling");
    return GPUImagePixellateFilter::createProgramExtra();
}

bool GPUImagePolkaDotFilter::beforeDrawExtra()
{
    glUniform1f(m_iDotScalingUniformLocation, m_fDotScaling);
    return GPUImagePixellateFilter::beforeDrawExtra();
}

