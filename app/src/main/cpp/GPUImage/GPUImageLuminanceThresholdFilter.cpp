/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLuminanceThresholdFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _luminanceThreshold_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform highp float threshold;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        highp float luminance = dot(textureColor.rgb, W);
        highp float thresholdResult = step(threshold, luminance);

        gl_FragColor = vec4(vec3(thresholdResult), textureColor.w);
    }
);


#else


// 片元着色器
extern const char _luminanceThreshold_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float threshold;

 const vec3 W = vec3(0.2125, 0.7154, 0.0721);

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
     float luminance = dot(textureColor.rgb, W);
     float thresholdResult = step(threshold, luminance);

     gl_FragColor = vec4(vec3(thresholdResult), textureColor.w);
 }
);


#endif


GPUImageLuminanceThresholdFilter::GPUImageLuminanceThresholdFilter()
    : GPUImageFilter(_luminanceThreshold_fragment_shader)
{
    m_fThreshold = 0.5f;
    m_iThresholdUniformLocation = -1;
}

GPUImageLuminanceThresholdFilter::~GPUImageLuminanceThresholdFilter()
{

}

void GPUImageLuminanceThresholdFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

void GPUImageLuminanceThresholdFilter::setThreshold(int percent)
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

bool GPUImageLuminanceThresholdFilter::createProgramExtra()
{
    m_iThresholdUniformLocation = glGetUniformLocation(m_uProgram, "threshold");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageLuminanceThresholdFilter::beforeDrawExtra()
{
    glUniform1f(m_iThresholdUniformLocation, m_fThreshold);
    return GPUImageFilter::beforeDrawExtra();
}

