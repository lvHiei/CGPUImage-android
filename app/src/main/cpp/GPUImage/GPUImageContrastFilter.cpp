/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageContrastFilter.h"
#include "GPUImageFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _contrast_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform lowp float contrast;\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.w);\n"
"}"
;

#else

// 片元着色器
extern const char _contrast_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform float contrast;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   // contrast filter \n"
"   vec4 contrastColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.a);\n"
"   gl_FragColor = contrastColor;\n"
"}\n"
;

#endif




GPUImageContrastFilter::GPUImageContrastFilter()
        :GPUImageFilter(_contrast_fragment_shader)
{
    m_fContrast = 1.0f;
}

GPUImageContrastFilter::~GPUImageContrastFilter()
{

}

void GPUImageContrastFilter::setContrast(int percent)
{
    float max = 4.0f;
    float min = 1.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setContrast(value);
}

bool GPUImageContrastFilter::createProgramExtra()
{
    m_iContrastLocation = glGetUniformLocation(m_uProgram, "contrast");
    return true;
}

bool GPUImageContrastFilter::beforeDrawExtra()
{
    glUniform1f(m_iContrastLocation, m_fContrast);
    return true;
}

bool GPUImageContrastFilter::onDrawExtra()
{
    return true;
}


void GPUImageContrastFilter::setContrast(float contrast)
{
    m_fContrast = contrast;
}

