/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSwirlFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _swirl_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp vec2 center;
    uniform highp float radius;
    uniform highp float angle;

    void main()
    {
        highp vec2 textureCoordinateToUse = textureCoordinate;
        highp float dist = distance(center, textureCoordinate);
        if (dist < radius)
        {
            textureCoordinateToUse -= center;
            highp float percent = (radius - dist) / radius;
            highp float theta = percent * percent * angle * 8.0;
            highp float s = sin(theta);
            highp float c = cos(theta);
            textureCoordinateToUse = vec2(dot(textureCoordinateToUse, vec2(c, -s)), dot(textureCoordinateToUse, vec2(s, c)));
            textureCoordinateToUse += center;
        }

        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );

    }
);

#else


// 片元着色器
extern const char _swirl_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform vec2 center;
 uniform float radius;
 uniform float angle;

 void main()
 {
     vec2 textureCoordinateToUse = textureCoordinate;
     float dist = distance(center, textureCoordinate);
     if (dist < radius)
     {
         textureCoordinateToUse -= center;
         float percent = (radius - dist) / radius;
         float theta = percent * percent * angle * 8.0;
         float s = sin(theta);
         float c = cos(theta);
         textureCoordinateToUse = vec2(dot(textureCoordinateToUse, vec2(c, -s)), dot(textureCoordinateToUse, vec2(s, c)));
         textureCoordinateToUse += center;
         gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
     }else{
         gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
     }

//     ;
 }
);

#endif



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

