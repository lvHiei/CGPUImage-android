/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMaskFilter.h"
#include "../util/FileUtil.h"


// 片元着色器
extern const char _mask_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    //Averages mask's the RGB values, and scales that value by the mask's alpha\n"
"    //\n"
"    //The dot product should take fewer cycles than doing an average normally\n"
"    //\n"
"    //Typical/ideal case, R,G, and B will be the same, and Alpha will be 1.0\n"
"    float newAlpha = dot(textureColor2.rgb, vec3(.33333334, .33333334, .33333334)) * textureColor2.a;\n"
"\n"
"    gl_FragColor = vec4(textureColor.xyz, newAlpha);\n"
"    //\t gl_FragColor = vec4(textureColor2);\n"
"}"
;


GPUImageMaskFilter::GPUImageMaskFilter()
    : GPUImageImageFilter(_mask_fragment_shader)
{

}

GPUImageMaskFilter::~GPUImageMaskFilter() {

}

bool GPUImageMaskFilter::loadImage()
{
    // this is decode the image of mask.jpg.
    // in the example we just use the rgba data stored in
    // the file mask.rgba.

    const char* filename = "mask.rgba";

    m_uPicWidth = 1494;
    m_uPicHeight = 2000;
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

