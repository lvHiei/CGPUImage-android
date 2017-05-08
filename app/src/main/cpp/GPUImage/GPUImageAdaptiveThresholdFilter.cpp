/**
 * Created by mj on 17-5-8.
 */

#include "GPUImageAdaptiveThresholdFilter.h"
#include "GPUImageGreyscaleFilter.h"
#include "GPUImageBoxBlurFilter.h"
#include "GPUImageTwoInputFilter.h"
#include "../util/TextureRotateUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _adaptiveThreshold_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    highp float blurredInput = texture2D(inputImageTexture, textureCoordinate).r;\n"
"    highp float localLuminance = texture2D(inputImageTexture2, textureCoordinate2).r;\n"
"    highp float thresholdResult = step(blurredInput - 0.05, localLuminance);\n"
"\n"
"    gl_FragColor = vec4(vec3(thresholdResult), 1.0);\n"
"}"
;

#else

// 片元着色器
extern const char _adaptiveThreshold_fragment_shader[]=
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    float blurredInput = texture2D(inputImageTexture, textureCoordinate).r;\n"
"    float localLuminance = texture2D(inputImageTexture2, textureCoordinate2).r;\n"
"    float thresholdResult = step(blurredInput - 0.05, localLuminance);\n"
"\n"
"    gl_FragColor = vec4(vec3(thresholdResult), 1.0);\n"
"}"
;

#endif



GPUImageAdaptiveThresholdFilter::GPUImageAdaptiveThresholdFilter()
    : GPUImageFilterGroup()
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

    GPUImageTwoInputFilter* filter = dynamic_cast<GPUImageTwoInputFilter*>(m_pAdaptiveThresholdFilter);
    if(NULL != filter){
        filter->setTexture2Id(m_pFrameBufferTextures[0]);
        filter->setTexture2Rotation(m_eRotation);
        if(m_uFilterCnt % 2 != 0){
            filter->setTexture2Coordinate(TextureRotateUtil::getTextureCoordinate(m_eRotation, false, true));
        }else{
            filter->setTexture2Coordinate(m_pTextureCoordinate);
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
}

