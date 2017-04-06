/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageAddBlendFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
const char _addBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 base = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    float r;\n"
"    if (overlay.r * base.a + base.r * overlay.a >= overlay.a * base.a) {\n"
"        r = overlay.a * base.a + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);\n"
"    } else {\n"
"        r = overlay.r + base.r;\n"
"    }\n"
"\n"
"    float g;\n"
"    if (overlay.g * base.a + base.g * overlay.a >= overlay.a * base.a) {\n"
"        g = overlay.a * base.a + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);\n"
"    } else {\n"
"        g = overlay.g + base.g;\n"
"    }\n"
"\n"
"    float b;\n"
"    if (overlay.b * base.a + base.b * overlay.a >= overlay.a * base.a) {\n"
"        b = overlay.a * base.a + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);\n"
"    } else {\n"
"        b = overlay.b + base.b;\n"
"    }\n"
"\n"
"    float a = overlay.a + base.a - overlay.a * base.a;\n"
"\n"
"    gl_FragColor = vec4(r, g, b, a);\n"
"}"
;


GPUImageAddBlendFilter::GPUImageAddBlendFilter()
    : GPUImageTwoInputFilter(_addBlend_fragment_shader)
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