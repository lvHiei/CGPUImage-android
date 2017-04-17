/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageFalseColorFilter.h"


// 片元着色器
extern const char _falseColor_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float intensity;\n"
"uniform vec3 firstColor;\n"
"uniform vec3 secondColor;\n"
"\n"
"const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float luminance = dot(textureColor.rgb, luminanceWeighting);\n"
"\n"
"    gl_FragColor = vec4( mix(firstColor.rgb, secondColor.rgb, luminance), textureColor.a);\n"
"}"
;


GPUImageFalseColorFilter::GPUImageFalseColorFilter()
    : GPUImageFilter(_falseColor_fragment_shader)
{
    m_pFirstColor[0] = 0.0f;
    m_pFirstColor[1] = 0.0f;
    m_pFirstColor[2] = 0.5f;

    m_pSecondColor[0] = 1.0f;
    m_pSecondColor[1] = 0.0f;
    m_pSecondColor[2] = 0.0f;
}


GPUImageFalseColorFilter::~GPUImageFalseColorFilter()
{

}

bool GPUImageFalseColorFilter::createProgramExtra()
{
    m_iFirstColorUniformLocation = glGetUniformLocation(m_uProgram, "firstColor");
    m_iSecondColorUniformLocation = glGetUniformLocation(m_uProgram, "secondColor");

    return true;
}

bool GPUImageFalseColorFilter::beforeDrawExtra()
{
    glUniform3fv(m_iFirstColorUniformLocation, 1, m_pFirstColor);
    glUniform3fv(m_iSecondColorUniformLocation, 1, m_pSecondColor);

    return true;
}

void GPUImageFalseColorFilter::setFirstColorRed(float red, float green, float blue)
{
    m_pFirstColor[0] = red;
    m_pFirstColor[1] = green;
    m_pFirstColor[2] = blue;
}

void GPUImageFalseColorFilter::setSecondColorRed(float red, float green, float blue)
{
    m_pSecondColor[0] = red;
    m_pSecondColor[1] = green;
    m_pSecondColor[2] = blue;
}
