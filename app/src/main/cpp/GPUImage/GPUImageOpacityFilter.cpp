/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageOpacityFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _opacity_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform lowp float opacity;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        gl_FragColor = vec4(textureColor.rgb, textureColor.a * opacity);
    }
);


#else

// 片元着色器
extern const char _opacity_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float opacity;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     gl_FragColor = vec4(textureColor.rgb, textureColor.a * opacity);
 }
);


#endif



GPUImageOpacityFilter::GPUImageOpacityFilter()
    : GPUImageFilter(_opacity_fragment_shader)
{
    m_fOpacity = 1.0f;
    m_iOpacityUniformLocation = -1;
}

GPUImageOpacityFilter::~GPUImageOpacityFilter()
{

}

void GPUImageOpacityFilter::setOpacity(float opacity)
{
    m_fOpacity = opacity;
}

void GPUImageOpacityFilter::setOpacity(int percent)
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
    setOpacity(value);
}

bool GPUImageOpacityFilter::createProgramExtra()
{
    m_iOpacityUniformLocation = glGetUniformLocation(m_uProgram, "opacity");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageOpacityFilter::beforeDrawExtra()
{
    glUniform1f(m_iOpacityUniformLocation, m_fOpacity);
    return GPUImageFilter::beforeDrawExtra();
}



