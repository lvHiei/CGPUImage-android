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
    GPUImageTwoInputFilter(const char* vertex, const char* fragment);
    virtual ~GPUImageTwoInputFilter();

    virtual bool release();

    virtual void setTexture2Id(GLuint texture2Id);
    virtual void setTexture2Coordinate(float *textureCoordinate);
    virtual void setTexture2Rotation(Rotation rotation);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    GLuint m_uTexture2Id;
    GLint m_iTexture2IdLocation;
    GLint m_iTexture2IdCoordinateLocation;

    GLfloat* m_pTexture2Coordinate;

    Rotation m_eTexture2Rotation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETWOINPUTFILTER_H
