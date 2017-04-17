/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageNonMaximumSuppressionFilter.h"


// 片元着色器
extern const char _nonMaximunSuppression_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
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
"void main()\n"
"{\n"
"    float bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"    float bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float leftColor = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightColor = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float topColor = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"    float topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"\n"
"    // Use a tiebreaker for pixels to the left and immediately above this one\n"
"    float multiplier = 1.0 - step(centerColor.r, topColor);\n"
"    multiplier = multiplier * (1.0 - step(centerColor.r, topLeftColor));\n"
"    multiplier = multiplier * (1.0 - step(centerColor.r, leftColor));\n"
"    multiplier = multiplier * (1.0 - step(centerColor.r, bottomLeftColor));\n"
"\n"
"    float maxValue = max(centerColor.r, bottomColor);\n"
"    maxValue = max(maxValue, bottomRightColor);\n"
"    maxValue = max(maxValue, rightColor);\n"
"    maxValue = max(maxValue, topRightColor);\n"
"\n"
"    gl_FragColor = vec4((centerColor.rgb * step(maxValue, centerColor.r) * multiplier), 1.0);\n"
"}"
;


GPUImageNonMaximumSuppressionFilter::GPUImageNonMaximumSuppressionFilter()
    : GPUImage3x3TextureSamplingFilter(_nonMaximunSuppression_fragment_shader)
{

}

GPUImageNonMaximumSuppressionFilter::~GPUImageNonMaximumSuppressionFilter()
{

}