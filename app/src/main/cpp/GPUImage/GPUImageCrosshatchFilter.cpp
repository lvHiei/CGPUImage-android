/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageCrosshatchFilter.h"


// 片元着色器
extern const char _crosshatch_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform float crossHatchSpacing;\n"
"uniform float lineWidth;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    float luminance = dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);\n"
"\n"
"    vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    if (luminance < 1.00)\n"
"    {\n"
"        if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <= lineWidth)\n"
"        {\n"
"            colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);\n"
"        }\n"
"    }\n"
"    if (luminance < 0.75)\n"
"    {\n"
"        if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <= lineWidth)\n"
"        {\n"
"            colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);\n"
"        }\n"
"    }\n"
"    if (luminance < 0.50)\n"
"    {\n"
"        if (mod(textureCoordinate.x + textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)\n"
"        {\n"
"            colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);\n"
"        }\n"
"    }\n"
"    if (luminance < 0.3)\n"
"    {\n"
"        if (mod(textureCoordinate.x - textureCoordinate.y - (crossHatchSpacing / 2.0), crossHatchSpacing) <= lineWidth)\n"
"        {\n"
"            colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);\n"
"        }\n"
"    }\n"
"\n"
"    gl_FragColor = colorToDisplay;\n"
"}"
;

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