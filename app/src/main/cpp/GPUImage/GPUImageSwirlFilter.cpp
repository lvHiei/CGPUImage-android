/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSwirlFilter.h"


// 片元着色器
extern const char _swirl_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform vec2 center;\n"
"uniform float radius;\n"
"uniform float angle;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 textureCoordinateToUse = textureCoordinate;\n"
"    float dist = distance(center, textureCoordinate);\n"
"    if (dist < radius)\n"
"    {\n"
"        textureCoordinateToUse -= center;\n"
"        float percent = (radius - dist) / radius;\n"
"        float theta = percent * percent * angle * 8.0;\n"
"        float s = sin(theta);\n"
"        float c = cos(theta);\n"
"        textureCoordinateToUse = vec2(dot(textureCoordinateToUse, vec2(c, -s)), dot(textureCoordinateToUse, vec2(s, c)));\n"
"        textureCoordinateToUse += center;\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
"    }else{\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    }\n"
"\n"
//"    ;\n"
"}"
;


GPUImageSwirlFilter::GPUImageSwirlFilter()
    : GPUImageFilter(_swirl_fragment_shader)
{
    m_fRadius = 0.5f;
    m_fAngle = 1.0f;

    m_pCenter[0] = 0.5f;
    m_pCenter[1] = 0.5f;

    m_iCenterUniformLocation = -1;
    m_iRadiusUniformLocation = -1;
    m_iAngleUniformLocation = -1;

}

GPUImageSwirlFilter::~GPUImageSwirlFilter()
{

}

void GPUImageSwirlFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

void GPUImageSwirlFilter::setRadius(float radius)
{
    m_fRadius = radius;
}

void GPUImageSwirlFilter::setRadius(int percent)
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
    setRadius(value);
}

void GPUImageSwirlFilter::setAngle(float angle)
{
    m_fAngle = angle;
}

bool GPUImageSwirlFilter::createProgramExtra()
{
    m_iCenterUniformLocation = glGetUniformLocation(m_uProgram, "center");
    m_iRadiusUniformLocation = glGetUniformLocation(m_uProgram, "radius");
    m_iAngleUniformLocation = glGetUniformLocation(m_uProgram, "angle");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageSwirlFilter::beforeDrawExtra()
{
    glUniform1f(m_iRadiusUniformLocation, m_fRadius);
    glUniform1f(m_iAngleUniformLocation, m_fAngle);
    glUniform2fv(m_iCenterUniformLocation, 1, m_pCenter);

    return GPUImageFilter::beforeDrawExtra();
}

