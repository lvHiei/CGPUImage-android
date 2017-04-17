/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageColorMatrixFilter.h"

// 片元着色器
extern const char _colorMatrix_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform lowp mat4 colorMatrix;\n"
"uniform lowp float intensity;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   //sepia filter \n"
"   lowp vec4 outputColor = textureColor * colorMatrix;\n"
"   vec4 sepiaColor = (intensity * outputColor) + ((1.0 - intensity) * textureColor);\n"
"   gl_FragColor = sepiaColor;\n"
"}\n"
;

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


