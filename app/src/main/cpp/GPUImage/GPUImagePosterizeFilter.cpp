/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePosterizeFilter.h"


// 片元着色器
const char _posterize_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float colorLevels;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = floor((textureColor * colorLevels) + vec4(0.5)) / colorLevels;\n"
"}"
;


GPUImagePosterizeFilter::GPUImagePosterizeFilter()
    : GPUImageFilter(_posterize_fragment_shader)
{
    m_iColorLevels = 10;

    m_iColorLevelsUniformLocation = -1;
}

GPUImagePosterizeFilter::~GPUImagePosterizeFilter()
{

}

void GPUImagePosterizeFilter::setColorLevels(int colorLevels)
{
    m_iColorLevels = colorLevels;
}

bool GPUImagePosterizeFilter::createProgramExtra()
{
    m_iColorLevelsUniformLocation = glGetUniformLocation(m_uProgram, "colorLevels");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePosterizeFilter::beforeDrawExtra()
{
    glUniform1f(m_iColorLevelsUniformLocation, m_iColorLevels);
    return GPUImageFilter::beforeDrawExtra();
}

