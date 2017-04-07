/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECHROMAKEYFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECHROMAKEYFILTER_H


#include "GPUImageFilter.h"

class GPUImageChromaKeyFilter : public GPUImageFilter{
public:
    GPUImageChromaKeyFilter();
    virtual ~GPUImageChromaKeyFilter();


    void setThresholdSensitivity(int percent);
    void setThresholdSensitivity(float thresholdSensitivity);
    void setSmoothing(float smoothing);
    void setColorToReplace(float red, float green, float blue);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** The threshold sensitivity controls how similar pixels need to be colored to be replaced

        The default value is 0.3
     */
    GLfloat m_fThresholdSensitivity;

    /** The degree of smoothing controls how gradually similar colors are replaced in the image

        The default value is 0.1
     */
    GLfloat m_fSmoothing;

    /** The color to be replaced is specified using individual red, green, and blue components (normalized to 1.0).

        The default is green: (0.0, 1.0, 0.0).
     */
    GLfloat m_pColorToReplace[3];

    GLint m_iThresholdSensitivityUniformLocation;
    GLint m_iSmoothingUniformLocation;
    GLint m_iColorToReplaceUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECHROMAKEYFILTER_H
