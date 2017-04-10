/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEHAZEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEHAZEFILTER_H


#include "GPUImageFilter.h"

/*
 * The haze filter can be used to add or remove haze (similar to a UV filter)
 *
 * @author Alaric Cole
 * @creationDate 03/10/12
 *
 */


/** The haze filter can be used to add or remove haze

 This is similar to a UV filter
 */
class GPUImageHazeFilter : public GPUImageFilter{
public:
    GPUImageHazeFilter();
    virtual ~GPUImageHazeFilter();

    void setDistance(float distance);
    void setSlope(float slope);

    void setDistance(int percent);
    void setSlope(int percent);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:

    /** Strength of the color applied. Default 0. Values between -.3 and .3 are best
    */
    GLfloat m_fDistance;

    /** Amount of color change. Default 0. Values between -.3 and .3 are best
    */
    GLfloat m_fSlope;

    GLint m_iDistanceUniformLocation;
    GLint m_iSlopeUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEHAZEFILTER_H
