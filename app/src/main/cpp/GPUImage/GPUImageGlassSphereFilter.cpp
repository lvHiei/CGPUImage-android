/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGlassSphereFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _glassSphere_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform highp vec2 center;\n"
"uniform highp float radius;\n"
"uniform highp float aspectRatio;\n"
"uniform highp float refractiveIndex;\n"
"// uniform vec3 lightPosition;\n"
"const highp vec3 lightPosition = vec3(-0.5, 0.5, 1.0);\n"
"const highp vec3 ambientLightPosition = vec3(0.0, 0.0, 1.0);\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));\n"
"    highp float distanceFromCenter = distance(center, textureCoordinateToUse);\n"
"    lowp float checkForPresenceWithinSphere = step(distanceFromCenter, radius);\n"
"\n"
"    distanceFromCenter = distanceFromCenter / radius;\n"
"\n"
"    highp float normalizedDepth = radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);\n"
"    highp vec3 sphereNormal = normalize(vec3(textureCoordinateToUse - center, normalizedDepth));\n"
"\n"
"    highp vec3 refractedVector = 2.0 * refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);\n"
"    refractedVector.xy = -refractedVector.xy;\n"
"\n"
"    highp vec3 finalSphereColor = texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5).rgb;\n"
"\n"
"    // Grazing angle lighting\n"
"    highp float lightingIntensity = 2.5 * (1.0 - pow(clamp(dot(ambientLightPosition, sphereNormal), 0.0, 1.0), 0.25));\n"
"    finalSphereColor += lightingIntensity;\n"
"\n"
"    // Specular lighting\n"
"    lightingIntensity  = clamp(dot(normalize(lightPosition), sphereNormal), 0.0, 1.0);\n"
"    lightingIntensity  = pow(lightingIntensity, 15.0);\n"
"    finalSphereColor += vec3(0.8, 0.8, 0.8) * lightingIntensity;\n"
"\n"
"    gl_FragColor = vec4(finalSphereColor, 1.0) * checkForPresenceWithinSphere;\n"
"}"
;

#else

// 片元着色器
extern const char _glassSphere_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"uniform vec2 center;\n"
"uniform float radius;\n"
"uniform float aspectRatio;\n"
"uniform float refractiveIndex;\n"
"// uniform vec3 lightPosition;\n"
"const vec3 lightPosition = vec3(-0.5, 0.5, 1.0);\n"
"const vec3 ambientLightPosition = vec3(0.0, 0.0, 1.0);\n"
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
"    vec3 refractedVector = 2.0 * refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);\n"
"    refractedVector.xy = -refractedVector.xy;\n"
"\n"
"    vec3 finalSphereColor = texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5).rgb;\n"
"\n"
"    // Grazing angle lighting\n"
"    float lightingIntensity = 2.5 * (1.0 - pow(clamp(dot(ambientLightPosition, sphereNormal), 0.0, 1.0), 0.25));\n"
"    finalSphereColor += lightingIntensity;\n"
"\n"
"    // Specular lighting\n"
"    lightingIntensity  = clamp(dot(normalize(lightPosition), sphereNormal), 0.0, 1.0);\n"
"    lightingIntensity  = pow(lightingIntensity, 15.0);\n"
"    finalSphereColor += vec3(0.8, 0.8, 0.8) * lightingIntensity;\n"
"\n"
"    gl_FragColor = vec4(finalSphereColor, 1.0) * checkForPresenceWithinSphere;\n"
"}"
;

#endif


GPUImageGlassSphereFilter::GPUImageGlassSphereFilter()
    : GPUImageSphereRefractionFilter(_glassSphere_fragment_shader)
{

}

GPUImageGlassSphereFilter::~GPUImageGlassSphereFilter() {

}

