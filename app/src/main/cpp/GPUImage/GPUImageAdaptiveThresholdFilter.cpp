/**
 * Created by lvHiei on 17-5-8.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageAdaptiveThresholdFilter.h"

#include "../util/TextureRotateUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _adaptiveThreshold_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
        highp float blurredInput = texture2D(inputImageTexture, textureCoordinate).r;
        highp float localLuminance = texture2D(inputImageTexture2, textureCoordinate2).r;
        highp float thresholdResult = step(blurredInput - 0.05, localLuminance);

        gl_FragColor = vec4(vec3(thresholdResult), 1.0);
    }
);

#else

// 片元着色器
extern const char _adaptiveThreshold_fragment_shader[]=SHADER_STR(
    varying vec2 textureCoordinate;
    varying vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    void main()
    {
        float blurredInput = texture2D(inputImageTexture, textureCoordinate).r;
        float localLuminance = texture2D(inputImageTexture2, textureCoordinate2).r;
        float thresholdResult = step(blurredInput - 0.05, localLuminance);

        gl_FragColor = vec4(vec3(thresholdResult), 1.0);
    }
);

#endif



GPUImageAdaptiveThresholdFilter::GPUImageAdaptiveThresholdFilter()
    : GPUImageFilterGroup(),
      m_pGreyScaleFilter(NULL),
      m_pBoxBlurFilter(NULL),
      m_pAdaptiveThresholdFilter(NULL)
{
    m_pGreyScaleFilter = new GPUImageGreyscaleFilter();

    m_pBoxBlurFilter = new GPUImageBoxBlurFilter();

    m_pAdaptiveThresholdFilter = new GPUImageTwoInputFilter(_adaptiveThreshold_fragment_shader);

    addFilter(m_pGreyScaleFilter);
    addFilter(m_pBoxBlurFilter);
    addFilter(m_pAdaptiveThresholdFilter);
}

GPUImageAdaptiveThresholdFilter::~GPUImageAdaptiveThresholdFilter()
{
    this->release();
}


bool GPUImageAdaptiveThresholdFilter::createProgram()
{
    bool ret =  GPUImageFilterGroup::createProgram();

    if(NULL != m_pAdaptiveThresholdFilter){
        m_pAdaptiveThresholdFilter->setTexture2Id(m_pFrameBufferTextures[0]);
        m_pAdaptiveThresholdFilter->setTexture2Rotation(m_eRotation);
        if(m_uFilterCnt % 2 != 0){
            m_pAdaptiveThresholdFilter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(m_eRotation, false, true));
        }else{
            m_pAdaptiveThresholdFilter->setTexture2Coordinate(m_pTextureCoordinate);
        }
    }

    return ret;
}


bool GPUImageAdaptiveThresholdFilter::release()
{
    if(m_pGreyScaleFilter){
        delete m_pGreyScaleFilter;
        m_pGreyScaleFilter = NULL;
    }

    if(m_pBoxBlurFilter){
        delete m_pBoxBlurFilter;
        m_pBoxBlurFilter = NULL;
    }

    if(m_pAdaptiveThresholdFilter){
        delete m_pAdaptiveThresholdFilter;
        m_pAdaptiveThresholdFilter = NULL;
    }

    return true;
}


void GPUImageAdaptiveThresholdFilter::setBlurRadiusInPixels(float blurRadiusInPixels)
{
    if(m_pBoxBlurFilter){
        m_pBoxBlurFilter->setBlurRadiusInPixels(blurRadiusInPixels);
    }
}

