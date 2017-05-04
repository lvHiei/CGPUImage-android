/**
* Created by lvHiei on 17-4-10.
* This is a project of GPUImage implemented with c++, you can
* use it free. if you find some bug please send me a email.
* My Email is majun_1523@163.com.
*/

#include "GPUImageKuwaharaFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _kuwahara_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"uniform sampler2D inputImageTexture;\n"
"uniform int radius;\n"
"\n"
"precision highp float;\n"
"\n"
"const vec2 src_size = vec2 (1.0 / 768.0, 1.0 / 1024.0);\n"
"\n"
"void main (void)\n"
"{\n"
"    vec2 uv = textureCoordinate;\n"
"    float n = float((radius + 1) * (radius + 1));\n"
"    int i; int j;\n"
"    vec3 m0 = vec3(0.0); vec3 m1 = vec3(0.0); vec3 m2 = vec3(0.0); vec3 m3 = vec3(0.0);\n"
"    vec3 s0 = vec3(0.0); vec3 s1 = vec3(0.0); vec3 s2 = vec3(0.0); vec3 s3 = vec3(0.0);\n"
"    vec3 c;\n"
"\n"
"    for (j = -radius; j <= 0; ++j)  {\n"
"        for (i = -radius; i <= 0; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m0 += c;\n"
"            s0 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = -radius; j <= 0; ++j)  {\n"
"        for (i = 0; i <= radius; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m1 += c;\n"
"            s1 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = 0; j <= radius; ++j)  {\n"
"        for (i = 0; i <= radius; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m2 += c;\n"
"            s2 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = 0; j <= radius; ++j)  {\n"
"        for (i = -radius; i <= 0; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m3 += c;\n"
"            s3 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"\n"
"    float min_sigma2 = 1e+2;\n"
"    m0 /= n;\n"
"    s0 = abs(s0 / n - m0 * m0);\n"
"\n"
"    float sigma2 = s0.r + s0.g + s0.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m0, 1.0);\n"
"    }\n"
"\n"
"    m1 /= n;\n"
"    s1 = abs(s1 / n - m1 * m1);\n"
"\n"
"    sigma2 = s1.r + s1.g + s1.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m1, 1.0);\n"
"    }\n"
"\n"
"    m2 /= n;\n"
"    s2 = abs(s2 / n - m2 * m2);\n"
"\n"
"    sigma2 = s2.r + s2.g + s2.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m2, 1.0);\n"
"    }\n"
"\n"
"    m3 /= n;\n"
"    s3 = abs(s3 / n - m3 * m3);\n"
"\n"
"    sigma2 = s3.r + s3.g + s3.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m3, 1.0);\n"
"    }\n"
"}"
;

#else


// 片元着色器
extern const char _kuwahara_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"uniform sampler2D inputImageTexture;\n"
"uniform int radius;\n"
"\n"
"const vec2 src_size = vec2 (1.0 / 768.0, 1.0 / 1024.0);\n"
"\n"
"void main (void)\n"
"{\n"
"    vec2 uv = textureCoordinate;\n"
"    float n = float((radius + 1) * (radius + 1));\n"
"    int i; int j;\n"
"    vec3 m0 = vec3(0.0); vec3 m1 = vec3(0.0); vec3 m2 = vec3(0.0); vec3 m3 = vec3(0.0);\n"
"    vec3 s0 = vec3(0.0); vec3 s1 = vec3(0.0); vec3 s2 = vec3(0.0); vec3 s3 = vec3(0.0);\n"
"    vec3 c;\n"
"\n"
"    for (j = -radius; j <= 0; ++j)  {\n"
"        for (i = -radius; i <= 0; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m0 += c;\n"
"            s0 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = -radius; j <= 0; ++j)  {\n"
"        for (i = 0; i <= radius; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m1 += c;\n"
"            s1 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = 0; j <= radius; ++j)  {\n"
"        for (i = 0; i <= radius; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m2 += c;\n"
"            s2 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"    for (j = 0; j <= radius; ++j)  {\n"
"        for (i = -radius; i <= 0; ++i)  {\n"
"            c = texture2D(inputImageTexture, uv + vec2(i,j) * src_size).rgb;\n"
"            m3 += c;\n"
"            s3 += c * c;\n"
"        }\n"
"    }\n"
"\n"
"\n"
"    float min_sigma2 = 1e+2;\n"
"    m0 /= n;\n"
"    s0 = abs(s0 / n - m0 * m0);\n"
"\n"
"    float sigma2 = s0.r + s0.g + s0.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m0, 1.0);\n"
"    }\n"
"\n"
"    m1 /= n;\n"
"    s1 = abs(s1 / n - m1 * m1);\n"
"\n"
"    sigma2 = s1.r + s1.g + s1.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m1, 1.0);\n"
"    }\n"
"\n"
"    m2 /= n;\n"
"    s2 = abs(s2 / n - m2 * m2);\n"
"\n"
"    sigma2 = s2.r + s2.g + s2.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m2, 1.0);\n"
"    }\n"
"\n"
"    m3 /= n;\n"
"    s3 = abs(s3 / n - m3 * m3);\n"
"\n"
"    sigma2 = s3.r + s3.g + s3.b;\n"
"    if (sigma2 < min_sigma2) {\n"
"        min_sigma2 = sigma2;\n"
"        gl_FragColor = vec4(m3, 1.0);\n"
"    }\n"
"}"
;

#endif



GPUImageKuwaharaFilter::GPUImageKuwaharaFilter()
    : GPUImageFilter(_kuwahara_fragment_shader)
{
    m_uRadius = 3;

    m_iRadiusUniformLocation = -1;
}

GPUImageKuwaharaFilter::~GPUImageKuwaharaFilter()
{

}

void GPUImageKuwaharaFilter::setRadius(uint32_t radius)
{
    m_uRadius = radius;
}

bool GPUImageKuwaharaFilter::createProgramExtra()
{
    m_iRadiusUniformLocation = glGetUniformLocation(m_uProgram, "radius");
    return true;
}

bool GPUImageKuwaharaFilter::beforeDrawExtra()
{
    glUniform1i(m_iRadiusUniformLocation, m_uRadius);
    return true;
}


