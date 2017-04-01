/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageColorMatrixFilter.h"



// 顶点着色器
const char _colorMatrix_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"

"varying vec2 textureCoordinate;\n"

"void main()\n"
"{\n"
"	gl_Position = position;\n"
"	textureCoordinate = inputTextureCoordinate.xy;\n"
"}\n"
;

// 片元着色器
const char _colorMatrix_fragment_shader[]=
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
const float colorMatrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
};

GPUImageColorMatrixFilter::GPUImageColorMatrixFilter()
        :GPUImageFilter()
{
    m_fIntensity = 1.0f;

    memcpy(m_pColorMatrix, colorMatrix, 16*sizeof(float));
}

GPUImageColorMatrixFilter::~GPUImageColorMatrixFilter()
{

}

void GPUImageColorMatrixFilter::setIntensity(float intensity)
{
    if(intensity < 0.0f){
        intensity = 0.0f;
    }

    if(intensity > 1.0f){
        intensity = 1.0f;
    }

    m_fIntensity = intensity;
}

bool GPUImageColorMatrixFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_colorMatrix_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _colorMatrix_vertex_shader);
    length = expLen;

    return true;
}

bool GPUImageColorMatrixFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(_colorMatrix_fragment_shader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

    sprintf(fragment, _colorMatrix_fragment_shader);
    length = expLen;
    return true;
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
