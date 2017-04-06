/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorLocalBinaryPatternFilter.h"

// 片元着色器
const char _colorLocalBinaryPattern_fragment_shader[]=
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
"    vec3 centerColor = texture2D(inputImageTexture, textureCoordinate).rgb;\n"
"    vec3 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;\n"
"    vec3 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;\n"
"    vec3 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;\n"
"    vec3 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;\n"
"    vec3 leftColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    vec3 rightColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"    vec3 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"    vec3 topColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"\n"
"    float redByteTally = 1.0 / 255.0 * step(centerColor.r, topRightColor.r);\n"
"    redByteTally += 2.0 / 255.0 * step(centerColor.r, topColor.r);\n"
"    redByteTally += 4.0 / 255.0 * step(centerColor.r, topLeftColor.r);\n"
"    redByteTally += 8.0 / 255.0 * step(centerColor.r, leftColor.r);\n"
"    redByteTally += 16.0 / 255.0 * step(centerColor.r, bottomLeftColor.r);\n"
"    redByteTally += 32.0 / 255.0 * step(centerColor.r, bottomColor.r);\n"
"    redByteTally += 64.0 / 255.0 * step(centerColor.r, bottomRightColor.r);\n"
"    redByteTally += 128.0 / 255.0 * step(centerColor.r, rightColor.r);\n"
"\n"
"    float blueByteTally = 1.0 / 255.0 * step(centerColor.b, topRightColor.b);\n"
"    blueByteTally += 2.0 / 255.0 * step(centerColor.b, topColor.b);\n"
"    blueByteTally += 4.0 / 255.0 * step(centerColor.b, topLeftColor.b);\n"
"    blueByteTally += 8.0 / 255.0 * step(centerColor.b, leftColor.b);\n"
"    blueByteTally += 16.0 / 255.0 * step(centerColor.b, bottomLeftColor.b);\n"
"    blueByteTally += 32.0 / 255.0 * step(centerColor.b, bottomColor.b);\n"
"    blueByteTally += 64.0 / 255.0 * step(centerColor.b, bottomRightColor.b);\n"
"    blueByteTally += 128.0 / 255.0 * step(centerColor.b, rightColor.b);\n"
"\n"
"    float greenByteTally = 1.0 / 255.0 * step(centerColor.g, topRightColor.g);\n"
"    greenByteTally += 2.0 / 255.0 * step(centerColor.g, topColor.g);\n"
"    greenByteTally += 4.0 / 255.0 * step(centerColor.g, topLeftColor.g);\n"
"    greenByteTally += 8.0 / 255.0 * step(centerColor.g, leftColor.g);\n"
"    greenByteTally += 16.0 / 255.0 * step(centerColor.g, bottomLeftColor.g);\n"
"    greenByteTally += 32.0 / 255.0 * step(centerColor.g, bottomColor.g);\n"
"    greenByteTally += 64.0 / 255.0 * step(centerColor.g, bottomRightColor.g);\n"
"    greenByteTally += 128.0 / 255.0 * step(centerColor.g, rightColor.g);\n"
"\n"
"    // TODO: Replace the above with a dot product and two vec4s\n"
"    // TODO: Apply step to a matrix, rather than individually\n"
"\n"
"    gl_FragColor = vec4(redByteTally, blueByteTally, greenByteTally, 1.0);\n"
"}"
;

GPUImageColorLocalBinaryPatternFilter::GPUImageColorLocalBinaryPatternFilter() :
    GPUImage3x3TextureSamplingFilter(_colorLocalBinaryPattern_fragment_shader)
{

}

GPUImageColorLocalBinaryPatternFilter::~GPUImageColorLocalBinaryPatternFilter()
{

}