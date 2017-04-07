/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorDodgeBlendFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
const char _colorDodgeBlend_fragment_shader[]=
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
"    vec3 baseOverlayAlphaProduct = vec3(overlay.a * base.a);\n"
"    vec3 rightHandProduct = overlay.rgb * (1.0 - base.a) + base.rgb * (1.0 - overlay.a);\n"
"\n"
"    vec3 firstBlendColor = baseOverlayAlphaProduct + rightHandProduct;\n"
"    vec3 overlayRGB = clamp((overlay.rgb / clamp(overlay.a, 0.01, 1.0)) * step(0.0, overlay.a), 0.0, 0.99);\n"
"\n"
"    vec3 secondBlendColor = (base.rgb * overlay.a) / (1.0 - overlayRGB) + rightHandProduct;\n"
"\n"
"    vec3 colorChoice = step((overlay.rgb * base.a + base.rgb * overlay.a), baseOverlayAlphaProduct);\n"
"\n"
"    gl_FragColor = vec4(mix(firstBlendColor, secondBlendColor, colorChoice), 1.0);\n"
"}"
;

GPUImageColorDodgeBlendFilter::GPUImageColorDodgeBlendFilter()
    : GPUImageImageFilter(_colorDodgeBlend_fragment_shader)
{

}

GPUImageColorDodgeBlendFilter::~GPUImageColorDodgeBlendFilter()
{

}

bool GPUImageColorDodgeBlendFilter::loadImage()
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