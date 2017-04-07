/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageBulgeDistortionFilter.h"


//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]=
//"precision mediump float;\n"
//"varying vec2 textureCoordinate;\n"
//"\n"
//"uniform sampler2D inputImageTexture;\n"
//"\n"
//"uniform float aspectRatio;\n"
//"uniform vec2 center;\n"
//"uniform float radius;\n"
//"uniform float scale;\n"
//"\n"
//"void main()\n"
//"{\n"
//"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);\n"
//"    float dist = distance(center, textureCoordinateToUse);\n"
//"    textureCoordinateToUse.x = textureCoordinate.x;\n"
//"    textureCoordinateToUse.y = textureCoordinate.y;\n"
//"\n"
//"    if (dist < radius)\n"
//"    {\n"
//"        textureCoordinateToUse -= center;\n"
//"        float percent = 1.0 - ((radius - dist) / radius) * scale;\n"
//"        percent = percent * percent;\n"
//"\n"
//"        textureCoordinateToUse = textureCoordinateToUse * percent;\n"
//"        textureCoordinateToUse += center;\n"
//"        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
//"    }\nelse{gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);}"
//"\n"
//"\nif(textureCoordinateToUse.x==textureCoordinate.x && textureCoordinateToUse.y==textureCoordinate.y){gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);}else{gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);}"
////"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
//"}"
//;




//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]=
//"precision mediump float;\n"
//"varying vec2 textureCoordinate;\n"
//"\n"
//"uniform sampler2D inputImageTexture;\n"
//"\n"
//"uniform float aspectRatio;\n"
//"uniform vec2 center;\n"
//"uniform float radius;\n"
//"uniform float scale;\n"
//"\n"
//"void main()\n"
//"{\n"
//"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);\n"
//"    float dist = distance(center, textureCoordinateToUse);\n"
//"    textureCoordinateToUse = textureCoordinate;\n"
//"\n"
//"    if (dist < radius)\n"
//"    {\n"
//"        textureCoordinateToUse -= center;\n"
//"        float percent = 1.0 - ((radius - dist) / radius) * scale;\n"
//"        percent = percent * percent;\n"
//"\n"
//"        textureCoordinateToUse = textureCoordinateToUse * percent;\n"
//"        textureCoordinateToUse += center;\n"
//"    }\n"
//"\n"
//"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
//"}"
//;


//// 片元着色器
//const char _bulgeDistortion_fragment_shader[]=
//"precision mediump float;\n"
//"varying vec2 textureCoordinate;\n"
//"\n"
//"uniform sampler2D inputImageTexture;\n"
//"\n"
//"uniform float aspectRatio;\n"
//"uniform vec2 center;\n"
//"uniform float radius;\n"
//"uniform float scale;\n"
//"\n"
//"void main()\n"
//"{\n"
//"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);\n"
//"    float dist = distance(center, textureCoordinateToUse);\n"
//"    textureCoordinateToUse = textureCoordinate;\n"
//"\n"
//"    if (dist < radius)\n"
//"    {\n"
//"        textureCoordinateToUse -= center;\n"
//"        float percent = 1.0 - ((radius - dist) / radius) * scale;\n"
//"        percent = percent * percent;\n"
//"\n"
//"        textureCoordinateToUse = textureCoordinateToUse * percent;\n"
//"        textureCoordinateToUse += center;\n"
//"    }\n"
//"    else\n"
//"    {\n"
//"        textureCoordinateToUse = textureCoordinate;\n"
//"    }\n"
//"    gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
//"}"
//;


// 不知道为什么 上面三个shader写法都不行，下面这个正常

// 片元着色器
const char _bulgeDistortion_fragment_shader[]=
"precision mediump float;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform float aspectRatio;\n"
"uniform vec2 center;\n"
"uniform float radius;\n"
"uniform float scale;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, ((textureCoordinate.y - center.y) * aspectRatio) + center.y);\n"
"    float dist = distance(center, textureCoordinateToUse);\n"
"    textureCoordinateToUse = textureCoordinate;\n"
"\n"
"    if (dist < radius)\n"
"    {\n"
"        textureCoordinateToUse -= center;\n"
"        float percent = 1.0 - ((radius - dist) / radius) * scale;\n"
"        percent = percent * percent;\n"
"\n"
"        textureCoordinateToUse = textureCoordinateToUse * percent;\n"
"        textureCoordinateToUse += center;\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinateToUse);\n"
"    }\n"
"    else\n"
"    {\n"
"        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    }\n"
"}"
;



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
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - (-1.0f)) / 100;

    m_fScale = -1.0f + incremental * percent;
}