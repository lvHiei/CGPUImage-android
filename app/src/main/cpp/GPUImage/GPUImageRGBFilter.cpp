/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageRGBFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _rgb_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform highp float redAdjustment;
    uniform highp float greenAdjustment;
    uniform highp float blueAdjustment;

    void main()
    {
        highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        gl_FragColor = vec4(textureColor.r * redAdjustment, textureColor.g * greenAdjustment, textureColor.b * blueAdjustment, textureColor.a);
    }
);

#else

// 片元着色器
extern const char _rgb_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float redAdjustment;
 uniform float greenAdjustment;
 uniform float blueAdjustment;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     gl_FragColor = vec4(textureColor.r * redAdjustment, textureColor.g * greenAdjustment, textureColor.b * blueAdjustment, textureColor.a);
 }
);

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

