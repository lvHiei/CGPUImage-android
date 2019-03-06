/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageAddBlendFilter.h"
#include "../util/FileUtil.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _addBlend_fragment_shader[]= SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
        lowp vec4 base = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

        mediump float r;
        if (overlay.r * base.a + base.r * overlay.a >= overlay.a * base.a) {
            r = overlay.a * base.a + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
        } else {
            r = overlay.r + base.r;
        }

        mediump float g;
        if (overlay.g * base.a + base.g * overlay.a >= overlay.a * base.a) {
            g = overlay.a * base.a + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
        } else {
            g = overlay.g + base.g;
        }

        mediump float b;
        if (overlay.b * base.a + base.b * overlay.a >= overlay.a * base.a) {
            b = overlay.a * base.a + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
        } else {
            b = overlay.b + base.b;
        }

        mediump float a = overlay.a + base.a - overlay.a * base.a;

        gl_FragColor = vec4(r, g, b, a);
    }
);

#else
// 片元着色器
extern const char _addBlend_fragment_shader[]= SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 void main()
 {
     vec4 base = texture2D(inputImageTexture, textureCoordinate);
     vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

     float r;
     if (overlay.r * base.a + base.r * overlay.a >= overlay.a * base.a) {
         r = overlay.a * base.a + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
     } else {
         r = overlay.r + base.r;
     }

     float g;
     if (overlay.g * base.a + base.g * overlay.a >= overlay.a * base.a) {
         g = overlay.a * base.a + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
     } else {
         g = overlay.g + base.g;
     }

     float b;
     if (overlay.b * base.a + base.b * overlay.a >= overlay.a * base.a) {
         b = overlay.a * base.a + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
     } else {
         b = overlay.b + base.b;
     }

     float a = overlay.a + base.a - overlay.a * base.a;

     gl_FragColor = vec4(r, g, b, a);
 }
);

#endif




GPUImageAddBlendFilter::GPUImageAddBlendFilter()
    : GPUImageImageFilter(_addBlend_fragment_shader)
{

}

GPUImageAddBlendFilter::~GPUImageAddBlendFilter()
{
    this->release();
}

bool GPUImageAddBlendFilter::loadImage()
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