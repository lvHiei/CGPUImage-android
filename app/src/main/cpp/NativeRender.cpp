/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "NativeRender.h"
#include "GPUImage/GPUImageGreyscaleFilter.h"
#include "GPUImage/GPUImageContrastFilter.h"
#include "GPUImage/GPUImageSepiaFilter.h"
#include "GPUImage/GPUImageSaturationFilter.h"
#include "GPUImage/GPUImageAmatorkaFilter.h"
#include "GPUImage/GPUImageMissEtikateFilter.h"
#include "GPUImage/GPUImageGammaFilter.h"
#include "GPUImage/GPUImage3x3ConvolutionFilter.h"
#include "GPUImage/GPUImageColorLocalBinaryPatternFilter.h"
#include "GPUImage/GPUImageDirectionalSobelEdgeDetectionFilter.h"
#include "GPUImage/GPUImageLocalBinaryPatternFilter.h"
#include "GPUImage/GPUImageMedianFilter.h"
#include "GPUImage/GPUImageNonMaximumSuppressionFilter.h"
#include "GPUImage/GPUImageWeakPixelInclusionFilter.h"
#include "GPUImage/GPUImageThresholdedNonMaximumSuppressionFilter.h"
#include "GPUImage/GPUImageToonFilter.h"
#include "GPUImage/GPUImageAddBlendFilter.h"
#include "GPUImage/GPUImageBrightnessFilter.h"
#include "GPUImage/GPUImageBulgeDistortionFilter.h"
#include "GPUImage/GPUImageCGAColorspaceFilter.h"
#include "GPUImage/GPUImageChromaKeyBlendFilter.h"
#include "GPUImage/GPUImageChromaKeyFilter.h"
#include "GPUImage/GPUImageColorBlendFilter.h"
#include "GPUImage/GPUImageColorBurnBlendFilter.h"
#include "GPUImage/GPUImageColorDodgeBlendFilter.h"
#include "GPUImage/GPUImageColorInvertFilter.h"
#include "GPUImage/GPUImageColorPackingFilter.h"
#include "GPUImage/GPUImageColourFASTSamplingOperation.h"
#include "GPUImage/GPUImageCrosshatchFilter.h"
#include "GPUImage/GPUImageDarkenBlendFilter.h"
#include "GPUImage/GPUImageDifferenceBlendFilter.h"
#include "GPUImage/GPUImageDirectionalNonMaximumSuppressionFilter.h"
#include "GPUImage/GPUImageDissolveBlendFilter.h"
#include "GPUImage/GPUImageDivideBlendFilter.h"
#include "GPUImage/GPUImageEmbossFilter.h"
#include "GPUImage/GPUImageExclusionBlendFilter.h"
#include "GPUImage/GPUImageExposureFilter.h"
#include "GPUImage/GPUImageFalseColorFilter.h"
#include "GPUImage/GPUImageHardLightBlendFilter.h"
#include "GPUImage/GPUImageHazeFilter.h"
#include "GPUImage/GPUImageHighlightShadowFilter.h"
#include "GPUImage/GPUImageHighlightShadowTintFilter.h"
#include "GPUImage/GPUImageHSBFilter.h"
#include "GPUImage/GPUImageHueBlendFilter.h"
#include "GPUImage/GPUImageHueFilter.h"
#include "GPUImage/GPUImageKuwaharaFilter.h"
#include "GPUImage/GPUImageKuwaharaRadius3Filter.h"
#include "GPUImage/GPUImageLaplacianFilter.h"
#include "GPUImage/GPUImageLevelsFilter.h"
#include "GPUImage/GPUImageLightenBlendFilter.h"
#include "GPUImage/GPUImageLinearBurnBlendFilter.h"
#include "GPUImage/GPUImageLuminanceRangeFilter.h"
#include "GPUImage/GPUImageLuminanceThresholdFilter.h"
#include "GPUImage/GPUImageLuminosityBlendFilter.h"
#include "GPUImage/GPUImageMaskFilter.h"
#include "GPUImage/GPUImageMonochromeFilter.h"
#include "GPUImage/GPUImageMosaicFilter.h"
#include "GPUImage/GPUImageMotionBlurFilter.h"
#include "GPUImage/GPUImageMultiplyBlendFilter.h"
#include "GPUImage/GPUImageNormalBlendFilter.h"
#include "GPUImage/GPUImageOpacityFilter.h"
#include "GPUImage/GPUImageOverlayBlendFilter.h"
#include "GPUImage/GPUImagePerlinNoiseFilter.h"
#include "GPUImage/GPUImagePinchDistortionFilter.h"
#include "GPUImage/GPUImagePixellateFilter.h"


//顶点坐标（前四个点）与纹理坐标（后四个点）
float vertex_coordinate[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
};

