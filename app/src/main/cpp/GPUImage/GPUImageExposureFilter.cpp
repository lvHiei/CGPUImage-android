/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageExposureFilter.h"


// 片元着色器
const char _exposure_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float exposure;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(textureColor.rgb * pow(2.0, exposure), textureColor.w);\n"
"}"
;

GPUImageExposureFilter::GPUImageExposureFilter()
    : GPUImageFilter(_exposure_fragment_shader)
{
    m_fExposure = 0.0f;

    m_iExposureUniformLocation = -1;
}

GPUImageExposureFilter::~GPUImageExposureFilter()
{

}

bool GPUImageExposureFilter::createProgramExtra()
{
    m_iExposureUniformLocation = glGetUniformLocation(m_uProgram, "exposure");
    return true;
}

bool GPUImageExposureFilter::beforeDrawExtra()
{
    glUniform1f(m_iExposureUniformLocation, m_fExposure);
    return true;
}

void GPUImageExposureFilter::setExposure(float exposure)
{
    m_fExposure = exposure;
}

void GPUImageExposureFilter::setExposure(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (10.0f - (-10.0f)) / 100;

    m_fExposure = 0.0f + incremental * percent;
}