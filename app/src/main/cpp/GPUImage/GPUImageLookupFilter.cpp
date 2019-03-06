/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLookupFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _lookUp_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2; // TODO: This is not used

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2; // lookup texture

    uniform lowp float intensity;

    void main()
    {
        highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        // this is redundancy, use it because some device will has gl error if the textureCoordinate2 is not used
        highp vec4 textureColor2 = texture2D(inputImageTexture, textureCoordinate2);

        highp float blueColor = textureColor.b * 63.0;

        highp vec2 quad1;
        quad1.y = floor(floor(blueColor) / 8.0);
        quad1.x = floor(blueColor) - (quad1.y * 8.0);

        highp vec2 quad2;
        quad2.y = floor(ceil(blueColor) / 8.0);
        quad2.x = ceil(blueColor) - (quad2.y * 8.0);

        highp vec2 texPos1;
        texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
        texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

        highp vec2 texPos2;
        texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
        texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

        lowp vec4 newColor1 = texture2D(inputImageTexture2, texPos1);
        lowp vec4 newColor2 = texture2D(inputImageTexture2, texPos2);

        lowp vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
        gl_FragColor = mix(textureColor, vec4(newColor.rgb, textureColor.w), intensity);
    }
);

#else

// 片元着色器
extern const char _lookUp_fragment_shader[]=SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture2;
 varying vec2 textureCoordinate2;

 uniform float intensity;

 void main()
 {
 	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
 	// this is redundancy, use it because some device will has gl error if the textureCoordinate2 is not used
 	vec4 textureColor2 = texture2D(inputImageTexture, textureCoordinate2);
    // lookupfilter
    float blueColor = textureColor.b * 63.0;

    vec2 quad1;
    quad1.y = floor(floor(blueColor) / 8.0);
    quad1.x = floor(blueColor) - (quad1.y * 8.0);

    vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);

    vec2 texPos1;
    texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

    vec2 texPos2;
    texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

    lowp vec4 newColor1 = texture2D(inputImageTexture2, texPos1);
    lowp vec4 newColor2 = texture2D(inputImageTexture2, texPos2);

    lowp vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    vec4 lookUpColor = mix(textureColor, vec4(newColor.rgb, textureColor.w), lookupIntensity);
    gl_FragColor = lookUpColor;
//    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
 }
);

#endif



GPUImageLookupFilter::GPUImageLookupFilter() :
    GPUImageImageFilter(_lookUp_fragment_shader)
{
    m_fIntensity = 1.0f;

    m_pFilename = NULL;
}


GPUImageLookupFilter::GPUImageLookupFilter(const char *filename)
    : GPUImageImageFilter(_lookUp_fragment_shader)
{
    m_fIntensity = 1.0f;

    m_pFilename = (char *) malloc(strlen(filename) + 1);
    strcpy(m_pFilename, filename);
}


GPUImageLookupFilter::~GPUImageLookupFilter()
{
    this->release();
}

bool GPUImageLookupFilter::createProgramExtra()
{
    GPUImageImageFilter::createProgramExtra();

    m_iIntensityLocation = glGetUniformLocation(m_uProgram, "intensity");

    return true;
}

bool GPUImageLookupFilter::beforeDrawExtra()
{
    glUniform1f(m_iIntensityLocation, m_fIntensity);
    GPUImageImageFilter::beforeDrawExtra();
    return true;
}

void GPUImageLookupFilter::setIntensity(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fIntensity = 0.0f + incremental * percent;
}


void GPUImageLookupFilter::setIntensity(float intensity)
{
    m_fIntensity = intensity;
}


bool GPUImageLookupFilter::loadImage()
{
    if(!m_pFilename){
        return GPUImageImageFilter::loadImage();
    }

    const char* filename = m_pFilename;

    m_uPicWidth = 512;
    m_uPicHeight = 512;
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


bool GPUImageLookupFilter::release()
{
    if(m_pFilename){
        free(m_pFilename);
        m_pFilename = NULL;
    }

    return GPUImageImageFilter::release();
}

