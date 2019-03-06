/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePolarPixellateFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _polarPixellate_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp vec2 center;
    uniform highp vec2 pixelSize;


    void main()
    {
        highp vec2 normCoord = 2.0 * textureCoordinate - 1.0;
        highp vec2 normCenter = 2.0 * center - 1.0;

        normCoord -= normCenter;

        highp float r = length(normCoord); // to polar coords
        highp float phi = atan(normCoord.y, normCoord.x); // to polar coords

        r = r - mod(r, pixelSize.x) + 0.03;
        phi = phi - mod(phi, pixelSize.y);

        normCoord.x = r * cos(phi);
        normCoord.y = r * sin(phi);

        normCoord += normCenter;

        mediump vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;

        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );

    }
);

#else


// 片元着色器
extern const char _polarPixellate_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform vec2 center;
 uniform vec2 pixelSize;


 void main()
 {
     vec2 normCoord = 2.0 * textureCoordinate - 1.0;
     vec2 normCenter = 2.0 * center - 1.0;

     normCoord -= normCenter;

     float r = length(normCoord); // to polar coords
     float phi = atan(normCoord.y, normCoord.x); // to polar coords

     r = r - mod(r, pixelSize.x) + 0.03;
     phi = phi - mod(phi, pixelSize.y);

     normCoord.x = r * cos(phi);
     normCoord.y = r * sin(phi);

     normCoord += normCenter;

     vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;

     gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );

 }
);

#endif




GPUImagePolarPixellateFilter::GPUImagePolarPixellateFilter()
    : GPUImageFilter(_polarPixellate_fragment_shader)
{
    m_pPixelSzie[0] = 0.05f;
    m_pPixelSzie[1] = 0.05f;

    m_pCenter[0] = 0.5f;
    m_pCenter[1] = 0.5f;


    m_iCenterUniformLocation = -1;
    m_iPixelSzieUniformLocation = -1;
}

GPUImagePolarPixellateFilter::~GPUImagePolarPixellateFilter()
{

}

void GPUImagePolarPixellateFilter::setPixelSize(float x, float y)
{
    m_pPixelSzie[0] = x;
    m_pPixelSzie[1] = y;
}

void GPUImagePolarPixellateFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

bool GPUImagePolarPixellateFilter::createProgramExtra()
{
    m_iCenterUniformLocation = glGetUniformLocation(m_uProgram, "center");
    m_iPixelSzieUniformLocation = glGetUniformLocation(m_uProgram, "pixelSize");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePolarPixellateFilter::beforeDrawExtra()
{
    glUniform2fv(m_iCenterUniformLocation, 1, m_pCenter);
    glUniform2fv(m_iPixelSzieUniformLocation, 1, m_pPixelSzie);
    return GPUImageFilter::beforeDrawExtra();
}

