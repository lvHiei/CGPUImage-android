/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDNONMAXIMUMSUPPRESSIONFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDNONMAXIMUMSUPPRESSIONFILTER_H


#include "GPUImage3x3TextureSamplingFilter.h"

class GPUImageThresholdedNonMaximumSuppressionFilter : public GPUImage3x3TextureSamplingFilter{
public:
    GPUImageThresholdedNonMaximumSuppressionFilter();
    virtual ~GPUImageThresholdedNonMaximumSuppressionFilter();

public:
    void setThreshold(int percent);
    void setThreshold(float threshold);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    /** Any local maximum above this threshold will be white,
     * and anything below black. Ranges from 0.0 to 1.0, with 0.8 as the default
     */
    GLfloat m_fThreshold;

    GLint m_iThresholdUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETHRESHOLDEDNONMAXIMUMSUPPRESSIONFILTER_H
