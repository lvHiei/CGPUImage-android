/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageDivideBlendFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
extern const char _divideBlend_fragment_shader[]=
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
"    float ra;\n"
"    if (overlay.a == 0.0 || ((base.r / overlay.r) > (base.a / overlay.a)))\n"
"        ra = overlay.a * base.a + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);\n"
"    else\n"
"        ra = (base.r * overlay.a * overlay.a) / overlay.r + overlay.r * (1.0 - base.a) + base.r * (1.0 - overlay.a);\n"
"\n"
"\n"
"    float ga;\n"
"    if (overlay.a == 0.0 || ((base.g / overlay.g) > (base.a / overlay.a)))\n"
"        ga = overlay.a * base.a + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);\n"
"    else\n"
"        ga = (base.g * overlay.a * overlay.a) / overlay.g + overlay.g * (1.0 - base.a) + base.g * (1.0 - overlay.a);\n"
"\n"
"\n"
"    float ba;\n"
"    if (overlay.a == 0.0 || ((base.b / overlay.b) > (base.a / overlay.a)))\n"
"        ba = overlay.a * base.a + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);\n"
"    else\n"
"        ba = (base.b * overlay.a * overlay.a) / overlay.b + overlay.b * (1.0 - base.a) + base.b * (1.0 - overlay.a);\n"
"\n"
"    float a = overlay.a + base.a - overlay.a * base.a;\n"
"\n"
"    gl_FragColor = vec4(ra, ga, ba, a);\n"
"}"
;



GPUImageDivideBlendFilter::GPUImageDivideBlendFilter()
    : GPUImageImageFilter(_divideBlend_fragment_shader)
{

}

GPUImageDivideBlendFilter::~GPUImageDivideBlendFilter()
{

}

bool GPUImageDivideBlendFilter::loadImage()
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