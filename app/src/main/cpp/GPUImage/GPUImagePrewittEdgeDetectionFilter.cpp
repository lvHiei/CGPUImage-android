/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePrewittEdgeDetectionFilter.h"


// 片元着色器
extern const char _prewittEdgeDetection_fragment_shader[]=
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
"uniform float edgeStrength;\n"
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
"    float h = -topLeftIntensity - topIntensity - topRightIntensity + bottomLeftIntensity + bottomIntensity + bottomRightIntensity;\n"
"    float v = -bottomLeftIntensity - leftIntensity - topLeftIntensity + bottomRightIntensity + rightIntensity + topRightIntensity;\n"
"\n"
"    float mag = length(vec2(h, v)) * edgeStrength;\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;


GPUImagePrewittEdgeDetectionFilter::GPUImagePrewittEdgeDetectionFilter()
    : GPUImageSobelEdgeDetectionFilter(_prewittEdgeDetection_fragment_shader)
{
    m_fEdgeStrength = 1.0f;
}

GPUImagePrewittEdgeDetectionFilter::~GPUImagePrewittEdgeDetectionFilter()
{

}

