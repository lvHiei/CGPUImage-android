/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLocalBinaryPatternFilter.h"


// 片元着色器
const char _localBinaryPattern_fragment_shader[]=
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
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;\n"
"    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"\n"
"    float byteTally = 1.0 / 255.0 * step(centerIntensity, topRightIntensity);\n"
"    byteTally += 2.0 / 255.0 * step(centerIntensity, topIntensity);\n"
"    byteTally += 4.0 / 255.0 * step(centerIntensity, topLeftIntensity);\n"
"    byteTally += 8.0 / 255.0 * step(centerIntensity, leftIntensity);\n"
"    byteTally += 16.0 / 255.0 * step(centerIntensity, bottomLeftIntensity);\n"
"    byteTally += 32.0 / 255.0 * step(centerIntensity, bottomIntensity);\n"
"    byteTally += 64.0 / 255.0 * step(centerIntensity, bottomRightIntensity);\n"
"    byteTally += 128.0 / 255.0 * step(centerIntensity, rightIntensity);\n"
"\n"
"    // TODO: Replace the above with a dot product and two vec4s\n"
"    // TODO: Apply step to a matrix, rather than individually\n"
"\n"
"    gl_FragColor = vec4(byteTally, byteTally, byteTally, 1.0);\n"
"}"
;

GPUImageLocalBinaryPatternFilter::GPUImageLocalBinaryPatternFilter()
    : GPUImage3x3TextureSamplingFilter(_localBinaryPattern_fragment_shader)
{

}

GPUImageLocalBinaryPatternFilter::~GPUImageLocalBinaryPatternFilter()
{

}