/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageDissolveBlendFilter.h"
#include "../util/FileUtil.h"

// 片元着色器
extern const char _dissolveBlend_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"uniform float mixturePercent;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    gl_FragColor = mix(textureColor, textureColor2, mixturePercent);\n"
"}"
;

GPUImageDissolveBlendFilter::GPUImageDissolveBlendFilter()
    : GPUImageImageFilter(_dissolveBlend_fragment_shader)
{
    m_fMix = 0.5f;
    m_iMixUniformLocation = -1;
}

GPUImageDissolveBlendFilter::~GPUImageDissolveBlendFilter()
{

}

bool GPUImageDissolveBlendFilter::createProgramExtra()
{
    GPUImageImageFilter::createProgramExtra();
    m_iMixUniformLocation = glGetUniformLocation(m_uProgram, "mixturePercent");
    return true;
}

bool GPUImageDissolveBlendFilter::beforeDrawExtra()
{
    GPUImageImageFilter::beforeDrawExtra();
    glUniform1f(m_iMixUniformLocation, m_fMix);
    return true;
}

bool GPUImageDissolveBlendFilter::loadImage()
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

void GPUImageDissolveBlendFilter::setMix(int percent)
{
    float max = 1.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setMix(value);
}

void GPUImageDissolveBlendFilter::setMix(float mix)
{
    m_fMix = mix;
}