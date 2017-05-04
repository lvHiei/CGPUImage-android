/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePolarPixellateFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _polarPixellate_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform highp vec2 center;\n"
"uniform highp vec2 pixelSize;\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 normCoord = 2.0 * textureCoordinate - 1.0;\n"
"    highp vec2 normCenter = 2.0 * center - 1.0;\n"
"\n"
"    normCoord -= normCenter;\n"
"\n"
"    highp float r = length(normCoord); // to polar coords \n"
"    highp float phi = atan(normCoord.y, normCoord.x); // to polar coords \n"
"\n"
"    r = r - mod(r, pixelSize.x) + 0.03;\n"
"    phi = phi - mod(phi, pixelSize.y);\n"
"\n"
"    normCoord.x = r * cos(phi);\n"
"    normCoord.y = r * sin(phi);\n"
"\n"
"    normCoord += normCenter;\n"
"\n"
"    mediump vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;\n"
"\n"
"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );\n"
"\n"
"}"
;

#else


// 片元着色器
extern const char _polarPixellate_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform vec2 center;\n"
"uniform vec2 pixelSize;\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    vec2 normCoord = 2.0 * textureCoordinate - 1.0;\n"
"    vec2 normCenter = 2.0 * center - 1.0;\n"
"\n"
"    normCoord -= normCenter;\n"
"\n"
"    float r = length(normCoord); // to polar coords\n"
"    float phi = atan(normCoord.y, normCoord.x); // to polar coords\n"
"\n"
"    r = r - mod(r, pixelSize.x) + 0.03;\n"
"    phi = phi - mod(phi, pixelSize.y);\n"
"\n"
"    normCoord.x = r * cos(phi);\n"
"    normCoord.y = r * sin(phi);\n"
"\n"
"    normCoord += normCenter;\n"
"\n"
"    vec2 textureCoordinateToUse = normCoord / 2.0 + 0.5;\n"
"\n"
"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse );\n"
"\n"
"}"
;

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

