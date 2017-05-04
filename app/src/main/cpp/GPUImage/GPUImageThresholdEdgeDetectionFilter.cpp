/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageThresholdEdgeDetectionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _thresholdEdgeDetection_fragment_shader[]=
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
"\n"
"uniform float edgeStrength;\n"
"\n"
"void main()\n"
"{\n"
"//     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n"
"//     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n"
"//     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n"
"//     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n"
"    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n"
"    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n"
"    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n"
"    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n"
"    float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;\n"
"//     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"//     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"//     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + leftIntensity + 2.0 * centerIntensity + rightIntensity;\n"
"//     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomIntensity + 2.0 * centerIntensity + topIntensity;\n"
"    float h = (centerIntensity - topIntensity) + (bottomIntensity - centerIntensity);\n"
"    float v = (centerIntensity - leftIntensity) + (rightIntensity - centerIntensity);\n"
"//     float h = (centerIntensity - topIntensity);\n"
"//     float j = (topIntensity - centerIntensity);\n"
"//     h = max(h,j);\n"
"//     j = abs(h);\n"
"//     float v = (centerIntensity - leftIntensity);\n"
"\n"
"    float mag = length(vec2(h, v)) * edgeStrength;\n"
"    mag = step(threshold, mag);\n"
"\n"
"//     float mag = abs(h);\n"
"\n"
"//     gl_FragColor = vec4(h, h, h, 1.0);\n"
"//     gl_FragColor = vec4(texture2D(inputImageTexture, textureCoordinate));\n"
"//     gl_FragColor = vec4(h, centerIntensity, j, 1.0);\n"
"    gl_FragColor = vec4(mag, mag, mag, 1.0);\n"
"}"
;

#else


// 片元着色器
extern const char _thresholdEdgeDetection_fragment_shader[]=
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
"\n"
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
"    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n"
"    h = max(0.0, h);\n"
"    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n"
"    v = max(0.0, v);\n"
"\n"
"    float mag = length(vec2(h, v)) * edgeStrength;\n"
"    mag = step(threshold, mag);\n"
"\n"
"    gl_FragColor = vec4(vec3(mag), 1.0);\n"
"}"
;


#endif


GPUImageThresholdEdgeDetectionFilter::GPUImageThresholdEdgeDetectionFilter()
    : GPUImageSobelEdgeDetectionFilter(_thresholdEdgeDetection_fragment_shader)
{
    m_fEdgeStrength = 1.0f;
    m_fThreshold = 0.25f;

    m_iThresholdUniformLocation = -1;
}

GPUImageThresholdEdgeDetectionFilter::GPUImageThresholdEdgeDetectionFilter(const char *fragment)
    : GPUImageSobelEdgeDetectionFilter(fragment)
{
    m_fEdgeStrength = 1.0f;
    m_fThreshold = 0.25f;

    m_iThresholdUniformLocation = -1;
}

GPUImageThresholdEdgeDetectionFilter::~GPUImageThresholdEdgeDetectionFilter()
{

}

void GPUImageThresholdEdgeDetectionFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

void GPUImageThresholdEdgeDetectionFilter::setThreshold(int percent)
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
    setThreshold(value);
}

bool GPUImageThresholdEdgeDetectionFilter::secondCreateProgramExtra()
{
    m_iThresholdUniformLocation = glGetUniformLocation(m_uSecondProgram, "threshold");
    return GPUImageSobelEdgeDetectionFilter::secondCreateProgramExtra();
}

bool GPUImageThresholdEdgeDetectionFilter::secondBeforeDraw()
{
    glUniform1f(m_iThresholdUniformLocation, m_fThreshold);
    return GPUImageSobelEdgeDetectionFilter::secondBeforeDraw();
}


