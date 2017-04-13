/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGESKINTONEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGESKINTONEFILTER_H


#include "GPUImageFilter.h"

class GPUImageSkinToneFilter : public GPUImageFilter{
public:
    GPUImageSkinToneFilter();
    virtual ~GPUImageSkinToneFilter();


    void setSkinToneAdjust(float skinToneAdjust);
    void setSkinHue(float skinHue);
    void setSkinHueShreshold(float skinHueThreshold);
    void setMaxHueShift(float maxHueShift);
    void setMaxSaturationShift(float maxSaturationShift);
    void setUpperSkinToneColor(int upperSkinToneColor);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();


protected:

    // The amount of effect to apply, between -1.0 (pink) and +1.0 (orange OR green). Default is 0.0.
    GLfloat m_fSkinToneAdjust;

    // The initial hue of skin to adjust. Default is 0.05 (a common skin red).
    GLfloat m_fSkinHue;

    // The bell curve "breadth" of the skin hue adjustment (i.e. how different from the original skinHue will the modifications effect).
    // Default is 40.0
    GLfloat m_fSkinHueThreshold;

    // The maximum amount of hue shift allowed in the adjustments that affect hue (pink, green). Default = 0.25.
    GLfloat m_fMaxHueShift;

    // The maximum amount of saturation shift allowed in the adjustments that affect saturation (orange). Default = 0.4.
    GLfloat m_fMaxSaturationShift;

    // Defines whether the upper range (> 0.0) will change the skin tone to green (hue) or orange (saturation)
    GLint m_iUpperSkinToneColor;


    GLint m_iSkinToneAdjustUniformLocation;
    GLint m_iSkinHueUniformLocation;
    GLint m_iSkinHueThresholdUniformLocation;
    GLint m_iMaxHueShiftUniformLocation;
    GLint m_iMaxSaturationShiftUniformLocation;
    GLint m_iUpperSkinToneColorUniformLocation;

};


#endif //CGPUIMAGE_ANDROID_GPUIMAGESKINTONEFILTER_H
