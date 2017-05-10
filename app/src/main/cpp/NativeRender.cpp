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
#include "GPUImage/GPUImagePixellatePositionFilter.h"
#include "GPUImage/GPUImagePolarPixellateFilter.h"
#include "GPUImage/GPUImagePolkaDotFilter.h"
#include "GPUImage/GPUImagePosterizeFilter.h"
#include "GPUImage/GPUImageRGBFilter.h"
#include "GPUImage/GPUImageSaturationBlendFilter.h"
#include "GPUImage/GPUImageScreenBlendFilter.h"
#include "GPUImage/GPUImageSharpenFilter.h"
#include "GPUImage/GPUImageSkinToneFilter.h"
#include "GPUImage/GPUImageSoftLightBlendFilter.h"
#include "GPUImage/GPUImageSourceOverBlendFilter.h"
#include "GPUImage/GPUImageSubtractBlendFilter.h"
#include "GPUImage/GPUImageSphereRefractionFilter.h"
#include "GPUImage/GPUImageStretchDistortionFilter.h"
#include "GPUImage/GPUImageSwirlFilter.h"
#include "GPUImage/GPUImageVibranceFilter.h"
#include "GPUImage/GPUImageVignetteFilter.h"
#include "GPUImage/GPUImageWhiteBalanceFilter.h"
#include "GPUImage/GPUImageZoomBlurFilter.h"
#include "GPUImage/GPUImagePoissonBlendFilter.h"
#include "GPUImage/GPUImageSobelEdgeDetectionFilter.h"
#include "GPUImage/GPUImagePrewittEdgeDetectionFilter.h"
#include "GPUImage/GPUImageThresholdEdgeDetectionFilter.h"
#include "GPUImage/GPUImageSketchFilter.h"
#include "GPUImage/GPUImageXYDerivativeFilter.h"
#include "GPUImage/GPUImageThresholdSketchFilter.h"
#include "GPUImage/GPUImageDilationFilter.h"
#include "GPUImage/GPUImageRGBDilationFilter.h"
#include "GPUImage/GPUImageErosionFilter.h"
#include "GPUImage/GPUImageRGBErosionFilter.h"
#include "GPUImage/GPUImageLanczosResamplingFilter.h"
#include "GPUImage/GPUImageGaussianBlurFilter.h"
#include "GPUImage/GPUImageGaussianBlurPositionFilter.h"
#include "GPUImage/GPUImageBilateralFilter.h"
#include "GPUImage/GPUImageBoxBlurFilter.h"
#include "GPUImage/GPUImageSingleComponentGaussianBlurFilter.h"
#include "GPUImage/GPUImageVoronoiConsumerFilter.h"
#include "GPUImage/GPUImageGlassSphereFilter.h"
#include "GPUImage/GPUImageJFAVoronoiFilter.h"
#include "GPUImage/GPUImageToneCurveFilter.h"
#include "GPUImage/GPUImageCropFilter.h"
#include "GPUImage/GPUImageAdaptiveThresholdFilter.h"
#include "GPUImage/GPUImageCannyEdgeDetectionFilter.h"
#include "GPUImage/GPUImageClosingFilter.h"
#include "GPUImage/GPUImageOpeningFilter.h"
#include "GPUImage/GPUImageRGBClosingFilter.h"
#include "GPUImage/GPUImageRGBOpeningFilter.h"
#include "GPUImage/GPUImageColourFASTFeatureDetector.h"
#include "GPUImage/GPUImageGaussianSelectiveBlurFilter.h"
#include "GPUImage/GPUImageHalftoneFilter.h"
#include "GPUImage/GPUImageiOSBlurFilter.h"
#include "GPUImage/GPUImageSmoothToonFilter.h"
#include "GPUImage/GPUImageSoftEleganceFilter.h"


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

    m_pFilter->setTextureSize(1280, 720);

    m_pFilter->setVertexCoordinate(vertex_coordinate);
    if(m_bFrontCamera){
        m_pFilter->setTextureRotation(ROTATION_270);
        m_pFilter->setTextureCoordinate(textureCoord_front);
    }else{
        m_pFilter->setTextureRotation(ROTATION_90);
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
//    m_pFilter = new GPUImagePixellateFilter();
//    m_pFilter = new GPUImagePixellatePositionFilter();
//    m_pFilter = new GPUImagePolarPixellateFilter();
//    m_pFilter = new GPUImagePolkaDotFilter();
//    m_pFilter = new GPUImagePosterizeFilter();
//    m_pFilter = new GPUImageRGBFilter();
//    m_pFilter = new GPUImageSaturationBlendFilter();
//    m_pFilter = new GPUImageScreenBlendFilter();
//    m_pFilter = new GPUImageSharpenFilter();
//    m_pFilter = new GPUImageSkinToneFilter();
//    m_pFilter = new GPUImageSoftLightBlendFilter();
//    m_pFilter = new GPUImageSourceOverBlendFilter();
//    m_pFilter = new GPUImageSubtractBlendFilter();
//    m_pFilter = new GPUImageSphereRefractionFilter();
//    m_pFilter = new GPUImageStretchDistortionFilter();
//    m_pFilter = new GPUImageSwirlFilter();
//    m_pFilter = new GPUImageVibranceFilter();
//    m_pFilter = new GPUImageVignetteFilter();
//    m_pFilter = new GPUImageWhiteBalanceFilter();
//    m_pFilter = new GPUImageZoomBlurFilter();
//    m_pFilter = new GPUImagePoissonBlendFilter();
//    m_pFilter = new GPUImageSobelEdgeDetectionFilter();
//    m_pFilter = new GPUImagePrewittEdgeDetectionFilter();
//    m_pFilter = new GPUImageThresholdEdgeDetectionFilter();
//    m_pFilter = new GPUImageSketchFilter();
//    m_pFilter = new GPUImageXYDerivativeFilter();
//    m_pFilter = new GPUImageThresholdSketchFilter();
//    m_pFilter = new GPUImageDilationFilter();
//    m_pFilter = new GPUImageRGBDilationFilter();
//    m_pFilter = new GPUImageErosionFilter();
//    m_pFilter = new GPUImageRGBErosionFilter();
//    m_pFilter = new GPUImageLanczosResamplingFilter();
//    m_pFilter = new GPUImageGaussianBlurFilter();
//    m_pFilter = new GPUImageGaussianBlurPositionFilter();
//    m_pFilter = new GPUImageBilateralFilter();
//    m_pFilter = new GPUImageBoxBlurFilter();
//    m_pFilter = new GPUImageSingleComponentGaussianBlurFilter();
//    m_pFilter = new GPUImageVoronoiConsumerFilter();
//    m_pFilter = new GPUImageGlassSphereFilter();
//    m_pFilter = new GPUImageJFAVoronoiFilter();
//    m_pFilter = new GPUImageToneCurveFilter();
//    m_pFilter = new GPUImageCropFilter();
//    m_pFilter = new GPUImageAdaptiveThresholdFilter();
//    m_pFilter = new GPUImageCannyEdgeDetectionFilter();
//    m_pFilter = new GPUImageClosingFilter();
//    m_pFilter = new GPUImageOpeningFilter();
//    m_pFilter = new GPUImageRGBClosingFilter();
//    m_pFilter = new GPUImageRGBOpeningFilter();
//    m_pFilter = new GPUImageColourFASTFeatureDetector();
//    m_pFilter = new GPUImageGaussianSelectiveBlurFilter();
//    m_pFilter = new GPUImageHalftoneFilter();
//    m_pFilter = new GPUImageiOSBlurFilter();
//    m_pFilter = new GPUImageSmoothToonFilter();
    m_pFilter = new GPUImageSoftEleganceFilter();
}

bool NativeRender::draw(int textureId, int viewWidth, int viewHeight)
{
    if(!m_pFilter){
        return false;
    }

    LOGI("NativeRender::draw...");
    return m_pFilter->draw(textureId, viewWidth, viewHeight);
}

bool NativeRender::setFrontCamera(bool front)
{
    m_bFrontCamera = front;

    if(NULL != m_pFilter){
        if(m_bFrontCamera){
            m_pFilter->setTextureRotation(ROTATION_270);
            m_pFilter->setTextureCoordinate(textureCoord_front);
        }else{
            m_pFilter->setTextureRotation(ROTATION_90);
            m_pFilter->setTextureCoordinate(textureCoord_back);
        }
    }

    return true;
}


bool NativeRender::setPercent(int percent)
{
    if(!m_pFilter){
        return false;
    }

    GPUImageCropFilter* filter = dynamic_cast<GPUImageCropFilter*>(m_pFilter);
    if(NULL != filter){
        filter->setCropRegion(GLRect(0.0, 0.0, 1.0, 1.0*percent/100));
    }

    return true;
}

