/**
 * Created by lvHiei on 17-4-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTFILTER_H


#include "GPUImageFilter.h"

class GPUImageTwoInputFilter : public GPUImageFilter{
public:
    GPUImageTwoInputFilter(const char* fragment);
    virtual ~GPUImageTwoInputFilter();

    virtual bool release();

protected:
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    virtual bool loadImage();

protected:
    char* m_pFragmentShader;

protected:
    GLuint m_uImageTextureId;
    GLint m_iImageTextureIdLocation;
    GLint m_iImageTextureIdCoordinateLocation;

protected:
    uint8_t *m_pPicDataRGBA;
    uint32_t m_uPicWidth;
    uint32_t m_uPicHeight;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTFILTER_H
