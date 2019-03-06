/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageThresholdEdgeDetectionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _thresholdEdgeDetection_fragment_shader[] = SHADER_STR(
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
    uniform lowp float threshold;

    uniform float edgeStrength;

    void main()
    {
        //     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        //     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        //     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
        //     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
        float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
        float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
        float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;
        //     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
        //     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;
        //     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + leftIntensity + 2.0 * centerIntensity + rightIntensity;
        //     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomIntensity + 2.0 * centerIntensity + topIntensity;
        float h = (centerIntensity - topIntensity) + (bottomIntensity - centerIntensity);
        float v = (centerIntensity - leftIntensity) + (rightIntensity - centerIntensity);
        //     float h = (centerIntensity - topIntensity);
        //     float j = (topIntensity - centerIntensity);
        //     h = max(h,j);
        //     j = abs(h);
        //     float v = (centerIntensity - leftIntensity);

        float mag = length(vec2(h, v)) * edgeStrength;
        mag = step(threshold, mag);

        //     float mag = abs(h);

        //     gl_FragColor = vec4(h, h, h, 1.0);
        //     gl_FragColor = vec4(texture2D(inputImageTexture, textureCoordinate));
        //     gl_FragColor = vec4(h, centerIntensity, j, 1.0);
        gl_FragColor = vec4(mag, mag, mag, 1.0);
    }
);

#else


// 片元着色器
extern const char _thresholdEdgeDetection_fragment_shader[] = SHADER_STR(
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
 uniform float threshold;

 uniform float edgeStrength;

 void main()
 {
     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
     float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
     h = max(0.0, h);
     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;
     v = max(0.0, v);

     float mag = length(vec2(h, v)) * edgeStrength;
     mag = step(threshold, mag);

     gl_FragColor = vec4(vec3(mag), 1.0);
 }
);


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


