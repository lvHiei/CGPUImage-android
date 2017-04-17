/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>

#include "GPUImageHueFilter.h"



// 片元着色器
extern const char _hue_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float hueAdjust;\n"
"const vec4  kRGBToYPrime = vec4 (0.299, 0.587, 0.114, 0.0);\n"
"const vec4  kRGBToI     = vec4 (0.595716, -0.274453, -0.321263, 0.0);\n"
"const vec4  kRGBToQ     = vec4 (0.211456, -0.522591, 0.31135, 0.0);\n"
"\n"
"const vec4  kYIQToR   = vec4 (1.0, 0.9563, 0.6210, 0.0);\n"
"const vec4  kYIQToG   = vec4 (1.0, -0.2721, -0.6474, 0.0);\n"
"const vec4  kYIQToB   = vec4 (1.0, -1.1070, 1.7046, 0.0);\n"
"\n"
"void main ()\n"
"{\n"
"    // Sample the input pixel\n"
"    vec4 color   = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    // Convert to YIQ\n"
"    float   YPrime  = dot (color, kRGBToYPrime);\n"
"    float   I      = dot (color, kRGBToI);\n"
"    float   Q      = dot (color, kRGBToQ);\n"
"\n"
"    // Calculate the hue and chroma\n"
"    float   hue     = atan (Q, I);\n"
"    float   chroma  = sqrt (I * I + Q * Q);\n"
"\n"
"    // Make the user's adjustments\n"
"    hue += (-hueAdjust); //why negative rotation?\n"
"\n"
"    // Convert back to YIQ\n"
"    Q = chroma * sin (hue);\n"
"    I = chroma * cos (hue);\n"
"\n"
"    // Convert back to RGB\n"
"    vec4    yIQ   = vec4 (YPrime, I, Q, 0.0);\n"
"    color.r = dot (yIQ, kYIQToR);\n"
"    color.g = dot (yIQ, kYIQToG);\n"
"    color.b = dot (yIQ, kYIQToB);\n"
"\n"
"    // Save the result\n"
"    gl_FragColor = color;\n"
"}"
;


GPUImageHueFilter::GPUImageHueFilter()
    : GPUImageFilter(_hue_fragment_shader)
{
    m_fHue = 90;
    m_iHueUniformLocation = -1;
}

GPUImageHueFilter::~GPUImageHueFilter()
{

}

void GPUImageHueFilter::setHue(float hue)
{
    m_fHue = fmodf(hue, 360.0) * M_PI / 180;
}

bool GPUImageHueFilter::createProgramExtra()
{
    m_iHueUniformLocation = glGetUniformLocation(m_uProgram, "hueAdjust");
    return true;
}

bool GPUImageHueFilter::beforeDrawExtra()
{
    glUniform1f(m_iHueUniformLocation, m_fHue);
    return true;
}


