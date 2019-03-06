/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHardLightBlendFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _hardLight_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        mediump vec4 base = texture2D(inputImageTexture, textureCoordinate);
        mediump vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

        highp float ra;
        if (2.0 * overlay.r < overlay.a) {
            ra = 2.0 * overlay.r * base.r + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
        } else {
            ra = overlay.a * base.a - 2.0 * (base.a - base.r) * (overlay.a - overlay.r) + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
        }

        highp float ga;
        if (2.0 * overlay.g < overlay.a) {
            ga = 2.0 * overlay.g * base.g + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
        } else {
            ga = overlay.a * base.a - 2.0 * (base.a - base.g) * (overlay.a - overlay.g) + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
        }

        highp float ba;
        if (2.0 * overlay.b < overlay.a) {
            ba = 2.0 * overlay.b * base.b + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
        } else {
            ba = overlay.a * base.a - 2.0 * (base.a - base.b) * (overlay.a - overlay.b) + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
        }

        gl_FragColor = vec4(ra, ga, ba, 1.0);
    }
);


#else

// 片元着色器
extern const char _hardLight_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 const vec3 W = vec3(0.2125, 0.7154, 0.0721);

 void main()
 {
     vec4 base = texture2D(inputImageTexture, textureCoordinate);
     vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

     float ra;
     if (2.0 * overlay.r < overlay.a) {
         ra = 2.0 * overlay.r * base.r + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
     } else {
         ra = overlay.a * base.a - 2.0 * (base.a - base.r) * (overlay.a - overlay.r) + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);
     }

     float ga;
     if (2.0 * overlay.g < overlay.a) {
         ga = 2.0 * overlay.g * base.g + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
     } else {
         ga = overlay.a * base.a - 2.0 * (base.a - base.g) * (overlay.a - overlay.g) + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);
     }

     float ba;
     if (2.0 * overlay.b < overlay.a) {
         ba = 2.0 * overlay.b * base.b + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
     } else {
         ba = overlay.a * base.a - 2.0 * (base.a - base.b) * (overlay.a - overlay.b) + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);
     }

     gl_FragColor = vec4(ra, ga, ba, 1.0);
 }
);


#endif


GPUImageHardLightBlendFilter::GPUImageHardLightBlendFilter()
    : GPUImageImageFilter(_hardLight_fragment_shader)
{

}

GPUImageHardLightBlendFilter::~GPUImageHardLightBlendFilter()
{

}

bool GPUImageHardLightBlendFilter::loadImage()
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

