/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHalftoneFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _halftone_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform highp float fractionalWidthOfPixel;\n"
"uniform highp float aspectRatio;\n"
"uniform highp float dotScaling;\n"
"\n"
"const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);\n"
"\n"
"    highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;\n"
"    highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);\n"
"\n"
"    lowp vec3 sampledColor = texture2D(inputImageTexture, samplePos ).rgb;\n"
"    highp float dotScaling = 1.0 - dot(sampledColor, W);\n"
"\n"
"    lowp float checkForPresenceWithinDot = 1.0 - step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);\n"
"\n"
"    gl_FragColor = vec4(vec3(checkForPresenceWithinDot), 1.0);\n"
"}"
;

#else

// 片元着色器
extern const char _halftone_fragment_shader[]=
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform float fractionalWidthOfPixel;\n"
"uniform float aspectRatio;\n"
"uniform float dotScaling;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);\n"
"\n"
"    vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;\n"
"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);\n"
"\n"
"    vec3 sampledColor = texture2D(inputImageTexture, samplePos ).rgb;\n"
"    float dotScaling = 1.0 - dot(sampledColor, W);\n"
"\n"
"    float checkForPresenceWithinDot = 1.0 - step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);\n"
"\n"
"    gl_FragColor = vec4(vec3(checkForPresenceWithinDot), 1.0);\n"
"}"
;

#endif



GPUImageHalftoneFilter::GPUImageHalftoneFilter()
    : GPUImagePixellateFilter(_halftone_fragment_shader)
{
    m_fFractionalWidthOfAPixel = 0.01f;
}

GPUImageHalftoneFilter::~GPUImageHalftoneFilter()
{

}

