/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorBlendFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _colorBlend_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"highp float lum(lowp vec3 c) {\n"
"    return dot(c, vec3(0.3, 0.59, 0.11));\n"
"}\n"
"\n"
"lowp vec3 clipcolor(lowp vec3 c) {\n"
"highp float l = lum(c);\n"
"lowp float n = min(min(c.r, c.g), c.b);\n"
"lowp float x = max(max(c.r, c.g), c.b);\n"
"\n"
"if (n < 0.0) {\n"
"c.r = l + ((c.r - l) * l) / (l - n);\n"
"c.g = l + ((c.g - l) * l) / (l - n);\n"
"c.b = l + ((c.b - l) * l) / (l - n);\n"
"}\n"
"if (x > 1.0) {\n"
"c.r = l + ((c.r - l) * (1.0 - l)) / (x - l);\n"
"c.g = l + ((c.g - l) * (1.0 - l)) / (x - l);\n"
"c.b = l + ((c.b - l) * (1.0 - l)) / (x - l);\n"
"}\n"
"\n"
"return c;\n"
"}\n"
"\n"
"lowp vec3 setlum(lowp vec3 c, highp float l) {\n"
"highp float d = l - lum(c);\n"
"c = c + vec3(d);\n"
"return clipcolor(c);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    highp vec4 baseColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    highp vec4 overlayColor = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    gl_FragColor = vec4(baseColor.rgb * (1.0 - overlayColor.a) + setlum(overlayColor.rgb, lum(baseColor.rgb)) * overlayColor.a, baseColor.a);\n"
"}"
;

#else


// 片元着色器
extern const char _colorBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"float lum(vec3 c) {\n"
"    return dot(c, vec3(0.3, 0.59, 0.11));\n"
"}\n"
"\n"
"vec3 clipcolor(vec3 c) {\n"
"    float l = lum(c);\n"
"    float n = min(min(c.r, c.g), c.b);\n"
"    float x = max(max(c.r, c.g), c.b);\n"
"\n"
"    if (n < 0.0) {\n"
"        c.r = l + ((c.r - l) * l) / (l - n);\n"
"        c.g = l + ((c.g - l) * l) / (l - n);\n"
"        c.b = l + ((c.b - l) * l) / (l - n);\n"
"    }\n"
"    if (x > 1.0) {\n"
"        c.r = l + ((c.r - l) * (1.0 - l)) / (x - l);\n"
"        c.g = l + ((c.g - l) * (1.0 - l)) / (x - l);\n"
"        c.b = l + ((c.b - l) * (1.0 - l)) / (x - l);\n"
"    }\n"
"\n"
"    return c;\n"
"}\n"
"\n"
"vec3 setlum(vec3 c, float l) {\n"
"    float d = l - lum(c);\n"
"    c = c + vec3(d);\n"
"    return clipcolor(c);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    vec4 baseColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 overlayColor = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    gl_FragColor = vec4(baseColor.rgb * (1.0 - overlayColor.a) + setlum(overlayColor.rgb, lum(baseColor.rgb)) * overlayColor.a, baseColor.a);\n"
"}"
;

#endif




GPUImageColorBlendFilter::GPUImageColorBlendFilter()
    : GPUImageImageFilter(_colorBlend_fragment_shader)
{

}

GPUImageColorBlendFilter::~GPUImageColorBlendFilter()
{

}

bool GPUImageColorBlendFilter::loadImage()
{
    // this is decode the image of blend.png.
    // in the example we just use the rgba data stored in
    // the file blend.rgba.

    const char* filename = "blend.rgba";

    m_uPicWidth = 720;
    m_uPicHeight = 1280;
    uint32_t fileLen = FileUtil::getFileSize(filename);
    if(fileLen > 0){
        m_pPicDataRGBA = (uint8_t *) malloc(fileLen * sizeof(uint8_t));
        if(!m_pPicDataRGBA){
            return false;
        }

        FileUtil::loadFile(filename, m_pPicDataRGBA, fileLen);
    }
    return true;
}