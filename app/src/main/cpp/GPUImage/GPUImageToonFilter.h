/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETOONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETOONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

/** This uses Sobel edge detection to place a black border around objects,
 and then it quantizes the colors present in the image to give a cartoon-like quality to the image.
 */

class GPUImageToonFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageToonFilter();
    virtual ~GPUImageToonFilter();

    void setThreshold(int percent);
    void setThreshold(float threshold);
    void setQuantizationLevels(float quantizationLevels);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    /** The threshold at which to apply the edges, default of 0.2
     */
    GLfloat m_fThreshold;

    /** The levels of quantization for the posterization of colors within the scene, with a default of 10.0
     */
    GLfloat m_fQuantizationLevels;

    GLint m_iThresholdUniformLocation;
    GLint m_iQuantizationLevelsUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETOONFILTER_H
