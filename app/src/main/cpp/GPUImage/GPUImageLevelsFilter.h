/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGELEVELSFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGELEVELSFILTER_H


#include "GPUImageFilter.h"

/**
 * Levels like Photoshop.
 *
 * The min, max, minOut and maxOut parameters are floats in the range [0, 1].
 * If you have parameters from Photoshop in the range [0, 255] you must first
 * convert them to be [0, 1].
 * The gamma/mid parameter is a float >= 0. This matches the value from Photoshop.
 *
 * If you want to apply levels to RGB as well as individual channels you need to use
 * this filter twice - first for the individual channels and then for all channels.
 */

class GPUImageLevelsFilter : public GPUImageFilter{
public:
    GPUImageLevelsFilter();
    virtual ~GPUImageLevelsFilter();

    /** Set levels for the red channel */
    void setRedMin(float min, float mid, float max, float minOut, float maxOut);
    void setRedMin(float min, float mid, float max);

    /** Set levels for the green channel */
    void setGreenMin(float min, float mid, float max, float minOut, float maxOut);
    void setGreenMin(float min, float mid, float max);


    /** Set levels for the green channel */
    void setBlueMin(float min, float mid, float max, float minOut, float maxOut);
    void setBlueMin(float min, float mid, float max);


    /** Set levels for all channels at once */
    void setMin(float min, float mid, float max, float minOut, float maxOut);
    void setMin(float min, float mid, float max);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLfloat m_pMinVector[3];
    GLfloat m_pMidVector[3];
    GLfloat m_pMaxVector[3];
    GLfloat m_pMinOutputVector[3];
    GLfloat m_pMaxOutputVector[3];

    GLint m_iMinVectorUniformLocation;
    GLint m_iMidVectorUniformLocation;
    GLint m_iMaxVectorUniformLocation;
    GLint m_iMinOutputVectorUniformLocation;
    GLint m_iMaxOutputVectorUniformLocation;

};


#endif //CGPUIMAGE_ANDROID_GPUIMAGELEVELSFILTER_H
