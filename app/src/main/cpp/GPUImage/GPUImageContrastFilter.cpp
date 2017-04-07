/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageContrastFilter.h"
#include "GPUImageFilter.h"

// 片元着色器
const char _contrast_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform float contrast;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   // contrast filter \n"
"   vec4 contrastColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.a);\n"
"   gl_FragColor = contrastColor;\n"
"}\n"
;

GPUImageContrastFilter::GPUImageContrastFilter()
        :GPUImageFilter(_contrast_fragment_shader)
{
    m_fContrast = 1.0f;
}

GPUImageContrastFilter::~GPUImageContrastFilter()
{

}

void GPUImageContrastFilter::setContrast(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (4.0f - 1.0f) / 100;

    m_fContrast = 1.0f + incremental * percent;
}

bool GPUImageContrastFilter::createProgramExtra()
{
    m_iContrastLocation = glGetUniformLocation(m_uProgram, "contrast");
    return true;
}

bool GPUImageContrastFilter::beforeDrawExtra()
{
    glUniform1f(m_iContrastLocation, m_fContrast);
    return true;
}

bool GPUImageContrastFilter::onDrawExtra()
{
    return true;
}