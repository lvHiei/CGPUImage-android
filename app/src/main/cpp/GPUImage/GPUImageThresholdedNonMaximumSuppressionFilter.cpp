/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageThresholdedNonMaximumSuppressionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _thresholdedNonMaximumSuppression_fragment_shader[]=SHADER_STR(
    uniform sampler2D inputImageTexture;

    varying highp vec2 textureCoordinate;
    varying highp vec2 leftTextureCoordinate;
    varying highp vec2 rightTextureCoordinate;

    varying highp vec2 topTextureCoordinate;
    varying highp vec2 topLeftTextureCoordinate;
    varying highp vec2 topRightTextureCoordinate;

    varying highp vec2 bottomTextureCoordinate;
    varying highp vec2 bottomLeftTextureCoordinate;
    varying highp vec2 bottomRightTextureCoordinate;

    uniform lowp float threshold;

    void main()
    {
        lowp float bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        lowp float bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        lowp float bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        lowp vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
        lowp float leftColor = texture2D(inputImageTexture, leftTextureCoordinate).r;
        lowp float rightColor = texture2D(inputImageTexture, rightTextureCoordinate).r;
        lowp float topColor = texture2D(inputImageTexture, topTextureCoordinate).r;
        lowp float topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        lowp float topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).r;

        // Use a tiebreaker for pixels to the left and immediately above this one
        lowp float multiplier = 1.0 - step(centerColor.r, topColor);
        multiplier = multiplier * (1.0 - step(centerColor.r, topLeftColor));
        multiplier = multiplier * (1.0 - step(centerColor.r, leftColor));
        multiplier = multiplier * (1.0 - step(centerColor.r, bottomLeftColor));

        lowp float maxValue = max(centerColor.r, bottomColor);
        maxValue = max(maxValue, bottomRightColor);
        maxValue = max(maxValue, rightColor);
        maxValue = max(maxValue, topRightColor);

        lowp float finalValue = centerColor.r * step(maxValue, centerColor.r) * multiplier;
        finalValue = step(threshold, finalValue);

        gl_FragColor = vec4(finalValue, finalValue, finalValue, 1.0);
        //
        //     gl_FragColor = vec4((centerColor.rgb * step(maxValue, step(threshold, centerColor.r)) * multiplier), 1.0);
    }
);

#else

// 片元着色器
extern const char _thresholdedNonMaximumSuppression_fragment_shader[]=SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;

 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 uniform float threshold;

 void main()
 {
     float bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);
     float leftColor = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightColor = texture2D(inputImageTexture, rightTextureCoordinate).r;
     float topColor = texture2D(inputImageTexture, topTextureCoordinate).r;
     float topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate).r;

     // Use a tiebreaker for pixels to the left and immediately above this one
     float multiplier = 1.0 - step(centerColor.r, topColor);
     multiplier = multiplier * (1.0 - step(centerColor.r, topLeftColor));
     multiplier = multiplier * (1.0 - step(centerColor.r, leftColor));
     multiplier = multiplier * (1.0 - step(centerColor.r, bottomLeftColor));

     float maxValue = max(centerColor.r, bottomColor);
     maxValue = max(maxValue, bottomRightColor);
     maxValue = max(maxValue, rightColor);
     maxValue = max(maxValue, topRightColor);

     float finalValue = centerColor.r * step(maxValue, centerColor.r) * multiplier;
     finalValue = step(threshold, finalValue);

     gl_FragColor = vec4(finalValue, finalValue, finalValue, 1.0);
     //
     //     gl_FragColor = vec4((centerColor.rgb * step(maxValue, step(threshold, centerColor.r)) * multiplier), 1.0);
 }
);

#endif




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

