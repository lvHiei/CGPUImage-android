/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMonochromeFilter.h"


// 片元着色器
const char _monochrome_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float intensity;\n"
"uniform vec3 filterColor;\n"
"\n"
"const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    //desat, then apply overlay blend\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float luminance = dot(textureColor.rgb, luminanceWeighting);\n"
"\n"
"    vec4 desat = vec4(vec3(luminance), 1.0);\n"
"\n"
"    //overlay\n"
"    vec4 outputColor = vec4(\n"
"            (desat.r < 0.5 ? (2.0 * desat.r * filterColor.r) : (1.0 - 2.0 * (1.0 - desat.r) * (1.0 - filterColor.r))),\n"
"            (desat.g < 0.5 ? (2.0 * desat.g * filterColor.g) : (1.0 - 2.0 * (1.0 - desat.g) * (1.0 - filterColor.g))),\n"
"            (desat.b < 0.5 ? (2.0 * desat.b * filterColor.b) : (1.0 - 2.0 * (1.0 - desat.b) * (1.0 - filterColor.b))),\n"
"            1.0\n"
"    );\n"
"\n"
"    //which is better, or are they equal?\n"
"    gl_FragColor = vec4( mix(textureColor.rgb, outputColor.rgb, intensity), textureColor.a);\n"
"}"
;


GPUImageMonochromeFilter::GPUImageMonochromeFilter()
    : GPUImageFilter(_monochrome_fragment_shader)
{
    m_fIntensity = 1.0f;

    m_iIntensityUniformLocation = -1;
    m_iColorUniformLocation = -1;

    m_pColor[0] = 0.6f;
    m_pColor[1] = 0.45f;
    m_pColor[2] = 0.3f;
}

GPUImageMonochromeFilter::~GPUImageMonochromeFilter()
{

}

void GPUImageMonochromeFilter::setIntensity(float intensity)
{
    m_fIntensity = intensity;
}

void GPUImageMonochromeFilter::setIntensity(int percent)
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

void GPUImageMonochromeFilter::setColorRed(float red, float green, float blue)
{
    m_pColor[0] = red;
    m_pColor[1] = green;
    m_pColor[2] = blue;
}

bool GPUImageMonochromeFilter::createProgramExtra()
{
    m_iIntensityUniformLocation = glGetUniformLocation(m_uProgram, "intensity");
    m_iColorUniformLocation = glGetUniformLocation(m_uProgram, "filterColor");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageMonochromeFilter::beforeDrawExtra()
{
    glUniform1f(m_iIntensityUniformLocation, m_fIntensity);
    glUniform3fv(m_iColorUniformLocation, 1, m_pColor);
    return GPUImageFilter::beforeDrawExtra();
}

