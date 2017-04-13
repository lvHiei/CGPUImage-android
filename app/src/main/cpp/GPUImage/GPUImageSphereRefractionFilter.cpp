/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSphereRefractionFilter.h"


// 片元着色器
const char _sphereRefraction_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform vec2 center;\n"
"uniform float radius;\n"
"uniform float aspectRatio;\n"
"uniform float refractiveIndex;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    float distanceFromCenter = distance(center, textureCoordinateToUse);\n"
"    float checkForPresenceWithinSphere = step(distanceFromCenter, radius);\n"
"\n"
"    distanceFromCenter = distanceFromCenter / radius;\n"
"\n"
"    float normalizedDepth = radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);\n"
"    vec3 sphereNormal = normalize(vec3(textureCoordinateToUse - center, normalizedDepth));\n"
"\n"
"    vec3 refractedVector = refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);\n"
"\n"
"    gl_FragColor = texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5) * checkForPresenceWithinSphere;\n"
"}"
;


GPUImageSphereRefractionFilter::GPUImageSphereRefractionFilter()
    : GPUImageFilter(_sphereRefraction_fragment_shader)
{
    m_fAspectRatio = 720.0f/1280.0f;

    m_fRadius = 0.25f;
//    m_fRadius = 0.15f;
    m_fRefractiveIndex = 0.71f;

    m_pCenter[0] = 0.5f;
    m_pCenter[1] = 0.5f;

    m_iRadiusUniformLocation = -1;
    m_iCenterUniformLocation = -1;
    m_iAspectRatioUniformLocation = -1;
    m_iRefractiveIndexUniformLocation = -1;
}

GPUImageSphereRefractionFilter::~GPUImageSphereRefractionFilter()
{

}

void GPUImageSphereRefractionFilter::setCenter(float x, float y)
{
    m_pCenter[0] = x;
    m_pCenter[1] = y;
}

void GPUImageSphereRefractionFilter::setRadius(float radius)
{
    m_fRadius = radius;
}

void GPUImageSphereRefractionFilter::setRefractiveIndex(float refractiveIndex)
{
    m_fRefractiveIndex = refractiveIndex;
}

void GPUImageSphereRefractionFilter::setAspectRatio(float aspectRatio)
{
    m_fAspectRatio = aspectRatio;
}

void GPUImageSphereRefractionFilter::setRadius(int percent)
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

bool GPUImageSphereRefractionFilter::createProgramExtra()
{
    m_iCenterUniformLocation = glGetUniformLocation(m_uProgram, "center");
    m_iRadiusUniformLocation = glGetUniformLocation(m_uProgram, "radius");
    m_iAspectRatioUniformLocation = glGetUniformLocation(m_uProgram, "aspectRatio");
    m_iRefractiveIndexUniformLocation = glGetUniformLocation(m_uProgram, "refractiveIndex");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageSphereRefractionFilter::beforeDrawExtra()
{
    glUniform2fv(m_iCenterUniformLocation, 1, m_pCenter);
    glUniform1f(m_iRadiusUniformLocation, m_fRadius);
    glUniform1f(m_iAspectRatioUniformLocation, m_fAspectRatio);
    glUniform1f(m_iRefractiveIndexUniformLocation, m_fRefractiveIndex);

    return GPUImageFilter::beforeDrawExtra();
}



