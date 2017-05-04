/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageNormalBlendFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _normalBlend_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 c2 = texture2D(inputImageTexture, textureCoordinate);\n"
"    lowp vec4 c1 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    lowp vec4 outputColor;\n"
"\n"
"//     outputColor.r = c1.r + c2.r * c2.a * (1.0 - c1.a);\n"
"//     outputColor.g = c1.g + c2.g * c2.a * (1.0 - c1.a);\n"
"//     outputColor.b = c1.b + c2.b * c2.a * (1.0 - c1.a);\n"
"//     outputColor.a = c1.a + c2.a * (1.0 - c1.a);\n"
"\n"
"    lowp float a = c1.a + c2.a * (1.0 - c1.a);\n"
"    lowp float alphaDivisor = a + step(a, 0.0); // Protect against a divide-by-zero blacking out things in the output\n"
"\n"
"    outputColor.r = (c1.r * c1.a + c2.r * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.g = (c1.g * c1.a + c2.g * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.b = (c1.b * c1.a + c2.b * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.a = a;\n"
"\n"
"    gl_FragColor = outputColor;\n"
"}"
;

#else

// 片元着色器
extern const char _normalBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 c2 = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 c1 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    vec4 outputColor;\n"
"\n"
"    //     outputColor.r = c1.r + c2.r * c2.a * (1.0 - c1.a);\n"
"    //     outputColor.g = c1.g + c2.g * c2.a * (1.0 - c1.a);\n"
"    //     outputColor.b = c1.b + c2.b * c2.a * (1.0 - c1.a);\n"
"    //     outputColor.a = c1.a + c2.a * (1.0 - c1.a);\n"
"\n"
"    float a = c1.a + c2.a * (1.0 - c1.a);\n"
"    float alphaDivisor = a + step(a, 0.0); // Protect against a divide-by-zero blacking out things in the output\n"
"\n"
"    outputColor.r = (c1.r * c1.a + c2.r * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.g = (c1.g * c1.a + c2.g * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.b = (c1.b * c1.a + c2.b * c2.a * (1.0 - c1.a))/alphaDivisor;\n"
"    outputColor.a = a;\n"
"\n"
"    gl_FragColor = outputColor;\n"
"}"
;

#endif




GPUImageNormalBlendFilter::GPUImageNormalBlendFilter()
    : GPUImageImageFilter(_normalBlend_fragment_shader)
{

}

GPUImageNormalBlendFilter::~GPUImageNormalBlendFilter()
{

}

bool GPUImageNormalBlendFilter::loadImage()
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

