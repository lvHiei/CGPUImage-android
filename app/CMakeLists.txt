# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_definitions(-D__ANDROID__GPUIMAGE__)
add_definitions(-D__GLSL_SUPPORT_HIGHP__)

add_library( # Sets the name of the library.
             cgpuimage

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp
             src/main/cpp/NativeRender.cpp
             src/main/cpp/util/TextureRotateUtil.cpp
             src/main/cpp/util/FileUtil.cpp
             src/main/cpp/GPUImage/GPUImageFilter.cpp
             src/main/cpp/GPUImage/GPUImageGreyscaleFilter.cpp
             src/main/cpp/GPUImage/GPUImageContrastFilter.cpp
             src/main/cpp/GPUImage/GPUImageSaturationFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorMatrixFilter.cpp
             src/main/cpp/GPUImage/GPUImageSepiaFilter.cpp
             src/main/cpp/GPUImage/GPUImageTwoInputFilter.cpp
             src/main/cpp/GPUImage/GPUImageLookupFilter.cpp
             src/main/cpp/GPUImage/GPUImageAmatorkaFilter.cpp
             src/main/cpp/GPUImage/GPUImageMissEtikateFilter.cpp
             src/main/cpp/GPUImage/GPUImageGammaFilter.cpp
             src/main/cpp/GPUImage/GPUImage3x3TextureSamplingFilter.cpp
             src/main/cpp/GPUImage/GPUImage3x3ConvolutionFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorLocalBinaryPatternFilter.cpp
             src/main/cpp/GPUImage/GPUImageDirectionalSobelEdgeDetectionFilter.cpp
             src/main/cpp/GPUImage/GPUImageLocalBinaryPatternFilter.cpp
             src/main/cpp/GPUImage/GPUImageMedianFilter.cpp
             src/main/cpp/GPUImage/GPUImageNonMaximumSuppressionFilter.cpp
             src/main/cpp/GPUImage/GPUImageThresholdedNonMaximumSuppressionFilter.cpp
             src/main/cpp/GPUImage/GPUImageToonFilter.cpp
             src/main/cpp/GPUImage/GPUImageWeakPixelInclusionFilter.cpp
             src/main/cpp/GPUImage/GPUImageAddBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageImageFilter.cpp
             src/main/cpp/GPUImage/GPUImageAlphaBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageBrightnessFilter.cpp
             src/main/cpp/GPUImage/GPUImageBulgeDistortionFilter.cpp
             src/main/cpp/GPUImage/GPUImageCGAColorspaceFilter.cpp
             src/main/cpp/GPUImage/GPUImageChromaKeyBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageChromaKeyFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorBurnBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorDodgeBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorInvertFilter.cpp
             src/main/cpp/GPUImage/GPUImageColorPackingFilter.cpp
             src/main/cpp/GPUImage/GPUImageColourFASTSamplingOperation.cpp
             src/main/cpp/GPUImage/GPUImageCrosshatchFilter.cpp
             src/main/cpp/GPUImage/GPUImageDarkenBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageDifferenceBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageDirectionalNonMaximumSuppressionFilter.cpp
             src/main/cpp/GPUImage/GPUImageDissolveBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageDivideBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageEmbossFilter.cpp
             src/main/cpp/GPUImage/GPUImageExclusionBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageExposureFilter.cpp
             src/main/cpp/GPUImage/GPUImageFalseColorFilter.cpp
             src/main/cpp/GPUImage/GPUImageHardLightBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageHazeFilter.cpp
             src/main/cpp/GPUImage/GPUImageHighlightShadowFilter.cpp
             src/main/cpp/GPUImage/GPUImageHighlightShadowTintFilter.cpp
             src/main/cpp/GPUImage/GPUImageHSBFilter.cpp
             src/main/cpp/GPUImage/GPUImageHueBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageHueFilter.cpp
             src/main/cpp/GPUImage/GPUImageKuwaharaFilter.cpp
             src/main/cpp/GPUImage/GPUImageKuwaharaRadius3Filter.cpp
             src/main/cpp/GPUImage/GPUImageLaplacianFilter.cpp
             src/main/cpp/GPUImage/GPUImageLevelsFilter.cpp
             src/main/cpp/GPUImage/GPUImageLightenBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageLinearBurnBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageLuminanceRangeFilter.cpp
             src/main/cpp/GPUImage/GPUImageLuminanceThresholdFilter.cpp
             src/main/cpp/GPUImage/GPUImageLuminosityBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageMaskFilter.cpp
             src/main/cpp/GPUImage/GPUImageMonochromeFilter.cpp
             src/main/cpp/GPUImage/GPUImageMosaicFilter.cpp
             src/main/cpp/GPUImage/GPUImageMotionBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageMultiplyBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageNormalBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageOpacityFilter.cpp
             src/main/cpp/GPUImage/GPUImageOverlayBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImagePerlinNoiseFilter.cpp
             src/main/cpp/GPUImage/GPUImagePinchDistortionFilter.cpp
             src/main/cpp/GPUImage/GPUImagePixellateFilter.cpp
             src/main/cpp/GPUImage/GPUImagePixellatePositionFilter.cpp
             src/main/cpp/GPUImage/GPUImagePolarPixellateFilter.cpp
             src/main/cpp/GPUImage/GPUImagePolkaDotFilter.cpp
             src/main/cpp/GPUImage/GPUImagePosterizeFilter.cpp
             src/main/cpp/GPUImage/GPUImageRGBFilter.cpp
             src/main/cpp/GPUImage/GPUImageSaturationBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageScreenBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageSharpenFilter.cpp
             src/main/cpp/GPUImage/GPUImageSkinToneFilter.cpp
             src/main/cpp/GPUImage/GPUImageSoftLightBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageSourceOverBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageSubtractBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageSphereRefractionFilter.cpp
             src/main/cpp/GPUImage/GPUImageStretchDistortionFilter.cpp
             src/main/cpp/GPUImage/GPUImageSwirlFilter.cpp
             src/main/cpp/GPUImage/GPUImageVibranceFilter.cpp
             src/main/cpp/GPUImage/GPUImageVignetteFilter.cpp
             src/main/cpp/GPUImage/GPUImageWhiteBalanceFilter.cpp
             src/main/cpp/GPUImage/GPUImageZoomBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageTwoInputCrossTextureSamplingFilter.cpp
             src/main/cpp/GPUImage/GPUImagePoissonBlendFilter.cpp
             src/main/cpp/GPUImage/GPUImageTwoPassFilter.cpp
             src/main/cpp/GPUImage/GPUImageSobelEdgeDetectionFilter.cpp
             src/main/cpp/GPUImage/GPUImagePrewittEdgeDetectionFilter.cpp
             src/main/cpp/GPUImage/GPUImageThresholdEdgeDetectionFilter.cpp
             src/main/cpp/GPUImage/GPUImageSketchFilter.cpp
             src/main/cpp/GPUImage/GPUImageXYDerivativeFilter.cpp
             src/main/cpp/GPUImage/GPUImageThresholdSketchFilter.cpp
             src/main/cpp/GPUImage/GPUImageTwoPassTextureSamplingFilter.cpp
             src/main/cpp/GPUImage/GPUImageDilationFilter.cpp
             src/main/cpp/GPUImage/GPUImageRGBDilationFilter.cpp
             src/main/cpp/GPUImage/GPUImageErosionFilter.cpp
             src/main/cpp/GPUImage/GPUImageRGBErosionFilter.cpp
             src/main/cpp/GPUImage/GPUImageLanczosResamplingFilter.cpp
             src/main/cpp/GPUImage/GPUImageGaussianBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageGaussianBlurPositionFilter.cpp
             src/main/cpp/GPUImage/GPUImageBilateralFilter.cpp
             src/main/cpp/GPUImage/GPUImageBoxBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageSingleComponentGaussianBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageVoronoiConsumerFilter.cpp
             src/main/cpp/GPUImage/GPUImageGlassSphereFilter.cpp
             src/main/cpp/GPUImage/GPUImageJFAVoronoiFilter.cpp
             src/main/cpp/GPUImage/GPUImageToneCurveFilter.cpp
             src/main/cpp/GPUImage/GPUImageCropFilter.cpp
             src/main/cpp/GPUImage/GPUImageFilterGroup.cpp
             src/main/cpp/GPUImage/GPUImageAdaptiveThresholdFilter.cpp
             src/main/cpp/GPUImage/GPUImageCannyEdgeDetectionFilter.cpp
             src/main/cpp/GPUImage/GPUImageClosingFilter.cpp
             src/main/cpp/GPUImage/GPUImageOpeningFilter.cpp
             src/main/cpp/GPUImage/GPUImageRGBClosingFilter.cpp
             src/main/cpp/GPUImage/GPUImageRGBOpeningFilter.cpp
             src/main/cpp/GPUImage/GPUImageColourFASTFeatureDetector.cpp
             src/main/cpp/GPUImage/GPUImageGaussianSelectiveBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageSelectiveFocusFilter.cpp
             src/main/cpp/GPUImage/GPUImageHalftoneFilter.cpp
             src/main/cpp/GPUImage/GPUImageiOSBlurFilter.cpp
             src/main/cpp/GPUImage/GPUImageSmoothToonFilter.cpp
             src/main/cpp/GPUImage/GPUImageSoftEleganceFilter.cpp
             src/main/cpp/GPUImage/GPUImagePureTiltShiftFilter.cpp
             src/main/cpp/GPUImage/GPUImageTiltShiftFilter.cpp
             src/main/cpp/GPUImage/GPUImagePureUnsharpMaskFilter.cpp
             src/main/cpp/GPUImage/GPUImageUnsharpMaskFilter.cpp
             src/main/cpp/GPUImage/GPUImageTransformFilter.cpp
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       cgpuimage

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       GLESv2
                       EGL

                       )

target_include_directories(cgpuimage PUBLIC )