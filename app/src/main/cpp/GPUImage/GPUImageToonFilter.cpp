/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageToonFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _toon_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float intensity;
    uniform highp float threshold;
    uniform highp float quantizationLevels;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
        float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
        float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
        float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
        float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
        float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

        float mag = length(vec2(h, v));

        vec3 posterizedImageColor = floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;

        float thresholdTest = 1.0 - step(threshold, mag);

        gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);
    }
);

#else

// 片元着色器
extern const char _toon_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform float intensity;
 uniform float threshold;
 uniform float quantizationLevels;

 const vec3 W = vec3(0.2125, 0.7154, 0.0721);

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
     float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

     float mag = length(vec2(h, v));

     vec3 posterizedImageColor = floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;

     float thresholdTest = 1.0 - step(threshold, mag);

     gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);
 }
);

#endif



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

void GPUImageToonFilter::setQuantizationLevels(float quantizationLevels)
{
    m_fQuantizationLevels = quantizationLevels;
}


void GPUImageToonFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

