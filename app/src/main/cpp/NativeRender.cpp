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
    switch (filterType){
        case FILTER_3X3_CONVOLUTION:
            m_pFilter = new GPUImage3x3ConvolutionFilter();
            break;

        case FILTER_ADAPTIVE_THRESHOLD:
            m_pFilter = new GPUImageAdaptiveThresholdFilter();
            break;
        case FILTER_ADD_BLEND:
            m_pFilter = new GPUImageAddBlendFilter();
            break;
        case FILTER_ALPHA_BLEND:
            m_pFilter = new GPUImageAlphaBlendFilter();
            break;
        case FILTER_AMATORKA:
            m_pFilter = new GPUImageAmatorkaFilter();
            break;

        case FILTER_BILATERAL:
            m_pFilter = new GPUImageBilateralFilter();
            break;
        case FILTER_BOXBLUR:
            m_pFilter = new GPUImageBoxBlurFilter();
            break;
        case FILTER_BRIGHTNESS:
            m_pFilter = new GPUImageBrightnessFilter();
            break;
        case FILTER_BULGE_DISTORTION:
            m_pFilter = new GPUImageBulgeDistortionFilter();
            break;

        case FILTER_CANNY_EDGE_DETECTION:
            m_pFilter = new GPUImageCannyEdgeDetectionFilter();
            break;
        case FILTER_CGA_COLORSPACE:
            m_pFilter = new GPUImageCGAColorspaceFilter();
            break;
        case FILTER_CHROMAKEY_BLEND:
            m_pFilter = new GPUImageChromaKeyBlendFilter();
            break;
        case FILTER_CHROMAKEY:
            m_pFilter = new GPUImageChromaKeyFilter();
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
            break;
        case FILTER_CROP:
            m_pFilter = new GPUImageCropFilter();
            break;
        case FILTER_CROSSHATCH:
            m_pFilter = new GPUImageCrosshatchFilter();
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
            break;
        case FILTER_DIRECTIONAL_SOBEL_EDGE_DETECTION:
            m_pFilter = new GPUImageDirectionalSobelEdgeDetectionFilter();
            break;
        case FILTER_DISSOLVE_BLEND:
            m_pFilter = new GPUImageDissolveBlendFilter();
            break;
        case FILTER_DIVIDE_BLEND:
            m_pFilter = new GPUImageDivideBlendFilter();
            break;

        case FILTER_EMBOSS:
            m_pFilter = new GPUImageEmbossFilter();
            break;
        case FILTER_EROSION:
            m_pFilter = new GPUImageErosionFilter();
            break;
        case FILTER_EXCLUSION_BLEND:
            m_pFilter = new GPUImageExclusionBlendFilter();
            break;
        case FILTER_EXPOSURE:
            m_pFilter = new GPUImageExposureFilter();
            break;

        case FILTER_FALSE_COLOR:
            m_pFilter = new GPUImageFalseColorFilter();
            break;

        case FILTER_GAMMA:
            m_pFilter = new GPUImageGammaFilter();
            break;
        case FILTER_GAUSSIAN_BLUR:
            m_pFilter = new GPUImageGaussianBlurFilter();
            break;
        case FILTER_GAUSSIAN_BLUR_POSITION:
            m_pFilter = new GPUImageGaussianBlurPositionFilter();
            break;
        case FILTER_GAUSSIAN_SELECTIVE_BLUR:
            m_pFilter = new GPUImageGaussianSelectiveBlurFilter();
            break;
        case FILTER_GLASS_SPHERE:
            m_pFilter = new GPUImageGlassSphereFilter();
            break;
        case FILTER_GREYSCALE:
            m_pFilter = new GPUImageGreyscaleFilter();
            break;

        case FILTER_HALFTONE:
            m_pFilter = new GPUImageHalftoneFilter();
            break;
        case FILTER_HARD_LIGHT_BLEND:
            m_pFilter = new GPUImageHardLightBlendFilter();
            break;
        case FILTER_HAZE:
            m_pFilter = new GPUImageHazeFilter();
            break;
        case FILTER_HIGHLIGHT_SHADOW:
            m_pFilter = new GPUImageHighlightShadowFilter();
            break;
        case FILTER_HIGHLIGHT_SHADOW_TINT:
            m_pFilter = new GPUImageHighlightShadowTintFilter();
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
            break;
        case FILTER_LIGHTEN_BLEND:
            m_pFilter = new GPUImageLightenBlendFilter();
            break;
        case FILTER_LINEAR_BURN_BLEND:
            m_pFilter = new GPUImageLinearBurnBlendFilter();
            break;
        case FILTER_LOCAL_BINARY_PATTERN:
            m_pFilter = new GPUImageLocalBinaryPatternFilter();
            break;
        case FILTER_LUMINANCE_RANGE:
            m_pFilter = new GPUImageLuminanceRangeFilter();
            break;
        case FILTER_LUMINANCE_THRESHOLD:
            m_pFilter = new GPUImageLuminanceThresholdFilter();
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
            break;
        case FILTER_MONOCHROME:
            m_pFilter = new GPUImageMonochromeFilter();
            break;
        case FILTER_MOSAIC:
            m_pFilter = new GPUImageMosaicFilter();
            break;
        case FILTER_MOTION_BLUR:
            m_pFilter = new GPUImageMotionBlurFilter();
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
            break;
        case FILTER_OPENING:
            m_pFilter = new GPUImageOpeningFilter();
            break;
        case FILTER_OVERLAY_BLEND:
            m_pFilter = new GPUImageOverlayBlendFilter();
            break;

        case FILTER_PERLIN_NOISE:
            m_pFilter = new GPUImagePerlinNoiseFilter();
            break;
        case FILTER_PINCH_DISTORTION:
            m_pFilter = new GPUImagePinchDistortionFilter();
            break;
        case FILTER_PIXELLATE:
            m_pFilter = new GPUImagePixellateFilter();
            break;
        case FILTER_PIXELLATE_POSITION:
            m_pFilter = new GPUImagePixellatePositionFilter();
            break;
        case FILTER_POISSON_BLEND:
            m_pFilter = new GPUImagePoissonBlendFilter();
            break;
        case FILTER_POLAR_PIXELLATE:
            m_pFilter = new GPUImagePolarPixellateFilter();
            break;
        case FILTER_POLKA_DOT:
            m_pFilter = new GPUImagePolkaDotFilter();
            break;
        case FILTER_POSTERIZE:
            m_pFilter = new GPUImagePosterizeFilter();
            break;
        case FILTER_PREWITT_EDGE_DETECTION:
            m_pFilter = new GPUImagePrewittEdgeDetectionFilter();
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
            break;
        case FILTER_RGB_OPENING:
            m_pFilter = new GPUImageRGBOpeningFilter();
            break;

        case FILTER_SATURATION_BLEND:
            m_pFilter = new GPUImageSaturationBlendFilter();
            break;
        case FILTER_SATURATION:
            m_pFilter = new GPUImageSaturationFilter();
            break;
        case FILTER_SCREEN_BLEND:
            m_pFilter = new GPUImageScreenBlendFilter();
            break;
        case FILTER_SEPIA:
            m_pFilter = new GPUImageSepiaFilter();
            break;
        case FILTER_SHARPEN:
            m_pFilter = new GPUImageSharpenFilter();
            break;
        case FILTER_SINGLE_COMPONENT_GAUSSIAN_BLUR:
            m_pFilter = new GPUImageSingleComponentGaussianBlurFilter();
            break;
        case FILTER_SKETCH:
            m_pFilter = new GPUImageSketchFilter();
            break;
        case FILTER_SKIN_TONE:
            m_pFilter = new GPUImageSkinToneFilter();
            break;
        case FILTER_SMOOTH_TOON:
            m_pFilter = new GPUImageSmoothToonFilter();
            break;
        case FILTER_SOBEL_EDGE_DETECTION:
            m_pFilter = new GPUImageSobelEdgeDetectionFilter();
            break;
        case FILTER_SOFT_ELEGANCE:
            m_pFilter = new GPUImageSoftEleganceFilter();
            break;
        case FILTER_SOFT_LIGHT_BLEND:
            m_pFilter = new GPUImageSoftLightBlendFilter();
            break;
        case FILTER_SOURCE_OVER_BLEND:
            m_pFilter = new GPUImageSourceOverBlendFilter();
            break;
        case FILTER_SPHERE_REFRACTION:
            m_pFilter = new GPUImageSphereRefractionFilter();
            break;
        case FILTER_STRETCH_DISTORTION:
            m_pFilter = new GPUImageStretchDistortionFilter();
            break;
        case FILTER_SUBTRACT_BLEND:
            m_pFilter = new GPUImageSubtractBlendFilter();
            break;
        case FILTER_SWIRL:
            m_pFilter = new GPUImageSwirlFilter();
            break;

        case FILTER_THRESHOLD_EDGE_DETECTION:
            m_pFilter = new GPUImageThresholdEdgeDetectionFilter();
            break;
        case FILTER_THRESHOLDED_NON_MAXIMUM_SUPPRESSION:
            m_pFilter = new GPUImageThresholdedNonMaximumSuppressionFilter();
            break;
        case FILTER_THRESHOLD_SKETCH:
            m_pFilter = new GPUImageThresholdSketchFilter();
            break;
        case FILTER_TILT_SHIFT:
            m_pFilter = new GPUImageTiltShiftFilter();
            break;
        case FILTER_TONE_CURVE:
            m_pFilter = new GPUImageToneCurveFilter();
            break;
        case FILTER_TOON:
            m_pFilter = new GPUImageToonFilter();
            break;

        case FILTER_UNSHARP_MASK:
            m_pFilter = new GPUImagePureUnsharpMaskFilter();
            break;

        case FILTER_VIBRANCE:
            m_pFilter = new GPUImageVibranceFilter();
            break;
        case FILTER_VIGNETTE:
            m_pFilter = new GPUImageVignetteFilter();
            break;
        case FILTER_VORONOI_CONSUMER:
            m_pFilter = new GPUImageVoronoiConsumerFilter();
            break;

        case FILTER_WEAK_PIXEL_INCLUSION:
            m_pFilter = new GPUImageWeakPixelInclusionFilter();
            break;
        case FILTER_WHITE_BALANCE:
            m_pFilter = new GPUImageWhiteBalanceFilter();
            break;

        case FILTER_XY_DERIVATIVE:
            m_pFilter = new GPUImageXYDerivativeFilter();
            break;
        case FILTER_ZOOM:
            m_pFilter = new GPUImageZoomBlurFilter();
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

    GPUImageCropFilter* filter = dynamic_cast<GPUImageCropFilter*>(m_pFilter);
    if(NULL != filter){
        filter->setCropRegion(GLRect(0.0, 0.0, 1.0, 1.0*percent/100));
    }

    float max = 0.8;
    float min = 0.2;

    float current = 0.2 + (0.8-0.2)*percent/100;

    GPUImageTiltShiftFilter* filter1 = dynamic_cast<GPUImageTiltShiftFilter*>(m_pFilter);
    if(NULL != filter1){
        filter1->setTopFocusLevel(current + 0.1);
        filter1->setBottomFocusLevel(current - 0.1);
    }

    return true;
}


void NativeRender::stop() {
    if(m_pFilter){
        delete m_pFilter;
        m_pFilter = NULL;
    }
}

