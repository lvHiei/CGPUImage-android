/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageVignetteFilter.h"


// 片元着色器
extern const char _vignette_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform vec2 vignetteCenter;\n"
"uniform vec3 vignetteColor;\n"
"uniform float vignetteStart;\n"
"uniform float vignetteEnd;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 sourceImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float d = distance(textureCoordinate, vec2(vignetteCenter.x, vignetteCenter.y));\n"
"    float percent = smoothstep(vignetteStart, vignetteEnd, d);\n"
"    gl_FragColor = vec4(mix(sourceImageColor.rgb, vignetteColor, percent), sourceImageColor.a);\n"
"}"
;


GPUImageVignetteFilter::GPUImageVignetteFilter()
    : GPUImageFilter(_vignette_fragment_shader)
{
    m_fVignetteStart = 0.3f;
    m_fVignetteEnd = 0.75f;

    m_pVignetteCenter[0] = 0.5f;
    m_pVignetteCenter[1] = 0.5f;

    m_pVignetteColor[0] = 0.0f;
    m_pVignetteColor[1] = 0.0f;
    m_pVignetteColor[2] = 0.0f;

    m_iVignetteCenterUniformLocation = -1;
    m_iVignetteColorUniformLocation = -1;
    m_iVignetteStartUniformLocation = -1;
    m_iVignetteEndUniformLocation = -1;
}

GPUImageVignetteFilter::~GPUImageVignetteFilter()
{

}

void GPUImageVignetteFilter::setVignetteCenter(float x, float y)
{
    m_pVignetteCenter[0] = x;
    m_pVignetteCenter[1] = y;
}

void GPUImageVignetteFilter::setVignetteColor(float red, float green, float blue)
{
    m_pVignetteColor[0] = red;
    m_pVignetteColor[1] = green;
    m_pVignetteColor[2] = blue;
}

void GPUImageVignetteFilter::setVignetteStart(float start)
{
    m_fVignetteStart = start;
}

void GPUImageVignetteFilter::setVignetteEnd(float end)
{
    m_fVignetteEnd = end;
}

bool GPUImageVignetteFilter::createProgramExtra()
{
    m_iVignetteCenterUniformLocation = glGetUniformLocation(m_uProgram, "vignetteCenter");
    m_iVignetteColorUniformLocation = glGetUniformLocation(m_uProgram, "vignetteColor");
    m_iVignetteStartUniformLocation = glGetUniformLocation(m_uProgram, "vignetteStart");
    m_iVignetteEndUniformLocation = glGetUniformLocation(m_uProgram, "vignetteEnd");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageVignetteFilter::beforeDrawExtra()
{
    glUniform1f(m_iVignetteStartUniformLocation, m_fVignetteStart);
    glUniform1f(m_iVignetteEndUniformLocation, m_fVignetteEnd);
    glUniform2fv(m_iVignetteCenterUniformLocation, 1, m_pVignetteCenter);
    glUniform3fv(m_iVignetteColorUniformLocation, 1, m_pVignetteColor);

    return GPUImageFilter::beforeDrawExtra();
}


