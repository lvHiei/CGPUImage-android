/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHardLightBlendFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
extern const char _hardLight_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 base = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    float ra;\n"
"    if (2.0 * overlay.r < overlay.a) {\n"
"        ra = 2.0 * overlay.r * base.r + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);\n"
"    } else {\n"
"        ra = overlay.a * base.a - 2.0 * (base.a - base.r) * (overlay.a - overlay.r) + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);\n"
"    }\n"
"\n"
"    float ga;\n"
"    if (2.0 * overlay.g < overlay.a) {\n"
"        ga = 2.0 * overlay.g * base.g + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);\n"
"    } else {\n"
"        ga = overlay.a * base.a - 2.0 * (base.a - base.g) * (overlay.a - overlay.g) + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);\n"
"    }\n"
"\n"
"    float ba;\n"
"    if (2.0 * overlay.b < overlay.a) {\n"
"        ba = 2.0 * overlay.b * base.b + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);\n"
"    } else {\n"
"        ba = overlay.a * base.a - 2.0 * (base.a - base.b) * (overlay.a - overlay.b) + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);\n"
"    }\n"
"\n"
"    gl_FragColor = vec4(ra, ga, ba, 1.0);\n"
"}"
;

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

