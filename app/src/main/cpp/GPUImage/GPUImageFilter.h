/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_GPUIMAGEFILTER_H
#define CGPUIMAGE_GPUIMAGEFILTER_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>


#include "../util/openglHeader.h"
#include "../util/logUtil.h"
#include "../util/const.h"


class GPUImageFilter {
public:
    GPUImageFilter();
    GPUImageFilter(const char* vertex, const char* fragment);
    GPUImageFilter(const char* fragment);
    virtual ~GPUImageFilter();


public:
    virtual bool createProgram();

    virtual void setVertexCoordinate(float* vertexCoordinate);

    virtual void setTextureCoordinate(float* textureCoordinate);

    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId = 0);
    virtual bool release();

    virtual bool createTexture(int textureWidth, int textureHeight);
    virtual bool draw(GLubyte* rgbaData, int viewWidth, int viewHeight);

    virtual void setTextureSize(int width, int height);
    virtual void setTextureRotation(Rotation rotation);

public:
    bool isRotationSwapWidthAndHeight();

protected:
    virtual bool createVertexShader(char* vertex, int& length);
    virtual bool createFragmentShader(char* fragment, int& length);

protected:
    bool beforeDraw();

    bool onDraw();

    bool checkGLError(const char* funName);

    bool init(const char *vertex, const char *fragment);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();
    virtual bool onDrawExtra();

protected:
    GLuint m_uProgram;
    GLuint m_uVertexShader;
    GLuint m_uFragmentShader;

    GLuint m_uPositionLocation;
    GLuint m_uTextureCoordLocation;

    GLfloat* m_pVertexCoordinate;
    GLfloat* m_pTextureCoordinate;

    char* m_pVertexShader;
    char* m_pFragmnetShader;

    GLuint m_uTextureId;
    int m_iTextureWidth;
    int m_iTextureHeight;

    Rotation m_eRotation;

    GLint m_iInputTextureUniformLocation;
};


#endif //CGPUIMAGE_GPUIMAGEFILTER_H
