/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageStretchDistortionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _stretchDistortion_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform highp vec2 center;\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 normCoord = 2.0 * textureCoordinate - 1.0;\n"
"    highp vec2 normCenter = 2.0 * center - 1.0;\n"
"\n"
"    normCoord -= normCenter;\n"
"    mediump vec2 s = sign(normCoord);\n"
"    normCoord = abs(normCoord);\n"
"    normCoord = 0.5 * normCoord + 0.5 * smoothstep(0.25, 0.5, normCoord) * normCoord;\n"
"    normCoord = s * normCoord;\n"
"\n"
"    normCoord += normCenter;\n"
"\n"
"    mediump vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;\n"
"\n"
"\n"
"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );\n"
"\n"
"}"
;

#else


// 片元着色器
extern const char _stretchDistortion_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform vec2 center;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 normCoord = 2.0 * textureCoordinate - 1.0;\n"
"    vec2 normCenter = 2.0 * center - 1.0;\n"
"\n"
"    normCoord -= normCenter;\n"
"    vec2 s = sign(normCoord);\n"
"    normCoord = abs(normCoord);\n"
"    normCoord = 0.5 * normCoord + 0.5 * smoothstep(0.25, 0.5, normCoord) * normCoord;\n"
"    normCoord = s * normCoord;\n"
"\n"
"    normCoord += normCenter;\n"
"\n"
"    vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;\n"
"\n"
"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
"}"
;

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

