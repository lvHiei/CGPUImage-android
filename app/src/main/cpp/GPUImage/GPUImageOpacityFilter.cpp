/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageOpacityFilter.h"


// 片元着色器
const char _opacity_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float opacity;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(textureColor.rgb, textureColor.a * opacity);\n"
"}"
;


GPUImageOpacityFilter::GPUImageOpacityFilter()
    : GPUImageFilter(_opacity_fragment_shader)
{

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
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fOpacity = 0.0f + incremental * percent;
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



