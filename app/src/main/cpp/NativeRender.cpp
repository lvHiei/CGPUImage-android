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
#include "GPUImage/GPUImageTiltShiftFilter.h"
#include "GPUImage/GPUImageUnsharpMaskFilter.h"
#include "GPUImage/GPUImageTransformFilter.h"


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

    m_bWantStopRender = false;
    m_bWantChangeFilter = false;
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

    m_bWantChangeFilter = false;
    m_bWantStopRender = false;

    m_fMaxValue = 1.0f;
    m_fMinValue = 0.0f;

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
    m_iFilterType = filterType;

    switch (filterType){
        case FILTER_3X3_CONVOLUTION:
            m_pFilter = new GPUImage3x3ConvolutionFilter();
            break;

        case FILTER_ADAPTIVE_THRESHOLD:
            m_pFilter = new GPUImageAdaptiveThresholdFilter();
            m_fMaxValue  = 20.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_ADD_BLEND:
            m_pFilter = new GPUImageAddBlendFilter();
            break;
        case FILTER_ALPHA_BLEND:
            m_pFilter = new GPUImageAlphaBlendFilter();
            break;
        case FILTER_AMATORKA:
            m_pFilter = new GPUImageAmatorkaFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;

        case FILTER_BILATERAL:
            m_pFilter = new GPUImageBilateralFilter();
            m_fMaxValue = 10.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_BOXBLUR:
            m_pFilter = new GPUImageBoxBlurFilter();
            m_fMaxValue = 24.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_BRIGHTNESS:
            m_pFilter = new GPUImageBrightnessFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = -1.0f;
            break;
        case FILTER_BULGE_DISTORTION:
            m_pFilter = new GPUImageBulgeDistortionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = -1.0f;
            break;

        case FILTER_CANNY_EDGE_DETECTION:
            m_pFilter = new GPUImageCannyEdgeDetectionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_CGA_COLORSPACE:
            m_pFilter = new GPUImageCGAColorspaceFilter();
            break;
        case FILTER_CHROMAKEY_BLEND:
            m_pFilter = new GPUImageChromaKeyBlendFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_CHROMAKEY:
            m_pFilter = new GPUImageChromaKeyFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_CLOSING:
            m_pFilter = new GPUImageClosingFilter();
            break;
        case FILTER_COLOR_BLEND:
            m_pFilter = new GPUImageColorBlendFilter();
            break;
        case FILTER_COLOR_BURN_BLEND:
            m_pFilter = new GPUImageColorBurnBlendFilter();
            break;
        case FILTER_COLOR_DODGE_BLEND:
            m_pFilter = new GPUImageColorDodgeBlendFilter();
            break;
        case FILTER_COLOR_INVERT:
            m_pFilter = new GPUImageColorInvertFilter();
            break;
        case FILTER_COLOR_LOCAL_BINARY_PATTERN:
            m_pFilter = new GPUImageColorLocalBinaryPatternFilter();
            break;
        case FILTER_COLOR_MATRIX:
            m_pFilter = new GPUImageColorMatrixFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_COLOR_PACKING:
            m_pFilter = new GPUImageColorPackingFilter();
            break;
        case FILTER_COLOUR_FAST_FEATURE_DETECTOR:
            m_pFilter = new GPUImageColourFASTFeatureDetector();
            break;
        case FILTER_COLOUR_FAST_SAMPLING_OPERATION:
            m_pFilter = new GPUImageColourFASTSamplingOperation();
            break;
        case FILTER_CONTRAST:
            m_pFilter = new GPUImageContrastFilter();
            m_fMaxValue = 4.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_CROP:
            m_pFilter = new GPUImageCropFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.2f;
            break;
        case FILTER_CROSSHATCH:
            m_pFilter = new GPUImageCrosshatchFilter();
            m_fMaxValue = 0.06f;
            m_fMinValue = 0.01f;
            break;

        case FILTER_DARKEN_BLEND:
            m_pFilter = new GPUImageDarkenBlendFilter();
            break;
        case FILTER_DIFFERENCE_BLEND:
            m_pFilter = new GPUImageDifferenceBlendFilter();
            break;
        case FILTER_DILATION:
            m_pFilter = new GPUImageDilationFilter();
            break;
        case FILTER_DIRECTIONAL_NON_MAXIMUM_SUPPRESSION:
            m_pFilter = new GPUImageDirectionalNonMaximumSuppressionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.2f;
            break;
        case FILTER_DIRECTIONAL_SOBEL_EDGE_DETECTION:
            m_pFilter = new GPUImageDirectionalSobelEdgeDetectionFilter();
            break;
        case FILTER_DISSOLVE_BLEND:
            m_pFilter = new GPUImageDissolveBlendFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_DIVIDE_BLEND:
            m_pFilter = new GPUImageDivideBlendFilter();
            break;

        case FILTER_EMBOSS:
            m_pFilter = new GPUImageEmbossFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_EROSION:
            m_pFilter = new GPUImageErosionFilter();
            break;
        case FILTER_EXCLUSION_BLEND:
            m_pFilter = new GPUImageExclusionBlendFilter();
            break;
        case FILTER_EXPOSURE:
            m_pFilter = new GPUImageExposureFilter();
            m_fMaxValue = 4.0f;
            m_fMinValue = -4.0f;
            break;

        case FILTER_FALSE_COLOR:
            m_pFilter = new GPUImageFalseColorFilter();
            break;

        case FILTER_GAMMA:
            m_pFilter = new GPUImageGammaFilter();
            m_fMaxValue = 3.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_GAUSSIAN_BLUR:
            m_pFilter = new GPUImageGaussianBlurFilter();
            m_fMaxValue = 24.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_GAUSSIAN_BLUR_POSITION:
            m_pFilter = new GPUImageGaussianBlurPositionFilter();
            m_fMaxValue = 0.75f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_GAUSSIAN_SELECTIVE_BLUR:
            m_pFilter = new GPUImageGaussianSelectiveBlurFilter();
            m_fMaxValue = 0.75f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_GLASS_SPHERE:
            m_pFilter = new GPUImageGlassSphereFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_GREYSCALE:
            m_pFilter = new GPUImageGreyscaleFilter();
            break;

        case FILTER_HALFTONE:
            m_pFilter = new GPUImageHalftoneFilter();
            m_fMaxValue = 0.05f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_HARD_LIGHT_BLEND:
            m_pFilter = new GPUImageHardLightBlendFilter();
            break;
        case FILTER_HAZE:
            m_pFilter = new GPUImageHazeFilter();
            m_fMaxValue = 0.2f;
            m_fMinValue = -0.2f;
            break;
        case FILTER_HIGHLIGHT_SHADOW:
            m_pFilter = new GPUImageHighlightShadowFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_HIGHLIGHT_SHADOW_TINT:
            m_pFilter = new GPUImageHighlightShadowTintFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_HSB:
            m_pFilter = new GPUImageHSBFilter();
            break;
        case FILTER_HUE_BLEND:
            m_pFilter = new GPUImageHueBlendFilter();
            break;
        case FILTER_HUE:
            m_pFilter = new GPUImageHueFilter();
            break;

        case FILTER_IOS_BLURE:
            m_pFilter = new GPUImageiOSBlurFilter();
            break;

        case FILTER_JFA_VORONOI:
            m_pFilter = new GPUImageJFAVoronoiFilter();
            break;

        case FILTER_KUWAHARA:
            m_pFilter = new GPUImageKuwaharaFilter();
            m_fMaxValue = 8.0f;
            m_fMinValue = 3.0f;
            break;
        case FILTER_KUWAHARA_RADIUS3:
            m_pFilter = new GPUImageKuwaharaRadius3Filter();
            break;

        case FILTER_LANCZOS_RESAMPLING:
            m_pFilter = new GPUImageLanczosResamplingFilter();
            break;
        case FILTER_LAPLACIAN:
            m_pFilter = new GPUImageLaplacianFilter();
            break;
        case FILTER_LEVELS:
            m_pFilter = new GPUImageLevelsFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_LIGHTEN_BLEND:
            m_pFilter = new GPUImageLightenBlendFilter();
            break;
        case FILTER_LINEAR_BURN_BLEND:
            m_pFilter = new GPUImageLinearBurnBlendFilter();
            break;
        case FILTER_LOCAL_BINARY_PATTERN:
            m_pFilter = new GPUImageLocalBinaryPatternFilter();
            m_fMaxValue = 5.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_LUMINANCE_RANGE:
            m_pFilter = new GPUImageLuminanceRangeFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_LUMINANCE_THRESHOLD:
            m_pFilter = new GPUImageLuminanceThresholdFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_LUMINOSITY_BLEND:
            m_pFilter = new GPUImageLuminosityBlendFilter();
            break;

        case FILTER_MASK:
            m_pFilter = new GPUImageMaskFilter();
            break;
        case FILTER_MEDIAN:
            m_pFilter = new GPUImageMedianFilter();
            break;
        case FILTER_MISS_ETIKATE:
            m_pFilter = new GPUImageMissEtikateFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_MONOCHROME:
            m_pFilter = new GPUImageMonochromeFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_MOSAIC:
            m_pFilter = new GPUImageMosaicFilter();
            m_fMaxValue = 0.05f;
            m_fMinValue = 0.002f;
            break;
        case FILTER_MOTION_BLUR:
            m_pFilter = new GPUImageMotionBlurFilter();
            m_fMaxValue = 180.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_MULTIPLY_BLEND:
            m_pFilter = new GPUImageMultiplyBlendFilter();
            break;

        case FILTER_NON_MAXIMUM_SUPPRESSION:
            m_pFilter = new GPUImageNonMaximumSuppressionFilter();
            break;
        case FILTER_NORMAL_BLEND:
            m_pFilter = new GPUImageNormalBlendFilter();
            break;

        case FILTER_OPACITY:
            m_pFilter = new GPUImageOpacityFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_OPENING:
            m_pFilter = new GPUImageOpeningFilter();
            break;
        case FILTER_OVERLAY_BLEND:
            m_pFilter = new GPUImageOverlayBlendFilter();
            break;

        case FILTER_PERLIN_NOISE:
            m_pFilter = new GPUImagePerlinNoiseFilter();
            m_fMaxValue = 30.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_PINCH_DISTORTION:
            m_pFilter = new GPUImagePinchDistortionFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = -2.0f;
            break;
        case FILTER_PIXELLATE:
            m_pFilter = new GPUImagePixellateFilter();
            m_fMaxValue = 0.3f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_PIXELLATE_POSITION:
            m_pFilter = new GPUImagePixellatePositionFilter();
            m_fMaxValue = 0.5f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_POISSON_BLEND:
            m_pFilter = new GPUImagePoissonBlendFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_POLAR_PIXELLATE:
            m_pFilter = new GPUImagePolarPixellateFilter();
            m_fMaxValue = 0.1f;
            m_fMinValue = -0.1f;
            break;
        case FILTER_POLKA_DOT:
            m_pFilter = new GPUImagePolkaDotFilter();
            m_fMaxValue = 0.3f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_POSTERIZE:
            m_pFilter = new GPUImagePosterizeFilter();
            m_fMaxValue = 20.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_PREWITT_EDGE_DETECTION:
            m_pFilter = new GPUImagePrewittEdgeDetectionFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;

        case FILTER_RGB_CLOSING:
            m_pFilter = new GPUImageRGBClosingFilter();
            break;
        case FILTER_RGB_DILATION:
            m_pFilter = new GPUImageRGBDilationFilter();
            break;
        case FILTER_RGB_EROSION:
            m_pFilter = new GPUImageRGBErosionFilter();
            break;
        case FILTER_RGB:
            m_pFilter = new GPUImageRGBFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_RGB_OPENING:
            m_pFilter = new GPUImageRGBOpeningFilter();
            break;

        case FILTER_SATURATION_BLEND:
            m_pFilter = new GPUImageSaturationBlendFilter();
            break;
        case FILTER_SATURATION:
            m_pFilter = new GPUImageSaturationFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_SCREEN_BLEND:
            m_pFilter = new GPUImageScreenBlendFilter();
            break;
        case FILTER_SEPIA:
            m_pFilter = new GPUImageSepiaFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_SHARPEN:
            m_pFilter = new GPUImageSharpenFilter();
            m_fMaxValue = 4.0f;
            m_fMinValue = -1.0f;
            break;
        case FILTER_SINGLE_COMPONENT_GAUSSIAN_BLUR:
            m_pFilter = new GPUImageSingleComponentGaussianBlurFilter();
            m_fMaxValue = 24.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_SKETCH:
            m_pFilter = new GPUImageSketchFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_SKIN_TONE:
            m_pFilter = new GPUImageSkinToneFilter();
            break;
        case FILTER_SMOOTH_TOON:
            m_pFilter = new GPUImageSmoothToonFilter();
            m_fMaxValue = 6.0f;
            m_fMinValue = 1.0f;
            break;
        case FILTER_SOBEL_EDGE_DETECTION:
            m_pFilter = new GPUImageSobelEdgeDetectionFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_SOFT_ELEGANCE:
            m_pFilter = new GPUImageSoftEleganceFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_SOFT_LIGHT_BLEND:
            m_pFilter = new GPUImageSoftLightBlendFilter();
            break;
        case FILTER_SOURCE_OVER_BLEND:
            m_pFilter = new GPUImageSourceOverBlendFilter();
            break;
        case FILTER_SPHERE_REFRACTION:
            m_pFilter = new GPUImageSphereRefractionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_STRETCH_DISTORTION:
            m_pFilter = new GPUImageStretchDistortionFilter();
            break;
        case FILTER_SUBTRACT_BLEND:
            m_pFilter = new GPUImageSubtractBlendFilter();
            break;
        case FILTER_SWIRL:
            m_pFilter = new GPUImageSwirlFilter();
            m_fMaxValue = 2.0f;
            m_fMinValue = 0.0f;
            break;

        case FILTER_THRESHOLD_EDGE_DETECTION:
            m_pFilter = new GPUImageThresholdEdgeDetectionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_THRESHOLDED_NON_MAXIMUM_SUPPRESSION:
            m_pFilter = new GPUImageThresholdedNonMaximumSuppressionFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_THRESHOLD_SKETCH:
            m_pFilter = new GPUImageThresholdSketchFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_TILT_SHIFT:
            m_pFilter = new GPUImageTiltShiftFilter();
            m_fMaxValue = 0.8f;
            m_fMinValue = 0.2f;
            break;
        case FILTER_TONE_CURVE:
            m_pFilter = new GPUImageToneCurveFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_TOON:
            m_pFilter = new GPUImageToonFilter();
            break;
        case FILTER_TRANSFORM:
            m_pFilter = new GPUImageTransformFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;

        case FILTER_UNSHARP_MASK:
            m_pFilter = new GPUImageUnsharpMaskFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;

        case FILTER_VIBRANCE:
            m_pFilter = new GPUImageVibranceFilter();
            m_fMaxValue = 1.0f;
            m_fMinValue = 0.0f;
            break;
        case FILTER_VIGNETTE:
            m_pFilter = new GPUImageVignetteFilter();
            m_fMaxValue = 0.9f;
            m_fMinValue = 0.5f;
            break;
        case FILTER_VORONOI_CONSUMER:
            m_pFilter = new GPUImageVoronoiConsumerFilter();
            break;

        case FILTER_WEAK_PIXEL_INCLUSION:
            m_pFilter = new GPUImageWeakPixelInclusionFilter();
            break;
        case FILTER_WHITE_BALANCE:
            m_pFilter = new GPUImageWhiteBalanceFilter();
            m_fMaxValue = 7500.0f;
            m_fMinValue = 2500.0f;
            break;

        case FILTER_XY_DERIVATIVE:
            m_pFilter = new GPUImageXYDerivativeFilter();
            break;
        case FILTER_ZOOM:
            m_pFilter = new GPUImageZoomBlurFilter();
            m_fMaxValue = 2.5f;
            m_fMinValue = 0.0f;
            break;

        default:
            m_pFilter = new GPUImageFilter();
            break;
    }
}

