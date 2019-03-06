/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageJFAVoronoiFilter.h"


// 顶点着色器
extern const char _JFAVoronoi_vertex_shader[] = SHADER_STR(
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    uniform float sampleStep;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    void main()
    {
        gl_Position = position;

        vec2 widthStep = vec2(sampleStep, 0.0);
        vec2 heightStep = vec2(0.0, sampleStep);
        vec2 widthHeightStep = vec2(sampleStep);
        vec2 widthNegativeHeightStep = vec2(sampleStep, -sampleStep);

        textureCoordinate = inputTextureCoordinate.xy;
        leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;
        rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;

        topTextureCoordinate = inputTextureCoordinate.xy - heightStep;
        topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;
        topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;

        bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;
        bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;
        bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _JFAVoronoi_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform vec2 size;
    //varying vec2 textureCoordinate;
    //uniform float sampleStep;

    vec2 getCoordFromColor(vec4 color)
    {
        float z = color.z * 256.0;
        float yoff = floor(z / 8.0);
        float xoff = mod(z, 8.0);
        float x = color.x*256.0 + xoff*256.0;
        float y = color.y*256.0 + yoff*256.0;
        return vec2(x,y) / size;
    }

    void main(void) {

        vec2 sub;
        vec4 dst;
        vec4 local = texture2D(inputImageTexture, textureCoordinate);
        vec4 sam;
        float l;
        float smallestDist;
        if(local.a == 0.0){

            smallestDist = dot(1.0,1.0);
        }else{
            sub = getCoordFromColor(local)-textureCoordinate;
            smallestDist = dot(sub,sub);
        }
        dst = local;


        sam = texture2D(inputImageTexture, topRightTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, topTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, topLeftTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, bottomRightTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, bottomTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, bottomLeftTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, leftTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }

        sam = texture2D(inputImageTexture, rightTextureCoordinate);
        if(sam.a == 1.0){
            sub = (getCoordFromColor(sam)-textureCoordinate);
            l = dot(sub,sub);
            if(l < smallestDist){
                smallestDist = l;
                dst = sam;
            }
        }
        gl_FragColor = dst;
    }
);




#else

// 片元着色器
extern const char _JFAVoronoi_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform vec2 size;
 //varying vec2 textureCoordinate;
 //uniform float sampleStep;

 vec2 getCoordFromColor(vec4 color)
 {
     float z = color.z * 256.0;
     float yoff = floor(z / 8.0);
     float xoff = mod(z, 8.0);
     float x = color.x*256.0 + xoff*256.0;
     float y = color.y*256.0 + yoff*256.0;
     return vec2(x,y) / size;
 }

 void main(void) {

     vec2 sub;
     vec4 dst;
     vec4 local = texture2D(inputImageTexture, textureCoordinate);
     vec4 sam;
     float l;
     float smallestDist;
     if(local.a == 0.0){

         smallestDist = dot(1.0,1.0);
     }else{
         sub = getCoordFromColor(local)-textureCoordinate;
         smallestDist = dot(sub,sub);
     }
     dst = local;


     sam = texture2D(inputImageTexture, topRightTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, topTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, topLeftTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, bottomRightTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, bottomTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, bottomLeftTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, leftTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }

     sam = texture2D(inputImageTexture, rightTextureCoordinate);
     if(sam.a == 1.0){
         sub = (getCoordFromColor(sam)-textureCoordinate);
         l = dot(sub,sub);
         if(l < smallestDist){
             smallestDist = l;
             dst = sam;
         }
     }
     gl_FragColor = dst;
 }
);

#endif


GPUImageJFAVoronoiFilter::GPUImageJFAVoronoiFilter()
    : GPUImageFilter(_JFAVoronoi_vertex_shader, _JFAVoronoi_fragment_shader)
{
    m_uFrameBufferId = 0;
    m_uFrameBufferTextureId = 0;

    m_iSampleStepUniformLocation = -1;
    m_iSizeUniformLocation = -1;
}

GPUImageJFAVoronoiFilter::~GPUImageJFAVoronoiFilter()
{
    this->release();
}

void GPUImageJFAVoronoiFilter::setSizeInPixels(int w, int h)
{
    float width = log2(w);
    float height = log2(h);

    if(width != height){
        LOGW("Voronoi point texture must be square");
        return;
    }

    if (width != floor(width) || height != floor(height)) {
        LOGW("Voronoi point texture must be a power of 2.  Texture size %f, %f", w, h);
        return;
    }

    m_pSizeInPixels[0] = w;
    m_pSizeInPixels[1] = h;
}

void GPUImageJFAVoronoiFilter::setNumPasses(int numpasses)
{
    m_iNumPasses = numpasses;
}

bool GPUImageJFAVoronoiFilter::draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId)
{
    glUseProgram(m_uProgram);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferId);
    this->beforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(0 ,0 , m_iTextureWidth, m_iTextureHeight);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    this->onDraw();

    int currentPass = 0;
    GLuint lastTextureID = textureId;
    for(int pass = 1; pass <= m_iNumPasses + 1; ++pass){
        currentPass = pass;

        glClear(GL_COLOR_BUFFER_BIT);
        if(pass % 2 == 0 ){
            lastTextureID = m_uFrameBufferTextureId;
            glBindTexture(GL_TEXTURE_2D, m_uFrameBufferTextureId);
        }else{
            lastTextureID = textureId;
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        float step = pow(2.0, m_iNumPasses - pass)/pow(2.0, m_iNumPasses);
        glUniform1f(m_iSampleStepUniformLocation, step);
        glUniform2f(m_iSizeUniformLocation, m_pSizeInPixels[0], m_pSizeInPixels[1]);

        this->beforeDraw();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    return GPUImageFilter::draw(lastTextureID, viewWidth, viewHeight, frameBufferId);
}


bool GPUImageJFAVoronoiFilter::createProgramExtra()
{
    m_iSampleStepUniformLocation = glGetUniformLocation(m_uProgram, "sampleStep");
    m_iSizeUniformLocation = glGetUniformLocation(m_uProgram, "size");

    bool ret =  GPUImageFilter::createProgramExtra();
    ret = ret & createFrameBuffer();
    return ret;
}


bool GPUImageJFAVoronoiFilter::release()
{

    if(0 != m_uFrameBufferId)
    {
        glDeleteFramebuffers(1, &m_uFrameBufferId);
        m_uFrameBufferId = 0;
    }

    if(0 != m_uFrameBufferTextureId)
    {
        glDeleteTextures(1, &m_uFrameBufferTextureId);
        m_uFrameBufferTextureId = 0;
    }

    return true;
}


bool GPUImageJFAVoronoiFilter::createFrameBuffer()
{
    glGenFramebuffers(1, &m_uFrameBufferId);
    glGenTextures(1, &m_uFrameBufferTextureId);

    glBindTexture(GL_TEXTURE_2D, m_uFrameBufferTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, m_uFrameBufferTextureId, 0);

    bool ret = GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return ret;
}

