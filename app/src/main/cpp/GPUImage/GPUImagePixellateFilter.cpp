/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePixellateFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _pixellate_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float fractionalWidthOfPixel;
    uniform highp float aspectRatio;

    void main()
    {
        highp vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);

        highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;
        gl_FragColor = texture2D(inputImageTexture, samplePos );
    }
);

#else

// 片元着色器
extern const char _pixellate_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform float fractionalWidthOfPixel;
 uniform float aspectRatio;

 void main()
 {
     vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);

     vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;
     gl_FragColor = texture2D(inputImageTexture, samplePos );
 }
);

#endif





GPUImagePixellateFilter::GPUImagePixellateFilter()
    : GPUImageFilter(_pixellate_fragment_shader)
{
    updateAspectRatio();

    m_fFractionalWidthOfAPixel = 0.05f;

    m_iAsepectRatioUniformLocation = -1;
    m_iFragUniformLocation = -1;
}


GPUImagePixellateFilter::GPUImagePixellateFilter(const char *fragment)
        : GPUImageFilter(fragment)
{
    updateAspectRatio();

    m_fFractionalWidthOfAPixel = 0.05f;

    m_iAsepectRatioUniformLocation = -1;
    m_iFragUniformLocation = -1;
}


GPUImagePixellateFilter::~GPUImagePixellateFilter()
{

}

void GPUImagePixellateFilter::setAspectRatio(float aspectRatio)
{
    m_fAspectRatio = aspectRatio;
}

void GPUImagePixellateFilter::setFractionalWidthOfAPixel(float fraction)
{
    GLfloat min = 1.0 / 1280.0;

    if(m_iTextureWidth != 0){
        min = 1.0 / m_iTextureWidth;
    }

    if(fraction < min){
        fraction = min;
    }

    m_fFractionalWidthOfAPixel = fraction;
}

bool GPUImagePixellateFilter::createProgramExtra()
{
    m_iFragUniformLocation = glGetUniformLocation(m_uProgram, "fractionalWidthOfPixel");
    m_iAsepectRatioUniformLocation = glGetUniformLocation(m_uProgram, "aspectRatio");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePixellateFilter::beforeDrawExtra()
{
    glUniform1f(m_iFragUniformLocation, m_fFractionalWidthOfAPixel);
    glUniform1f(m_iAsepectRatioUniformLocation, m_fAspectRatio);
    return GPUImageFilter::beforeDrawExtra();
}


void GPUImagePixellateFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateAspectRatio();
}

void GPUImagePixellateFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateAspectRatio();
}

void GPUImagePixellateFilter::updateAspectRatio()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fAspectRatio = isRotationSwapWidthAndHeight() ?
                     1.0 * m_iTextureHeight / m_iTextureWidth :
                     1.0 * m_iTextureWidth / m_iTextureHeight;
}

