/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageThresholdSketchFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _thresholdSketch_fragment_shader[]=
"precision highp float;\n"
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
"uniform sampler2D inputImageTexture;\n"
"uniform lowp float threshold;\n"
"uniform float edgeStrength;\n"
"\n"
"const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"\n"
"    float mag = (length(vec2(h, v)) * edgeStrength);\n"
"    mag = step(threshold, mag);\n"
"    mag = 1.0 - mag;\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;

#else

// 片元着色器
extern const char _thresholdSketch_fragment_shader[]=
"precision mediump float;\n"
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
"uniform sampler2D inputImageTexture;\n"
"uniform float threshold;\n"
"uniform float edgeStrength;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"\n"
"    float mag = 1.0 - length(vec2(h, v) * edgeStrength);\n"
"    mag = step(threshold, mag);\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;

#endif




GPUImageThresholdSketchFilter::GPUImageThresholdSketchFilter()
    : GPUImageThresholdEdgeDetectionFilter(_thresholdSketch_fragment_shader)
{

}

GPUImageThresholdSketchFilter::~GPUImageThresholdSketchFilter()
{

}

