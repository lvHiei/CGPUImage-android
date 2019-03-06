/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBrightnessFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _brightness_fragment_shader[]= SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform lowp float brightness;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);
    }
);

#else

// 片元着色器
extern const char _brightness_fragment_shader[]= SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float brightness;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);
 }
);
#endif



GPUImageBrightnessFilter::GPUImageBrightnessFilter()
    : GPUImageFilter(_brightness_fragment_shader)
{
    m_fBrightness = 0.0f;
//    m_fBrightness = 0.8f;

    m_iBrightUniformLocation = -1;
}

GPUImageBrightnessFilter::~GPUImageBrightnessFilter()
{

}

bool GPUImageBrightnessFilter::createProgramExtra()
{
    m_iBrightUniformLocation = glGetUniformLocation(m_uProgram, "brightness");
    return true;
}

bool GPUImageBrightnessFilter::beforeDrawExtra()
{
    glUniform1f(m_iBrightUniformLocation, m_fBrightness);
    return true;
}

void GPUImageBrightnessFilter::setBrightness(int percent)
{
    float max = 1.0f;
    float min = -1.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setBrightness(value);
}


void GPUImageBrightnessFilter::setBrightness(float brightness)
{
    m_fBrightness = brightness;
}

