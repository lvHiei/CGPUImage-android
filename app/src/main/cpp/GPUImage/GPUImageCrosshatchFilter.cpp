/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageCrosshatchFilter.h"



#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _crosshatch_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float crossHatchSpacing;
    uniform highp float lineWidth;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        highp float luminance = dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);

        lowp vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
        if (luminance < 1.00)
        {
            if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <= lineWidth)
            {
                colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
            }
        }
        if (luminance < 0.75)
        {
            if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <= lineWidth)
            {
                colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
            }
        }
        if (luminance < 0.50)
        {
            if (mod(textureCoordinate.x + textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)
            {
                colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
            }
        }
        if (luminance < 0.3)
        {
            if (mod(textureCoordinate.x - textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)
            {
                colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
            }
        }

        gl_FragColor = colorToDisplay;
    }
);

#else

// 片元着色器
extern const char _crosshatch_fragment_shader[]=SHANDER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform float crossHatchSpacing;
    uniform float lineWidth;

    const vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
     float luminance = dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);

     vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
     if (luminance < 1.00)
     {
         if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <= lineWidth)
         {
             colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
         }
     }
     if (luminance < 0.75)
     {
         if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <= lineWidth)
         {
             colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
         }
     }
     if (luminance < 0.50)
     {
         if (mod(textureCoordinate.x + textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)
         {
             colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
         }
     }
     if (luminance < 0.3)
     {
         if (mod(textureCoordinate.x - textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)
         {
             colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
         }
     }

     gl_FragColor = colorToDisplay;
    }
);

#endif



GPUImageCrosshatchFilter::GPUImageCrosshatchFilter()
    : GPUImageFilter(_crosshatch_fragment_shader)
{
    m_fCrossHatchSpacing = 0.03f;
    m_fLineWidth = 0.003f;

    m_iCrossHatchSpacingUniformLocation = -1;
    m_iLineWidthUniformLocation = -1;
}


GPUImageCrosshatchFilter::~GPUImageCrosshatchFilter()
{

}


bool GPUImageCrosshatchFilter::createProgramExtra()
{
    m_iCrossHatchSpacingUniformLocation = glGetUniformLocation(m_uProgram, "crossHatchSpacing");
    m_iLineWidthUniformLocation = glGetUniformLocation(m_uProgram, "lineWidth");

    return true;
}

bool GPUImageCrosshatchFilter::beforeDrawExtra()
{
    glUniform1f(m_iCrossHatchSpacingUniformLocation, m_fCrossHatchSpacing);
    glUniform1f(m_iLineWidthUniformLocation, m_fLineWidth);

    return true;
}

void GPUImageCrosshatchFilter::setCrossHatchSpacing(float crossHatchSpacing)
{
    float min = 1.0 / 1280;

    if(0 != m_iTextureWidth){
        min = 1.0 / m_iTextureWidth;
    }

    if(crossHatchSpacing < min){
        crossHatchSpacing = min;
    }

    m_fCrossHatchSpacing = crossHatchSpacing;
}

void GPUImageCrosshatchFilter::setLineWidth(float lineWidth)
{
    m_fLineWidth = lineWidth;
}