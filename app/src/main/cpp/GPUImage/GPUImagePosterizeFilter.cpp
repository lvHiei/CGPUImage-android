/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePosterizeFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _posterize_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform highp float colorLevels;

    void main()
    {
        highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        gl_FragColor = floor((textureColor * colorLevels) + vec4(0.5)) / colorLevels;
    }
);

#else


// 片元着色器
extern const char _posterize_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float colorLevels;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     gl_FragColor = floor((textureColor * colorLevels) + vec4(0.5)) / colorLevels;
 }
);


#endif



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

