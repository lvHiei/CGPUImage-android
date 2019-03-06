/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMaskFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _mask_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);

        //Averages mask's the RGB values, and scales that value by the mask's alpha
        //
        //The dot product should take fewer cycles than doing an average normally
        //
        //Typical/ideal case, R,G, and B will be the same, and Alpha will be 1.0
        lowp float newAlpha = dot(textureColor2.rgb, vec3(.33333334, .33333334, .33333334)) * textureColor2.a;

        gl_FragColor = vec4(textureColor.xyz, newAlpha);
        //\t gl_FragColor = vec4(textureColor2);
    }
);

#else

// 片元着色器
extern const char _mask_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
     vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);

     //Averages mask's the RGB values, and scales that value by the mask's alpha
     //
     //The dot product should take fewer cycles than doing an average normally
     //
     //Typical/ideal case, R,G, and B will be the same, and Alpha will be 1.0
     float newAlpha = dot(textureColor2.rgb, vec3(.33333334, .33333334, .33333334)) * textureColor2.a;

     gl_FragColor = vec4(textureColor.xyz, newAlpha);
     //\t gl_FragColor = vec4(textureColor2);
 }
);

#endif




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

