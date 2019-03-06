/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageStretchDistortionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _stretchDistortion_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp vec2 center;

    void main()
    {
        highp vec2 normCoord = 2.0 * textureCoordinate - 1.0;
        highp vec2 normCenter = 2.0 * center - 1.0;

        normCoord -= normCenter;
        mediump vec2 s = sign(normCoord);
        normCoord = abs(normCoord);
        normCoord = 0.5 * normCoord + 0.5 * smoothstep(0.25, 0.5, normCoord) * normCoord;
        normCoord = s * normCoord;

        normCoord += normCenter;

        mediump vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;


        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );

    }
);

#else


// 片元着色器
extern const char _stretchDistortion_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform vec2 center;

 void main()
 {
     vec2 normCoord = 2.0 * textureCoordinate - 1.0;
     vec2 normCenter = 2.0 * center - 1.0;

     normCoord -= normCenter;
     vec2 s = sign(normCoord);
     normCoord = abs(normCoord);
     normCoord = 0.5 * normCoord + 0.5 * smoothstep(0.25, 0.5, normCoord) * normCoord;
     normCoord = s * normCoord;

     normCoord += normCenter;

     vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;

     gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);
 }
);

#endif



GPUImageStretchDistortionFilter::GPUImageStretchDistortionFilter()
    : GPUImageFilter(_stretchDistortion_fragment_shader)
{
    m_pCenter[0] = 0.5f;
    m_pCenter[1] = 0.5f;

    m_iCenterUniformLocation = -1;
}

GPUImageStretchDistortionFilter::~GPUImageStretchDistortionFilter()
{

}

void GPUImageStretchDistortionFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

bool GPUImageStretchDistortionFilter::createProgramExtra()
{
    m_iCenterUniformLocation = glGetUniformLocation(m_uProgram, "center");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageStretchDistortionFilter::beforeDrawExtra()
{
    glUniform2fv(m_iCenterUniformLocation, 1, m_pCenter);
    return GPUImageFilter::beforeDrawExtra();
}

