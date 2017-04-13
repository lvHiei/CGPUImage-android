/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSoftLightBlendFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
const char _softLightBlend_fragment_shader[]=
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
"    float alphaDivisor = base.a + step(base.a, 0.0); // Protect against a divide-by-zero blacking out things in the output\n"
"    gl_FragColor = base * (overlay.a * (base / alphaDivisor) + (2.0 * overlay * (1.0 - (base / alphaDivisor)))) + overlay * (1.0 - base.a) + base * (1.0 - overlay.a);\n"
"    gl_FragColor = overlay;\n"
"}"
;


GPUImageSoftLightBlendFilter::GPUImageSoftLightBlendFilter()
    : GPUImageImageFilter(_softLightBlend_fragment_shader)
{

}

GPUImageSoftLightBlendFilter::~GPUImageSoftLightBlendFilter() {

}

bool GPUImageSoftLightBlendFilter::loadImage()
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

