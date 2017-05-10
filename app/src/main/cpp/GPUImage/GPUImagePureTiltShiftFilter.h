/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEPURETILTSHIFTFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEPURETILTSHIFTFILTER_H


#include "GPUImageTwoInputFilter.h"

class GPUImagePureTiltShiftFilter : public GPUImageTwoInputFilter{
public:
    GPUImagePureTiltShiftFilter();
    virtual ~GPUImagePureTiltShiftFilter();

    void setTopFocusLevel(float newValue);
    void setBottomFocusLevel(float newValue);
    void setFocusFallOffRate(float newValue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /// The normalized location of the top of the in-focus area in the image, this value should be lower than bottomFocusLevel, default 0.4
    GLfloat m_fTopFocusLevel;

    /// The normalized location of the bottom of the in-focus area in the image, this value should be higher than topFocusLevel, default 0.6
    GLfloat m_fBottomFocusLevel;

    /// The rate at which the image gets blurry away from the in-focus region, default 0.2
    GLfloat m_fFocusFallOffRate;

    GLint m_iTopFocusLevelUniformLocation;
    GLint m_iBottomFocusLevelUniformLocation;
    GLint m_iFocusFallOffRateUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEPURETILTSHIFTFILTER_H
