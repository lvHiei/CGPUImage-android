/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBrightnessFilter.h"

// 片元着色器
const char _brightness_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float brightness;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);\n"
"}"
;



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
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - (-1.0f)) / 100;

    m_fBrightness = -1.0f + incremental * percent;
}