/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECANNYEDGEDETECTIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECANNYEDGEDETECTIONFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageGreyscaleFilter.h"
#include "GPUImageSingleComponentGaussianBlurFilter.h"
#include "GPUImageDirectionalSobelEdgeDetectionFilter.h"
#include "GPUImageDirectionalNonMaximumSuppressionFilter.h"
#include "GPUImageWeakPixelInclusionFilter.h"

/** This applies the edge detection process described by John Canny in

 Canny, J., A Computational Approach To Edge Detection, IEEE Trans. Pattern Analysis and Machine Intelligence, 8(6):679–698, 1986.

 and implemented in OpenGL ES by

 A. Ensor, S. Hall. GPU-based Image Analysis on Mobile Devices. Proceedings of Image and Vision Computing New Zealand 2011.

 It starts with a conversion to luminance, followed by an accelerated 9-hit Gaussian blur. A Sobel operator is applied to obtain the overall
 gradient strength in the blurred image, as well as the direction (in texture sampling steps) of the gradient. A non-maximum suppression filter
 acts along the direction of the gradient, highlighting strong edges that pass the threshold and completely removing those that fail the lower
 threshold. Finally, pixels from in-between these thresholds are either included in edges or rejected based on neighboring pixels.
 */

class GPUImageCannyEdgeDetectionFilter : public GPUImageFilterGroup{
public:
    GPUImageCannyEdgeDetectionFilter();
    virtual ~GPUImageCannyEdgeDetectionFilter();


public:
    void setTexelWidth(GLfloat texelWidth);
    void setTexelHeight(GLfloat texelHeight);
    void setBlurRadiusInPixels(GLfloat blurRadiusInPixels);
    void setBlurTexelSpacingMultiplier(GLfloat blurTexelSpacingMultiplier);
    void setUpperThreshold(GLfloat upperThreshold);
    void setLowerThreshold(GLfloat lowerThreshold);

    virtual bool release();

protected:
    GPUImageGreyscaleFilter* m_pLuminanceFilter;
    GPUImageSingleComponentGaussianBlurFilter* m_pBlurFilter;
    GPUImageDirectionalSobelEdgeDetectionFilter* m_pEdgeDetectionFilter;
    GPUImageDirectionalNonMaximumSuppressionFilter* m_pNonMaximumSuppressionFilter;
    GPUImageWeakPixelInclusionFilter* m_pWeakPixelInclusionFilter;

protected:
    /** The image width and height factors tweak the appearance of the edges.
        These parameters affect the visibility of the detected edges
        By default, they match the inverse of the filter size in pixels
    */
    GLfloat m_fTexelWidth;

    /** The image width and height factors tweak the appearance of the edges.
        These parameters affect the visibility of the detected edges
        By default, they match the inverse of the filter size in pixels
    */
    GLfloat m_fTexelHeight;

    /** The underlying blur radius for the Gaussian blur. Default is 2.0.
    */
    GLfloat m_fBlurRadiusInPixels;

    /** The underlying blur texel spacing multiplier. Default is 1.0.
    */
    GLfloat m_fBlurTexelSpacingMultiplier;

    /** Any edge with a gradient magnitude above this threshold will pass and show up in the final result.
    */
    GLfloat m_fUpperThreshold;

    /** Any edge with a gradient magnitude below this threshold will fail and be removed from the final result.
    */
    GLfloat m_fLowerThreshold;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECANNYEDGEDETECTIONFILTER_H
