/**
 * Created by lvHiei on 17-5-8.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEFILTERGROUP_H
#define CGPUIMAGE_ANDROID_GPUIMAGEFILTERGROUP_H

#include <vector>
#include "GPUImageFilter.h"

typedef std::vector<GPUImageFilter* > FilterArray;

class GPUImageFilterGroup : public GPUImageFilter{
public:
    GPUImageFilterGroup();
    virtual ~GPUImageFilterGroup();

public:
    void addFilter(GPUImageFilter* filter);
    void clear();

    GPUImageFilter* getFilter(int idx);

    virtual bool createProgram();
    virtual void setVertexCoordinate(float *vertexCoordinate);
    virtual void setTextureCoordinate(float *textureCoordinate);
    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);
    virtual bool release();
    virtual void setTextureRotation(Rotation rotation);
    virtual void setTextureSize(int width, int height);


protected:
    bool createFrameBuffer();
    void deleteFrameBuffer();

protected:
    FilterArray m_vFilters;
    uint32_t m_uFilterCnt;

protected:
    GLuint* m_pFrameBuffers;
    GLuint* m_pFrameBufferTextures;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEFILTERGROUP_H
