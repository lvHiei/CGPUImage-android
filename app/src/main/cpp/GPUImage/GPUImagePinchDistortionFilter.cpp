/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePinchDistortionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _pinchDistortion_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp float aspectRatio;
    uniform highp vec2 center;
    uniform highp float radius;
    uniform highp float scale;

    void main()
    {
        highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
        highp float dist = distance(center, textureCoordinateToUse);
        textureCoordinateToUse = textureCoordinate;

        if (dist < radius)
        {
            textureCoordinateToUse -= center;
            highp float percent = 1.0 + ((0.5 - dist) / 0.5) * scale;
            textureCoordinateToUse = textureCoordinateToUse * percent;
            textureCoordinateToUse += center;

            gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );
        }
        else
        {
            gl_FragColor = texture2D(inputImageTexture, textureCoordinate );
        }
    }
);


#else

// 片元着色器
extern const char _pinchDistortion_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform float aspectRatio;
 uniform vec2 center;
 uniform float radius;
 uniform float scale;

 void main()
 {
     vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
     float dist = distance(center, textureCoordinateToUse);
     textureCoordinateToUse = textureCoordinate;

     if (dist < radius)
     {
         textureCoordinateToUse -= center;
         float percent = 1.0 + ((0.5 - dist) / 0.5) * scale;
         textureCoordinateToUse = textureCoordinateToUse * percent;
         textureCoordinateToUse += center;

         gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );
     }
     else
     {
         gl_FragColor = texture2D(inputImageTexture, textureCoordinate );
     }
 }
);


#endif



GPUImagePinchDistortionFilter::GPUImagePinchDistortionFilter()
    : GPUImageFilter(_pinchDistortion_fragment_shader)
{
    m_fRadius = 1.0f;
    m_fScale = 0.5f;

    m_pCenter[0] = 0.5f;
    m_pCenter[1] = 0.5f;

    updateAspectRatio();

    m_iCenterUnifornLocation = -1;
    m_iRadiusUnifornLocation = -1;
    m_iScaleUnifornLocation = -1;
}

GPUImagePinchDistortionFilter::~GPUImagePinchDistortionFilter()
{

}

void GPUImagePinchDistortionFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

void GPUImagePinchDistortionFilter::setRadius(float radius)
{
    m_fRadius = radius;
}

void GPUImagePinchDistortionFilter::setScale(float scale)
{
    m_fScale = scale;
}

void GPUImagePinchDistortionFilter::setRadius(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (2.0f - 0.0f) / 100;

    m_fRadius = 0.0f + incremental * percent;
}

void GPUImagePinchDistortionFilter::setScale(int percent)
{
    float max = 2.0f;
    float min = -2.0f;

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


void GPUImagePinchDistortionFilter::setAspectRatio(float aspectRatio)
{
    m_fAspectRatio = aspectRatio;
}


bool GPUImagePinchDistortionFilter::createProgramExtra()
{
    m_iCenterUnifornLocation = glGetUniformLocation(m_uProgram, "center");
    m_iRadiusUnifornLocation = glGetUniformLocation(m_uProgram, "radius");
    m_iScaleUnifornLocation = glGetUniformLocation(m_uProgram, "scale");
    m_iAspectUnifornLocation= glGetUniformLocation(m_uProgram, "aspectRatio");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePinchDistortionFilter::beforeDrawExtra()
{
    glUniform1f(m_iAspectUnifornLocation, m_fAspectRatio);
    glUniform1f(m_iRadiusUnifornLocation, m_fRadius);
    glUniform1f(m_iScaleUnifornLocation, m_fScale);
    glUniform2fv(m_iCenterUnifornLocation, 1, m_pCenter);

    return GPUImageFilter::beforeDrawExtra();
}


void GPUImagePinchDistortionFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateAspectRatio();
}

void GPUImagePinchDistortionFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateAspectRatio();
}

void GPUImagePinchDistortionFilter::updateAspectRatio()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fAspectRatio = isRotationSwapWidthAndHeight() ?
                     1.0 * m_iTextureHeight / m_iTextureWidth :
                     1.0 * m_iTextureWidth / m_iTextureHeight;
}


