/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePolkaDotFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _polkaDot_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float fractionalWidthOfPixel;
    uniform highp float aspectRatio;
    uniform highp float dotScaling;

    void main()
    {
        highp vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);

        highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;
        highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
        highp vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
        highp float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);
        lowp float checkForPresenceWithinDot = step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);

        lowp vec4 inputColor = texture2D(inputImageTexture, samplePos);

        gl_FragColor = vec4(inputColor.rgb * checkForPresenceWithinDot, inputColor.a);
    }
);

#else


// 片元着色器
extern const char _polkaDot_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform float fractionalWidthOfPixel;
 uniform float aspectRatio;
 uniform float dotScaling;

 void main()
 {
     vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);

     vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;
     vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
     vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
     float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);
     float checkForPresenceWithinDot = step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);

     vec4 inputColor = texture2D(inputImageTexture, samplePos);

     gl_FragColor = vec4(inputColor.rgb * checkForPresenceWithinDot, inputColor.a);
 }
);

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

