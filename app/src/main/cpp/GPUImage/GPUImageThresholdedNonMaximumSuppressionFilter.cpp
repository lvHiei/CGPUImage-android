/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageThresholdedNonMaximumSuppressionFilter.h"


// 片元着色器
extern const char _thresholdedNonMaximumSuppression_fragment_shader[]=
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
"uniform float threshold;\n"
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
"    float finalValue = centerColor.r * step(maxValue, centerColor.r) * multiplier;\n"
"    finalValue = step(threshold, finalValue);\n"
"\n"
"    gl_FragColor = vec4(finalValue, finalValue, finalValue, 1.0);\n"
"    //\n"
"    //     gl_FragColor = vec4((centerColor.rgb * step(maxValue, step(threshold, centerColor.r)) * multiplier), 1.0);\n"
"}"
;


GPUImageThresholdedNonMaximumSuppressionFilter::GPUImageThresholdedNonMaximumSuppressionFilter()
    : GPUImage3x3TextureSamplingFilter(_thresholdedNonMaximumSuppression_fragment_shader)
{
    m_fThreshold = 0.8f;
}

GPUImageThresholdedNonMaximumSuppressionFilter::~GPUImageThresholdedNonMaximumSuppressionFilter()
{

}

bool GPUImageThresholdedNonMaximumSuppressionFilter::createProgramExtra()
{
    m_iThresholdUniformLocation = glGetUniformLocation(m_uProgram, "threshold");
    GPUImage3x3TextureSamplingFilter::createProgramExtra();
    return true;
}

bool GPUImageThresholdedNonMaximumSuppressionFilter::beforeDrawExtra()
{
    glUniform1f(m_iThresholdUniformLocation, m_fThreshold);
    GPUImage3x3TextureSamplingFilter::beforeDrawExtra();
    return true;
}

void GPUImageThresholdedNonMaximumSuppressionFilter::setThreshold(int percent)
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


void GPUImageThresholdedNonMaximumSuppressionFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

