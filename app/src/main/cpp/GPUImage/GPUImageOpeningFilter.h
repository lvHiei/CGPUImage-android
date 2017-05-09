/**
 * Created by mj on 17-5-9.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEOPENINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEOPENINGFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageErosionFilter.h"
#include "GPUImageDilationFilter.h"

// A filter that first performs an erosion on the red channel of an image, followed by a dilation of the same radius.
// This helps to filter out smaller bright elements

class GPUImageOpeningFilter : public GPUImageFilterGroup{
public:
    GPUImageOpeningFilter();
    GPUImageOpeningFilter(int radius);
    virtual ~GPUImageOpeningFilter();


    void setHorizontalTexelSpacing(GLfloat horizontalTexelSpacing);
    void setVerticalTexelSpacing(GLfloat verticalTexelSpacing);

    virtual bool release();

protected:
    void initWithRadius(int radius);

protected:
    GPUImageErosionFilter* m_pErosionFilter;
    GPUImageDilationFilter* m_pDilationFilter;

protected:
    GLfloat m_fVerticalTexelSpacing;
    GLfloat m_fHorizontalTexelSpacing;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEOPENINGFILTER_H
