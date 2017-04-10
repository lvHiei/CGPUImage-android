/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageToonFilter.h"


// 片元着色器
const char _toon_fragment_shader[]=
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
"uniform float intensity;\n"
"uniform float threshold;\n"
"uniform float quantizationLevels;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
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
"    float mag = length(vec2(h, v));\n"
"\n"
"    vec3 posterizedImageColor = floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;\n"
"\n"
"    float thresholdTest = 1.0 - step(threshold, mag);\n"
"\n"
"    gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);\n"
"}"
;

GPUImageToonFilter::GPUImageToonFilter()
    : GPUImage3x3TextureSamplingFilter(_toon_fragment_shader)
{
    m_fThreshold = 0.2f;
    m_fQuantizationLevels = 10.0f;
}

GPUImageToonFilter::~GPUImageToonFilter()
{

}

bool GPUImageToonFilter::createProgramExtra()
{
    m_iThresholdUniformLocation = glGetUniformLocation(m_uProgram, "threshold");
    m_iQuantizationLevelsUniformLocation = glGetUniformLocation(m_uProgram, "quantizationLevels");
    GPUImage3x3TextureSamplingFilter::createProgramExtra();
    return true;
}

bool GPUImageToonFilter::beforeDrawExtra()
{
    glUniform1f(m_iThresholdUniformLocation, m_fThreshold);
    glUniform1f(m_iQuantizationLevelsUniformLocation, m_fQuantizationLevels);
    GPUImage3x3TextureSamplingFilter::beforeDrawExtra();
    return true;
}

void GPUImageToonFilter::setThreshold(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fThreshold = 0.0f + incremental * percent;
}

void GPUImageToonFilter::setQuantizationLevels(float quantizationLevels)
{
    m_fQuantizationLevels = quantizationLevels;
}


void GPUImageToonFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

