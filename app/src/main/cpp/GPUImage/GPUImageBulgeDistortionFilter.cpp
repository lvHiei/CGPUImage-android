/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBulgeDistortionFilter.h"


//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]= SHADER_STR(
//    precision mediump float;
//    varying vec2 textureCoordinate;
//
//    uniform sampler2D inputImageTexture;
//
//    uniform float aspectRatio;
//    uniform vec2 center;
//    uniform float radius;
//    uniform float scale;
//
//    void main()
//    {
//        vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);
//        float dist = distance(center, textureCoordinateToUse);
//        textureCoordinateToUse.x = textureCoordinate.x;
//        textureCoordinateToUse.y = textureCoordinate.y;
//
//        if (dist < radius)
//        {
//            textureCoordinateToUse -= center;
//            float percent = 1.0 - ((radius - dist) / radius) * scale;
//            percent = percent * percent;
//
//            textureCoordinateToUse = textureCoordinateToUse * percent;
//            textureCoordinateToUse += center;
//            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//        } else{gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);}
//
//        if(textureCoordinateToUse.x==textureCoordinate.x && textureCoordinateToUse.y==textureCoordinate.y)
//        {
//            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//        }else{
//            gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
//        }
////        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
//    }
//);
//



//
//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]= SHADER_STR(
//    precision mediump float;
//    varying vec2 textureCoordinate;
//
//    uniform sampler2D inputImageTexture;
//
//    uniform float aspectRatio;
//    uniform vec2 center;
//    uniform float radius;
//    uniform float scale;
//
//    void main()
//    {
//        vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);
//        float dist = distance(center, textureCoordinateToUse);
//        textureCoordinateToUse = textureCoordinate;
//
//        if (dist < radius)
//        {
//            textureCoordinateToUse -= center;
//            float percent = 1.0 - ((radius - dist) / radius) * scale;
//            percent = percent * percent;
//
//            textureCoordinateToUse = textureCoordinateToUse * percent;
//            textureCoordinateToUse += center;
//        }
//
//        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
//    }
//);

//
//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]= SHADER_STR(
//    precision mediump float;
//    varying vec2 textureCoordinate;
//
//    uniform sampler2D inputImageTexture;
//
//    uniform float aspectRatio;
//    uniform vec2 center;
//    uniform float radius;
//    uniform float scale;
//
//    void main()
//    {
//        vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);
//        float dist = distance(center, textureCoordinateToUse);
//        textureCoordinateToUse = textureCoordinate;
//
//        if (dist < radius)
//        {
//            textureCoordinateToUse -= center;
//            float percent = 1.0 - ((radius - dist) / radius) * scale;
//            percent = percent * percent;
//
//            textureCoordinateToUse = textureCoordinateToUse * percent;
//            textureCoordinateToUse += center;
//        }
//        else
//        {
//            textureCoordinateToUse = textureCoordinate;
//        }
//        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
//    }
//);


// 不知道为什么 上面三个shader写法都不行，下面这个正常


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _bulgeDistortion_fragment_shader[]= SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float aspectRatio;
    uniform highp vec2 center;
    uniform highp float radius;
    uniform highp float scale;

    void main()
    {
        highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);
        highp float dist = distance(center, textureCoordinateToUse);
        textureCoordinateToUse = textureCoordinate;

        if (dist < radius)
        {
            textureCoordinateToUse -= center;
            highp float percent = 1.0 - ((radius - dist) / radius) * scale;
            percent = percent * percent;

            textureCoordinateToUse = textureCoordinateToUse * percent;
            textureCoordinateToUse += center;
        }

        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );
    }
);

#else

// 片元着色器
extern const char _bulgeDistortion_fragment_shader[]= SHADER_STR(
     precision mediump float;

     varying vec2 textureCoordinate;

     uniform sampler2D inputImageTexture;

     uniform float aspectRatio;
     uniform vec2 center;
     uniform float radius;
     uniform float scale;

     void main()
     {
         vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);
         float dist = distance(center, textureCoordinateToUse);
         textureCoordinateToUse = textureCoordinate;

         if (dist < radius)
         {
             textureCoordinateToUse -= center;
             float percent = 1.0 - ((radius - dist) / radius) * scale;
             percent = percent * percent;

             textureCoordinateToUse = textureCoordinateToUse * percent;
             textureCoordinateToUse += center;
             gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
         }
         else
         {
             gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
         }
     }
);

#endif



GPUImageBulgeDistortionFilter::GPUImageBulgeDistortionFilter()
    : GPUImageFilter(_bulgeDistortion_fragment_shader)
{
    m_fAspectRatio = 16.0/9;
//    m_fAspectRatio = 1.0;

    m_fRadius = 0.25f;
    m_fScale = 0.5f;

    m_pCenter[0] = 0.5;
    m_pCenter[1] = 0.5;

    m_iCenterUniformLocation = -1;
    m_iRadiusUniformLocation = -1;
    m_iScaleUniformLocation = -1;
    m_iAspectRatioUniformLocation = -1;
}

GPUImageBulgeDistortionFilter::~GPUImageBulgeDistortionFilter()
{

}

bool GPUImageBulgeDistortionFilter::createProgramExtra()
{
    m_iAspectRatioUniformLocation = glGetUniformLocation(m_uProgram, "aspectRatio");
    m_iCenterUniformLocation = glGetUniformLocation(m_uProgram, "center");
    m_iRadiusUniformLocation = glGetUniformLocation(m_uProgram, "radius");
    m_iScaleUniformLocation = glGetUniformLocation(m_uProgram, "scale");

    return true;
}

bool GPUImageBulgeDistortionFilter::beforeDrawExtra()
{
    glUniform1f(m_iAspectRatioUniformLocation, m_fAspectRatio);
    glUniform1f(m_iRadiusUniformLocation, m_fRadius);
    glUniform1f(m_iScaleUniformLocation, m_fScale);
    glUniform2fv(m_iCenterUniformLocation, 1, m_pCenter);
    return true;
}

void GPUImageBulgeDistortionFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

void GPUImageBulgeDistortionFilter::setAspectRatio(float aspectRatio)
{
    m_fAspectRatio = aspectRatio;
}

void GPUImageBulgeDistortionFilter::setRadius(float radius)
{
    m_fRadius = radius;
}

void GPUImageBulgeDistortionFilter::setScale(float scale)
{
    m_fScale = scale;
}

void GPUImageBulgeDistortionFilter::setScale(int percent)
{
    float max = 1.0f;
    float min = -1.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setScale(value);
}