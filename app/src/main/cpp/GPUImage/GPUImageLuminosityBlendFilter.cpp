/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLuminosityBlendFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _luminosityBlend_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    highp float lum(lowp vec3 c) {
        return dot(c, vec3(0.3, 0.59, 0.11));
    }

    lowp vec3 clipcolor(lowp vec3 c) {
        highp float l = lum(c);
        lowp float n = min(min(c.r, c.g), c.b);
        lowp float x = max(max(c.r, c.g), c.b);

        if (n < 0.0) {
            c.r = l + ((c.r - l) * l) / (l - n);
            c.g = l + ((c.g - l) * l) / (l - n);
            c.b = l + ((c.b - l) * l) / (l - n);
        }
        if (x > 1.0) {
            c.r = l + ((c.r - l) * (1.0 - l)) / (x - l);
            c.g = l + ((c.g - l) * (1.0 - l)) / (x - l);
            c.b = l + ((c.b - l) * (1.0 - l)) / (x - l);
        }

        return c;
    }

    lowp vec3 setlum(lowp vec3 c, highp float l) {
        highp float d = l - lum(c);
        c = c + vec3(d);
        return clipcolor(c);
    }

    void main()
    {
        highp vec4 baseColor = texture2D(inputImageTexture, textureCoordinate);
        highp vec4 overlayColor = texture2D(inputImageTexture2, textureCoordinate2);

        gl_FragColor = vec4(baseColor.rgb * (1.0 - overlayColor.a) + setlum(baseColor.rgb, lum(overlayColor.rgb)) * overlayColor.a, baseColor.a);
    }
);

#else


// 片元着色器
extern const char _luminosityBlend_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 float lum(vec3 c) {
     return dot(c, vec3(0.3, 0.59, 0.11));
 }

 vec3 clipcolor(vec3 c) {
     float l = lum(c);
     float n = min(min(c.r, c.g), c.b);
     float x = max(max(c.r, c.g), c.b);

     if (n < 0.0) {
         c.r = l + ((c.r - l) * l) / (l - n);
         c.g = l + ((c.g - l) * l) / (l - n);
         c.b = l + ((c.b - l) * l) / (l - n);
     }
     if (x > 1.0) {
         c.r = l + ((c.r - l) * (1.0 - l)) / (x - l);
         c.g = l + ((c.g - l) * (1.0 - l)) / (x - l);
         c.b = l + ((c.b - l) * (1.0 - l)) / (x - l);
     }

     return c;
 }

 vec3 setlum(vec3 c, float l) {
     float d = l - lum(c);
     c = c + vec3(d);
     return clipcolor(c);
 }

 void main()
 {
     vec4 baseColor = texture2D(inputImageTexture, textureCoordinate);
     vec4 overlayColor = texture2D(inputImageTexture2, textureCoordinate2);

     gl_FragColor = vec4(baseColor.rgb * (1.0 - overlayColor.a) + setlum(baseColor.rgb, lum(overlayColor.rgb)) * overlayColor.a, baseColor.a);
 }
);

#endif



GPUImageLuminosityBlendFilter::GPUImageLuminosityBlendFilter()
    : GPUImageImageFilter(_luminosityBlend_fragment_shader)
{

}

GPUImageLuminosityBlendFilter::~GPUImageLuminosityBlendFilter()
{

}

bool GPUImageLuminosityBlendFilter::loadImage()
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

