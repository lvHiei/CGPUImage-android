/**
 * Created by mj on 17-5-9.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECLOSINGFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECLOSINGFILTER_H


#include "GPUImageFilterGroup.h"
#include "GPUImageErosionFilter.h"
#include "GPUImageDilationFilter.h"

// A filter that first performs a dilation on the red channel of an image, followed by an erosion of the same radius.
// This helps to filter out smaller dark elements.

class GPUImageClosingFilter : public GPUImageFilterGroup{
public:
    GPUImageClosingFilter();
    GPUImageClosingFilter(int radius);
    virtual ~GPUImageClosingFilter();

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


#endif //CGPUIMAGE_ANDROID_GPUIMAGECLOSINGFILTER_H