float textureCoord_front[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

float textureCoord_back[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

};


NativeRender::NativeRender()
{
    m_pFilter = NULL;

    m_bFrontCamera = true;
}

NativeRender::~NativeRender()
{
    if(NULL != m_pFilter)
    {
       delete m_pFilter;
        m_pFilter = NULL;
    }

}

bool NativeRender::createFilter(int filterType)
{
    if(NULL != m_pFilter){
        delete m_pFilter;
    }

    intenalCreateFilter(filterType);

    m_pFilter->setVertexCoordinate(vertex_coordinate);
    if(m_bFrontCamera){
        m_pFilter->setTextureCoordinate(textureCoord_front);
    }else{
        m_pFilter->setTextureCoordinate(textureCoord_back);
    }

    return m_pFilter->createProgram();
}

void NativeRender::intenalCreateFilter(int filterType)
{
//    m_pFilter = new GPUImageFilter();
//    m_pFilter = new GPUImageGreyscaleFilter();
//    m_pFilter = new GPUImageContrastFilter();
//    m_pFilter = new GPUImageSaturationFilter();
//    m_pFilter = new GPUImageSepiaFilter();
//    m_pFilter = new GPUImageAmatorkaFilter();
//    m_pFilter = new GPUImageMissEtikateFilter();
//    m_pFilter = new GPUImageGammaFilter();
//    m_pFilter = new GPUImage3x3ConvolutionFilter();
//    m_pFilter = new GPUImageColorLocalBinaryPatternFilter();
//    m_pFilter = new GPUImageDirectionalSobelEdgeDetectionFilter();
//    m_pFilter = new GPUImageLocalBinaryPatternFilter();
//    m_pFilter = new GPUImageMedianFilter();
//    m_pFilter = new GPUImageNonMaximumSuppressionFilter();
//    m_pFilter = new GPUImageWeakPixelInclusionFilter();
//    m_pFilter = new GPUImageThresholdedNonMaximumSuppressionFilter();
//    m_pFilter = new GPUImageToonFilter();
//    m_pFilter = new GPUImageAddBlendFilter();
//    m_pFilter = new GPUImageBrightnessFilter();
//    m_pFilter = new GPUImageBulgeDistortionFilter();
//    m_pFilter = new GPUImageCGAColorspaceFilter();
//    m_pFilter = new GPUImageChromaKeyBlendFilter();
//    m_pFilter = new GPUImageChromaKeyFilter();
//    m_pFilter = new GPUImageColorBlendFilter();
//    m_pFilter = new GPUImageColorBurnBlendFilter();
//    m_pFilter = new GPUImageColorDodgeBlendFilter();
//    m_pFilter = new GPUImageColorInvertFilter();
//    m_pFilter = new GPUImageColorPackingFilter();
//    m_pFilter = new GPUImageColourFASTSamplingOperation();
//    m_pFilter = new GPUImageCrosshatchFilter();
//    m_pFilter = new GPUImageDarkenBlendFilter();
//    m_pFilter = new GPUImageDifferenceBlendFilter();
//    m_pFilter = new GPUImageDirectionalNonMaximumSuppressionFilter();
//    m_pFilter = new GPUImageDissolveBlendFilter();
//    m_pFilter = new GPUImageDivideBlendFilter();
//    m_pFilter = new GPUImageEmbossFilter();
//    m_pFilter = new GPUImageExclusionBlendFilter();
//    m_pFilter = new GPUImageExposureFilter();
//    m_pFilter = new GPUImageFalseColorFilter();
//    m_pFilter = new GPUImageHardLightBlendFilter();
//    m_pFilter = new GPUImageHazeFilter();
//    m_pFilter = new GPUImageHighlightShadowFilter();
//    m_pFilter = new GPUImageHighlightShadowTintFilter();
//    m_pFilter = new GPUImageHSBFilter();
//    m_pFilter = new GPUImageHueBlendFilter();
//    m_pFilter = new GPUImageHueFilter();
//    m_pFilter = new GPUImageKuwaharaFilter();
//    m_pFilter = new GPUImageKuwaharaRadius3Filter();
//    m_pFilter = new GPUImageLaplacianFilter();
//    m_pFilter = new GPUImageLevelsFilter();
//    m_pFilter = new GPUImageLightenBlendFilter();
//    m_pFilter = new GPUImageLinearBurnBlendFilter();
//    m_pFilter = new GPUImageLuminanceRangeFilter();
//    m_pFilter = new GPUImageLuminanceThresholdFilter();
//    m_pFilter = new GPUImageLuminosityBlendFilter();
//    m_pFilter = new GPUImageMaskFilter();
//    m_pFilter = new GPUImageMonochromeFilter();
//    m_pFilter = new GPUImageMosaicFilter();
//    m_pFilter = new GPUImageMotionBlurFilter();
//    m_pFilter = new GPUImageMultiplyBlendFilter();
//    m_pFilter = new GPUImageNormalBlendFilter();
//    m_pFilter = new GPUImageOpacityFilter();
//    m_pFilter = new GPUImageOverlayBlendFilter();
//    m_pFilter = new GPUImagePerlinNoiseFilter();
//    m_pFilter = new GPUImagePinchDistortionFilter();
    m_pFilter = new GPUImagePixellateFilter();
}

bool NativeRender::draw(int textureId, int viewWidth, int viewHeight)
{
    if(!m_pFilter){
        return false;
    }

    LOGI("NativeRender::draw...");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, viewWidth, viewHeight);
    return m_pFilter->draw(textureId, viewWidth, viewHeight);
}

bool NativeRender::setFrontCamera(bool front)
{
    m_bFrontCamera = front;

    if(NULL != m_pFilter){
        if(m_bFrontCamera){
            m_pFilter->setTextureCoordinate(textureCoord_front);
        }else{
            m_pFilter->setTextureCoordinate(textureCoord_back);
        }
    }

    return true;
}