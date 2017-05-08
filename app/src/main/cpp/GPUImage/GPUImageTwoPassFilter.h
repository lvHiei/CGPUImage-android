/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETWOPASSFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETWOPASSFILTER_H


#include "GPUImageFilter.h"

/**
 * this can be replaced by groupFilter I think, but I don't conform
 * If someone known that the filter can be replaced by groupfiler, please
 * send me a email, my email is majun_1523@163.com.
 * thanks.
 *
 */
class GPUImageTwoPassFilter : public GPUImageFilter{
public:
    GPUImageTwoPassFilter(const char* firstVertex, const char* fisrtFragment, const char* secondVertex, const char* secondFragment);
    virtual ~GPUImageTwoPassFilter();

public:
    virtual bool createProgram();
    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);
    virtual bool release();

    virtual void setTextureCoordinate(float *textureCoordinate);

    virtual void resetShader(const char* firstVertex, const char* fisrtFragment, const char* secondVertex, const char* secondFragment);

protected:
    virtual bool firstCreateProgramExtra();
    virtual bool secondCreateProgramExtra();

    virtual bool firstBeforeDraw();
    virtual bool firstOnDraw();

    virtual bool secondBeforeDraw();
    virtual bool secondOnDraw();

protected:
    bool createFrameBuffer();


protected:
    GLuint m_uSecondProgram;
    GLuint m_uSecondVertexShader;
    GLuint m_uSecondFragmentShader;

    char* m_pSecondVertexShader;
    char* m_pSecondFragShader;


    GLint m_iSecondPositionAttrLocation;
    GLint m_iSecondTextureCoordAttrLocation;

    GLuint m_uFrameBufferId;
    GLuint m_uFrameTextureId;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETWOPASSFILTER_H