bool NativeRender::draw(int textureId, int viewWidth, int viewHeight)
{
    if(!m_pFilter){
        return false;
    }

    if(m_bWantStopRender){
        m_bWantStopRender = false;
        delete m_pFilter;
        m_pFilter = NULL;
        return true;
    }

    if(m_bWantChangeFilter){
        m_bWantChangeFilter = false;
        if(m_pFilter){
            delete m_pFilter;
            m_pFilter = NULL;
        }

        intenalCreateFilter(m_iFilterType);
    }


//    LOGI("NativeRender::draw...");
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

    float curValue = m_fMinValue + percent * (m_fMaxValue - m_fMinValue) / 100.0;

    switch (m_iFilterType){
        case FILTER_3X3_CONVOLUTION:
            break;

        case FILTER_ADAPTIVE_THRESHOLD:
        {
            GPUImageAdaptiveThresholdFilter* filter = dynamic_cast<GPUImageAdaptiveThresholdFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadiusInPixels(curValue);
            }
        }
            break;
        case FILTER_ADD_BLEND:
            break;
        case FILTER_ALPHA_BLEND:
            break;
        case FILTER_AMATORKA:
        {
            GPUImageAmatorkaFilter* filter = dynamic_cast<GPUImageAmatorkaFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;

        case FILTER_BILATERAL:
        {
            GPUImageBilateralFilter* filter = dynamic_cast<GPUImageBilateralFilter*>(m_pFilter);
            if(filter){
                filter->setDistanceNormalizationFactor(curValue);
            }
        }

            break;
        case FILTER_BOXBLUR:
        {
            GPUImageBoxBlurFilter* filter = dynamic_cast<GPUImageBoxBlurFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadiusInPixels(curValue);
            }
        }
            break;
        case FILTER_BRIGHTNESS:
        {
            GPUImageBrightnessFilter* filter = dynamic_cast<GPUImageBrightnessFilter*>(m_pFilter);
            if(filter){
                filter->setBrightness(curValue);
            }
        }
            break;
        case FILTER_BULGE_DISTORTION:
        {
            GPUImageBulgeDistortionFilter* filter = dynamic_cast<GPUImageBulgeDistortionFilter*>(m_pFilter);
            if(filter){
                filter->setScale(curValue);
            }
        }
            break;

        case FILTER_CANNY_EDGE_DETECTION:
        {
            GPUImageCannyEdgeDetectionFilter* filter = dynamic_cast<GPUImageCannyEdgeDetectionFilter*>(m_pFilter);
            if(filter){
                filter->setBlurTexelSpacingMultiplier(curValue);
            }
        }
            break;
        case FILTER_CGA_COLORSPACE:
            break;
        case FILTER_CHROMAKEY_BLEND:
        {
            GPUImageChromaKeyBlendFilter* filter = dynamic_cast<GPUImageChromaKeyBlendFilter*>(m_pFilter);
            if(filter){
                filter->setThresholdSensitivity(curValue);
            }
        }
            break;
        case FILTER_CHROMAKEY:
        {
            GPUImageChromaKeyFilter* filter = dynamic_cast<GPUImageChromaKeyFilter*>(m_pFilter);
            if(filter){
                filter->setThresholdSensitivity(curValue);
            }
        }
            break;
        case FILTER_CLOSING:
            break;
        case FILTER_COLOR_BLEND:
            break;
        case FILTER_COLOR_BURN_BLEND:
            break;
        case FILTER_COLOR_DODGE_BLEND:
            break;
        case FILTER_COLOR_INVERT:
            break;
        case FILTER_COLOR_LOCAL_BINARY_PATTERN:
            break;
        case FILTER_COLOR_MATRIX:
        {
            GPUImageColorMatrixFilter* filter = dynamic_cast<GPUImageColorMatrixFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;
        case FILTER_COLOR_PACKING:
            break;
        case FILTER_COLOUR_FAST_FEATURE_DETECTOR:
            break;
        case FILTER_COLOUR_FAST_SAMPLING_OPERATION:
            break;
        case FILTER_CONTRAST:
        {
            GPUImageContrastFilter* filter = dynamic_cast<GPUImageContrastFilter*>(m_pFilter);
            if(filter){
                filter->setContrast(curValue);
            }
        }
            break;
        case FILTER_CROP:
        {
            GPUImageCropFilter* filter = dynamic_cast<GPUImageCropFilter*>(m_pFilter);
            if(filter){
                filter->setCropRegion(GLRect(0.0, 0.0, 1.0, curValue));
            }
        }
            break;
        case FILTER_CROSSHATCH:
        {
            GPUImageCrosshatchFilter* filter = dynamic_cast<GPUImageCrosshatchFilter*>(m_pFilter);
            if(filter){
                filter->setCrossHatchSpacing(curValue);
            }
        }
            break;

        case FILTER_DARKEN_BLEND:
            break;
        case FILTER_DIFFERENCE_BLEND:
            break;
        case FILTER_DILATION:
            break;
        case FILTER_DIRECTIONAL_NON_MAXIMUM_SUPPRESSION:
        {
            GPUImageDirectionalNonMaximumSuppressionFilter* filter = dynamic_cast<GPUImageDirectionalNonMaximumSuppressionFilter*>(m_pFilter);
            if(filter){
                filter->setUpperThreshold(curValue);
            }
        }
            break;
        case FILTER_DIRECTIONAL_SOBEL_EDGE_DETECTION:
            break;
        case FILTER_DISSOLVE_BLEND:
        {
            GPUImageDissolveBlendFilter* filter = dynamic_cast<GPUImageDissolveBlendFilter*>(m_pFilter);
            if(filter){
                filter->setMix(curValue);
            }
        }
            break;
        case FILTER_DIVIDE_BLEND:
            break;

        case FILTER_EMBOSS:
        {
            GPUImageEmbossFilter* filter = dynamic_cast<GPUImageEmbossFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;
        case FILTER_EROSION:
            break;
        case FILTER_EXCLUSION_BLEND:
            break;
        case FILTER_EXPOSURE:
        {
            GPUImageExposureFilter* filter = dynamic_cast<GPUImageExposureFilter*>(m_pFilter);
            if(filter){
                filter->setExposure(curValue);
            }
        }
            break;

        case FILTER_FALSE_COLOR:
            break;

        case FILTER_GAMMA:
        {
            GPUImageGammaFilter* filter = dynamic_cast<GPUImageGammaFilter*>(m_pFilter);
            if(filter){
                filter->setGamma(curValue);
            }
        }
            break;
        case FILTER_GAUSSIAN_BLUR:
        {
            GPUImageGaussianBlurFilter* filter = dynamic_cast<GPUImageGaussianBlurFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadiusInPixels(curValue);
            }
        }
            break;
        case FILTER_GAUSSIAN_BLUR_POSITION:
        {
            GPUImageGaussianBlurPositionFilter* filter = dynamic_cast<GPUImageGaussianBlurPositionFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadius(curValue);
            }
        }
            break;
        case FILTER_GAUSSIAN_SELECTIVE_BLUR:
        {
            GPUImageGaussianSelectiveBlurFilter* filter = dynamic_cast<GPUImageGaussianSelectiveBlurFilter*>(m_pFilter);
            if(filter){
                filter->setExcludeCircleRadius(curValue);
            }
        }
            break;
        case FILTER_GLASS_SPHERE:
        {
            GPUImageGlassSphereFilter* filter = dynamic_cast<GPUImageGlassSphereFilter*>(m_pFilter);
            if(filter){
                filter->setRadius(curValue);
            }
        }
            break;
        case FILTER_GREYSCALE:
            break;

        case FILTER_HALFTONE:
        {
            GPUImageHalftoneFilter* filter = dynamic_cast<GPUImageHalftoneFilter*>(m_pFilter);
            if(filter){
                filter->setFractionalWidthOfAPixel(curValue);
            }
        }
            break;
        case FILTER_HARD_LIGHT_BLEND:
            break;
        case FILTER_HAZE:
        {
            GPUImageHazeFilter* filter = dynamic_cast<GPUImageHazeFilter*>(m_pFilter);
            if(filter){
                filter->setDistance(curValue);
            }
        }
            break;
        case FILTER_HIGHLIGHT_SHADOW:
        {
            GPUImageHighlightShadowFilter* filter = dynamic_cast<GPUImageHighlightShadowFilter*>(m_pFilter);
            if(filter){
                filter->setHighlights(curValue);
            }
        }
            break;
        case FILTER_HIGHLIGHT_SHADOW_TINT:
        {
            GPUImageHighlightShadowTintFilter* filter = dynamic_cast<GPUImageHighlightShadowTintFilter*>(m_pFilter);
            if(filter){
                filter->setHighlightTintIntensity(curValue);
            }
        }
            break;
        case FILTER_HSB:
            break;
        case FILTER_HUE_BLEND:
            break;
        case FILTER_HUE:
            break;

        case FILTER_IOS_BLURE:
            break;

        case FILTER_JFA_VORONOI:
            break;

        case FILTER_KUWAHARA:
        {
            GPUImageKuwaharaFilter* filter = dynamic_cast<GPUImageKuwaharaFilter*>(m_pFilter);
            if(filter){
                filter->setRadius(curValue);
            }
        }
            break;
        case FILTER_KUWAHARA_RADIUS3:
            break;

        case FILTER_LANCZOS_RESAMPLING:
            break;
        case FILTER_LAPLACIAN:
            break;
        case FILTER_LEVELS:
        {
            GPUImageLevelsFilter* filter = dynamic_cast<GPUImageLevelsFilter*>(m_pFilter);
            if(filter){
                filter->setRedMin(curValue, 1.0, 1.0, 0.0, 1.0);
                filter->setGreenMin(curValue, 1.0, 1.0, 0.0, 1.0);
                filter->setBlueMin(curValue, 1.0, 1.0, 0.0, 1.0);
            }
        }
            break;
        case FILTER_LIGHTEN_BLEND:
            break;
        case FILTER_LINEAR_BURN_BLEND:
            break;
        case FILTER_LOCAL_BINARY_PATTERN:
        {
            GPUImageLocalBinaryPatternFilter* filter = dynamic_cast<GPUImageLocalBinaryPatternFilter*>(m_pFilter);
            if(filter){
                filter->setTexelWidth(curValue/1280);
                filter->setTexelHeight(curValue/720);
            }
        }
            break;
        case FILTER_LUMINANCE_RANGE:
        {
            GPUImageLuminanceRangeFilter* filter = dynamic_cast<GPUImageLuminanceRangeFilter*>(m_pFilter);
            if(filter){
                filter->setRangeReductionFactor(curValue);
            }
        }

            break;
        case FILTER_LUMINANCE_THRESHOLD:
        {
            GPUImageLuminanceThresholdFilter* filter = dynamic_cast<GPUImageLuminanceThresholdFilter*>(m_pFilter);
            if(filter){
                filter->setThreshold(curValue);
            }
        }
            break;
        case FILTER_LUMINOSITY_BLEND:
            break;

        case FILTER_MASK:
            break;
        case FILTER_MEDIAN:
            break;
        case FILTER_MISS_ETIKATE:
        {
            GPUImageMissEtikateFilter* filter = dynamic_cast<GPUImageMissEtikateFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;
        case FILTER_MONOCHROME:
        {
            GPUImageMonochromeFilter* filter = dynamic_cast<GPUImageMonochromeFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;
        case FILTER_MOSAIC:
        {
            GPUImageMosaicFilter* filter = dynamic_cast<GPUImageMosaicFilter*>(m_pFilter);
            if(filter){
                filter->setDisplaySize(curValue, curValue);
            }
        }
            break;
        case FILTER_MOTION_BLUR:
        {
            GPUImageMotionBlurFilter* filter = dynamic_cast<GPUImageMotionBlurFilter*>(m_pFilter);
            if(filter){
                filter->setBlurAngle(curValue);
            }
        }
            break;
        case FILTER_MULTIPLY_BLEND:
            break;

        case FILTER_NON_MAXIMUM_SUPPRESSION:
            break;
        case FILTER_NORMAL_BLEND:
            break;

        case FILTER_OPACITY:
        {
            GPUImageOpacityFilter* filter = dynamic_cast<GPUImageOpacityFilter*>(m_pFilter);
            if(filter){
                filter->setOpacity(curValue);
            }
        }
            break;
        case FILTER_OPENING:
            break;
        case FILTER_OVERLAY_BLEND:
            break;

        case FILTER_PERLIN_NOISE:
        {
            GPUImagePerlinNoiseFilter* filter = dynamic_cast<GPUImagePerlinNoiseFilter*>(m_pFilter);
            if(filter){
                filter->setScale(curValue);
            }
        }
            break;
        case FILTER_PINCH_DISTORTION:
        {
            GPUImagePinchDistortionFilter* filter = dynamic_cast<GPUImagePinchDistortionFilter*>(m_pFilter);
            if(filter){
                filter->setScale(curValue);
            }
        }
            break;
        case FILTER_PIXELLATE:
        {
            GPUImagePixellateFilter* filter = dynamic_cast<GPUImagePixellateFilter*>(m_pFilter);
            if(filter){
                filter->setFractionalWidthOfAPixel(curValue);
            }
        }
            break;
        case FILTER_PIXELLATE_POSITION:
        {
            GPUImagePixellatePositionFilter* filter = dynamic_cast<GPUImagePixellatePositionFilter*>(m_pFilter);
            if(filter){
                filter->setRadius(curValue);
            }
        }
            break;
        case FILTER_POISSON_BLEND:
        {
            GPUImagePoissonBlendFilter* filter = dynamic_cast<GPUImagePoissonBlendFilter*>(m_pFilter);
            if(filter){
                filter->setMix(curValue);
            }
        }
            break;
        case FILTER_POLAR_PIXELLATE:
        {
            GPUImagePolarPixellateFilter* filter = dynamic_cast<GPUImagePolarPixellateFilter*>(m_pFilter);
            if(filter){
                filter->setPixelSize(curValue, curValue);
            }
        }
            break;
        case FILTER_POLKA_DOT:
        {
            GPUImagePolkaDotFilter* filter = dynamic_cast<GPUImagePolkaDotFilter*>(m_pFilter);
            if(filter){
                filter->setFractionalWidthOfAPixel(curValue);
            }
        }
            break;
        case FILTER_POSTERIZE:
        {
            GPUImagePosterizeFilter* filter = dynamic_cast<GPUImagePosterizeFilter*>(m_pFilter);
            if(filter){
                filter->setColorLevels(curValue);
            }
        }

            break;
        case FILTER_PREWITT_EDGE_DETECTION:
        {
            GPUImagePrewittEdgeDetectionFilter* filter = dynamic_cast<GPUImagePrewittEdgeDetectionFilter*>(m_pFilter);
            if(filter){
                filter->setEdgeStrength(curValue);
            }
        }
            break;

        case FILTER_RGB_CLOSING:
            break;
        case FILTER_RGB_DILATION:
            break;
        case FILTER_RGB_EROSION:
            break;
        case FILTER_RGB:
        {
            GPUImageRGBFilter* filter = dynamic_cast<GPUImageRGBFilter*>(m_pFilter);
            if(filter){
                filter->setGreen(curValue);
            }
        }

            break;
        case FILTER_RGB_OPENING:
            break;

        case FILTER_SATURATION_BLEND:
            break;
        case FILTER_SATURATION:
        {
            GPUImageSaturationFilter* filter = dynamic_cast<GPUImageSaturationFilter*>(m_pFilter);
            if(filter){
                filter->setSaturation(curValue);
            }
        }
            break;
        case FILTER_SCREEN_BLEND:
            break;
        case FILTER_SEPIA:
        {
            GPUImageSepiaFilter* filter = dynamic_cast<GPUImageSepiaFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;
        case FILTER_SHARPEN:
        {
            GPUImageSharpenFilter* filter = dynamic_cast<GPUImageSharpenFilter*>(m_pFilter);
            if(filter){
                filter->setSharpness(curValue);
            }
        }
            break;
        case FILTER_SINGLE_COMPONENT_GAUSSIAN_BLUR:
        {
            GPUImageSingleComponentGaussianBlurFilter* filter = dynamic_cast<GPUImageSingleComponentGaussianBlurFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadiusInPixels(curValue);
            }
        }
            break;
        case FILTER_SKETCH:
        {
            GPUImageSketchFilter* filter = dynamic_cast<GPUImageSketchFilter*>(m_pFilter);
            if(filter){
                filter->setEdgeStrength(curValue);
            }
        }
            break;
        case FILTER_SKIN_TONE:
            // dont known how to set
            break;
        case FILTER_SMOOTH_TOON:
        {
            GPUImageSmoothToonFilter* filter = dynamic_cast<GPUImageSmoothToonFilter*>(m_pFilter);
            if(filter){
                filter->setBlurRadiusInPixels(curValue);
            }
        }
            break;
        case FILTER_SOBEL_EDGE_DETECTION:
        {
            GPUImageSobelEdgeDetectionFilter* filter = dynamic_cast<GPUImageSobelEdgeDetectionFilter*>(m_pFilter);
            if(filter){
                filter->setEdgeStrength(curValue);
            }
        }
            break;
        case FILTER_SOFT_ELEGANCE:
        {
            GPUImageSoftEleganceFilter* filter = dynamic_cast<GPUImageSoftEleganceFilter*>(m_pFilter);
            if(filter){
                filter->setLookUpIntensity(curValue);
            }
        }
            break;
        case FILTER_SOFT_LIGHT_BLEND:
            break;
        case FILTER_SOURCE_OVER_BLEND:
            break;
        case FILTER_SPHERE_REFRACTION:
        {
            GPUImageSphereRefractionFilter* filter = dynamic_cast<GPUImageSphereRefractionFilter*>(m_pFilter);
            if(filter){
                filter->setRadius(curValue);
            }
        }

            break;
        case FILTER_STRETCH_DISTORTION:
            break;
        case FILTER_SUBTRACT_BLEND:
            break;
        case FILTER_SWIRL:
        {
            GPUImageSwirlFilter* filter = dynamic_cast<GPUImageSwirlFilter*>(m_pFilter);
            if(filter){
                filter->setAngle(curValue);
            }
        }
            break;

        case FILTER_THRESHOLD_EDGE_DETECTION:
        {
            GPUImageThresholdEdgeDetectionFilter* filter = dynamic_cast<GPUImageThresholdEdgeDetectionFilter*>(m_pFilter);
            if(filter){
                filter->setThreshold(curValue);
            }
        }
            break;
        case FILTER_THRESHOLDED_NON_MAXIMUM_SUPPRESSION:
        {
            GPUImageThresholdedNonMaximumSuppressionFilter* filter = dynamic_cast<GPUImageThresholdedNonMaximumSuppressionFilter*>(m_pFilter);
            if(filter){
                filter->setThreshold(curValue);
            }
        }
            break;
        case FILTER_THRESHOLD_SKETCH:
        {
            GPUImageThresholdSketchFilter* filter = dynamic_cast<GPUImageThresholdSketchFilter*>(m_pFilter);
            if(filter){
                filter->setThreshold(curValue);
            }
        }
            break;
        case FILTER_TILT_SHIFT:
        {
            GPUImageTiltShiftFilter* filter = dynamic_cast<GPUImageTiltShiftFilter*>(m_pFilter);
            if(filter){
                filter->setTopFocusLevel(curValue - 0.1);
                filter->setBottomFocusLevel(curValue + 0.1);
            }
        }
            break;
        case FILTER_TONE_CURVE:
        {
            GPUImageToneCurveFilter* filter = dynamic_cast<GPUImageToneCurveFilter*>(m_pFilter);
            if(filter){
                CurvePointArray points;
                points.push_back(GLPoint(0.0f, 0.0f));
                points.push_back(GLPoint(0.5f, curValue));
                points.push_back(GLPoint(1.0f, 0.75f));
                filter->setBlueControlPoints(points);
            }
        }
            break;
        case FILTER_TOON:
            break;
        case FILTER_TRANSFORM:
        {
            GPUImageTransformFilter* filter = dynamic_cast<GPUImageTransformFilter*>(m_pFilter);
            if(filter){
                filter->setScale(curValue);
            }
        }
            break;

        case FILTER_UNSHARP_MASK:
        {
            GPUImageUnsharpMaskFilter* filter = dynamic_cast<GPUImageUnsharpMaskFilter*>(m_pFilter);
            if(filter){
                filter->setIntensity(curValue);
            }
        }
            break;

        case FILTER_VIBRANCE:
        {
            GPUImageVibranceFilter* filter = dynamic_cast<GPUImageVibranceFilter*>(m_pFilter);
            if(filter){
                filter->setVibrance(curValue);
            }
        }
            break;
        case FILTER_VIGNETTE:
        {
            GPUImageVignetteFilter* filter = dynamic_cast<GPUImageVignetteFilter*>(m_pFilter);
            if(filter){
                filter->setVignetteEnd(curValue);
            }
        }
            break;
        case FILTER_VORONOI_CONSUMER:
            break;

        case FILTER_WEAK_PIXEL_INCLUSION:
            break;
        case FILTER_WHITE_BALANCE:
        {
            GPUImageWhiteBalanceFilter* filter = dynamic_cast<GPUImageWhiteBalanceFilter*>(m_pFilter);
            if(filter){
                filter->setTemperature(curValue);
            }
        }
            break;

        case FILTER_XY_DERIVATIVE:
            break;
        case FILTER_ZOOM:
        {
            GPUImageZoomBlurFilter* filter = dynamic_cast<GPUImageZoomBlurFilter*>(m_pFilter);
            if(filter){
                filter->setBlurSize(curValue);
            }
        }
            break;

        default:
            break;
    }

    return true;
}


void NativeRender::stop() {
    if(m_pFilter){
        delete m_pFilter;
        m_pFilter = NULL;
    }
}

