/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageColorMatrixFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _colorMatrix_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform lowp mat4 colorMatrix;
    uniform lowp float intensity;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 outputColor = textureColor * colorMatrix;

        gl_FragColor = (intensity * outputColor) + ((1.0 - intensity) * textureColor);
    }
);

#else

// 片元着色器
extern const char _colorMatrix_fragment_shader[]=SHADER_STR(
    precision mediump float;
    uniform sampler2D inputImageTexture;
    varying vec2 textureCoordinate;
    uniform mat4 colorMatrix;
    uniform float intensity;

    void main()
    {
    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
    //sepia filter
    vec4 outputColor = textureColor * colorMatrix;
    vec4 sepiaColor = (intensity * outputColor) + ((1.0 - intensity) * textureColor);
    gl_FragColor = sepiaColor;
    }
);

#endif


/*
 * 转换矩阵
 */
const GLfloat colorMatrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
};

GPUImageColorMatrixFilter::GPUImageColorMatrixFilter()
        :GPUImageFilter(_colorMatrix_fragment_shader)
{
    m_fIntensity = 1.0f;

    memcpy(m_pColorMatrix, colorMatrix, 16*sizeof(float));
}

GPUImageColorMatrixFilter::~GPUImageColorMatrixFilter()
{

}

void GPUImageColorMatrixFilter::setIntensity(int percent)
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
    setIntensity(value);
}

bool GPUImageColorMatrixFilter::createProgramExtra()
{
    m_iIntensityLocation =  glGetUniformLocation(m_uProgram, "intensity");
    m_iColorMatrixLocation =  glGetUniformLocation(m_uProgram, "colorMatrix");
    return true;
}

bool GPUImageColorMatrixFilter::beforeDrawExtra()
{
    glUniform1f(m_iIntensityLocation, m_fIntensity);
    glUniformMatrix4fv(m_iColorMatrixLocation, 1, false, m_pColorMatrix);

    return true;
}

bool GPUImageColorMatrixFilter::onDrawExtra()
{
    return true;
}


void GPUImageColorMatrixFilter::setIntensity(float intensity)
{
    m_fIntensity = intensity;
}


