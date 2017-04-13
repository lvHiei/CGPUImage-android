/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGammaFilter.h"

// 片元着色器
const char _gamma_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform float gamma;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   gl_FragColor = vec4(pow(textureColor.rgb, vec3(gamma)), textureColor.w);\n"
"}\n"
;

GPUImageGammaFilter::GPUImageGammaFilter()
    : GPUImageFilter(_gamma_fragment_shader)
{
    m_fGamma = 1.5f;
}


GPUImageGammaFilter::~GPUImageGammaFilter()
{

}

void GPUImageGammaFilter::setGamma(int percent)
{
    float max = 3.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setGamma(value);
}

bool GPUImageGammaFilter::createProgramExtra()
{
    m_iGammaLocation = glGetUniformLocation(m_uProgram, "gamma");
    return true;
}

bool GPUImageGammaFilter::beforeDrawExtra()
{
    glUniform1f(m_iGammaLocation, m_fGamma);
    return true;
}

bool GPUImageGammaFilter::onDrawExtra()
{
    return true;
}


void GPUImageGammaFilter::setGamma(float gamma)
{
    m_fGamma = gamma;
}

