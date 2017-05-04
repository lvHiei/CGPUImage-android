/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageRGBFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _rgb_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform highp float redAdjustment;\n"
"uniform highp float greenAdjustment;\n"
"uniform highp float blueAdjustment;\n"
"\n"
"void main()\n"
"{\n"
"    highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(textureColor.r * redAdjustment, textureColor.g * greenAdjustment, textureColor.b * blueAdjustment, textureColor.a);\n"
"}"
;

#else

// 片元着色器
extern const char _rgb_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float redAdjustment;\n"
"uniform float greenAdjustment;\n"
"uniform float blueAdjustment;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(textureColor.r * redAdjustment, textureColor.g * greenAdjustment, textureColor.b * blueAdjustment, textureColor.a);\n"
"}"
;

#endif





GPUImageRGBFilter::GPUImageRGBFilter()
    :  GPUImageFilter(_rgb_fragment_shader)
{
    m_fRed = 1.0f;
    m_fGreen = 1.0f;
    m_fBlue = 1.0f;

    m_iRedUniformLocation = -1;
    m_iGreenUniformLocation = -1;
    m_iBlueUniformLocation = -1;
}

GPUImageRGBFilter::~GPUImageRGBFilter()
{

}

void GPUImageRGBFilter::setRed(float red)
{
    m_fRed = red;
}

void GPUImageRGBFilter::setGreen(float green)
{
    m_fGreen = green;
}

void GPUImageRGBFilter::setBlue(float blue)
{
    m_fBlue = blue;
}

bool GPUImageRGBFilter::createProgramExtra()
{
    m_iRedUniformLocation = glGetUniformLocation(m_uProgram, "redAdjustment");
    m_iGreenUniformLocation = glGetUniformLocation(m_uProgram, "greenAdjustment");
    m_iBlueUniformLocation = glGetUniformLocation(m_uProgram, "blueAdjustment");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageRGBFilter::beforeDrawExtra()
{
    glUniform1f(m_iRedUniformLocation, m_fRed);
    glUniform1f(m_iGreenUniformLocation, m_fGreen);
    glUniform1f(m_iBlueUniformLocation, m_fBlue);

    return GPUImageFilter::beforeDrawExtra();
}

