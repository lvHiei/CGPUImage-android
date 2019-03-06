/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageDarkenBlendFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _darkenBlend_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
        lowp vec4 base = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 overlayer = texture2D(inputImageTexture2, textureCoordinate2);

        gl_FragColor = vec4(min(overlayer.rgb * base.a, base.rgb * overlayer.a) + overlayer.rgb * (1.0 - base.a) + base.rgb * (1.0 - overlayer.a), 1.0);
    }
);

#else

// 片元着色器
extern const char _darkenBlend_fragment_shader[] = SHADER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;
    varying vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
     vec4 base = texture2D(inputImageTexture, textureCoordinate);
     vec4 overlayer = texture2D(inputImageTexture2, textureCoordinate2);

     gl_FragColor = vec4(min(overlayer.rgb * base.a, base.rgb * overlayer.a) + overlayer.rgb * (1.0 - base.a) + base.rgb * (1.0 - overlayer.a), 1.0);
    }
);

#endif



GPUImageDarkenBlendFilter::GPUImageDarkenBlendFilter()
    : GPUImageImageFilter(_darkenBlend_fragment_shader)
{

}

GPUImageDarkenBlendFilter::~GPUImageDarkenBlendFilter()
{

}

bool GPUImageDarkenBlendFilter::loadImage()
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