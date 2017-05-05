/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageJFAVoronoiFilter.h"


// 顶点着色器
extern const char _JFAVoronoi_vertex_shader[]=
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"uniform float sampleStep;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 widthStep = vec2(sampleStep, 0.0);\n"
"    vec2 heightStep = vec2(0.0, sampleStep);\n"
"    vec2 widthHeightStep = vec2(sampleStep);\n"
"    vec2 widthNegativeHeightStep = vec2(sampleStep, -sampleStep);\n"
"\n"
"    textureCoordinate = inputTextureCoordinate.xy;\n"
"    leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;\n"
"    rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;\n"
"\n"
"    topTextureCoordinate = inputTextureCoordinate.xy - heightStep;\n"
"    topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;\n"
"    topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;\n"
"\n"
"    bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;\n"
"    bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;\n"
"    bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;\n"
"}"
;

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _JFAVoronoi_fragment_shader[]=
"precision highp float;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform vec2 size;\n"
"//varying vec2 textureCoordinate;\n"
"//uniform float sampleStep;\n"
"\n"
"vec2 getCoordFromColor(vec4 color)\n"
"{\n"
"    float z = color.z * 256.0;\n"
"    float yoff = floor(z / 8.0);\n"
"    float xoff = mod(z, 8.0);\n"
"    float x = color.x*256.0 + xoff*256.0;\n"
"    float y = color.y*256.0 + yoff*256.0;\n"
"    return vec2(x,y) / size;\n"
"}\n"
"\n"
"void main(void) {\n"
"\n"
"    vec2 sub;\n"
"    vec4 dst;\n"
"    vec4 local = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 sam;\n"
"    float l;\n"
"    float smallestDist;\n"
"    if(local.a == 0.0){\n"
"\n"
"        smallestDist = dot(1.0,1.0);\n"
"    }else{\n"
"        sub = getCoordFromColor(local)-textureCoordinate;\n"
"        smallestDist = dot(sub,sub);\n"
"    }\n"
"    dst = local;\n"
"\n"
"\n"
"    sam = texture2D(inputImageTexture, topRightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, topTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, topLeftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomRightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomLeftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, leftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, rightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"    gl_FragColor = dst;\n"
"}"
;




#else

// 片元着色器
extern const char _JFAVoronoi_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform vec2 size;\n"
"//varying vec2 textureCoordinate;\n"
"//uniform float sampleStep;\n"
"\n"
"vec2 getCoordFromColor(vec4 color)\n"
"{\n"
"    float z = color.z * 256.0;\n"
"    float yoff = floor(z / 8.0);\n"
"    float xoff = mod(z, 8.0);\n"
"    float x = color.x*256.0 + xoff*256.0;\n"
"    float y = color.y*256.0 + yoff*256.0;\n"
"    return vec2(x,y) / size;\n"
"}\n"
"\n"
"void main(void) {\n"
"\n"
"    vec2 sub;\n"
"    vec4 dst;\n"
"    vec4 local = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 sam;\n"
"    float l;\n"
"    float smallestDist;\n"
"    if(local.a == 0.0){\n"
"\n"
"        smallestDist = dot(1.0,1.0);\n"
"    }else{\n"
"        sub = getCoordFromColor(local)-textureCoordinate;\n"
"        smallestDist = dot(sub,sub);\n"
"    }\n"
"    dst = local;\n"
"\n"
"\n"
"    sam = texture2D(inputImageTexture, topRightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, topTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, topLeftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomRightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, bottomLeftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, leftTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"\n"
"    sam = texture2D(inputImageTexture, rightTextureCoordinate);\n"
"    if(sam.a == 1.0){\n"
"        sub = (getCoordFromColor(sam)-textureCoordinate);\n"
"        l = dot(sub,sub);\n"
"        if(l < smallestDist){\n"
"            smallestDist = l;\n"
"            dst = sam;\n"
"        }\n"
"    }\n"
"    gl_FragColor = dst;\n"
"}"
;

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

bool GPUImageJFAVoronoiFilter::draw(GLuint textureId, int viewWidth, int viewHeight)
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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return GPUImageFilter::draw(lastTextureID, viewWidth, viewHeight);
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

    if(0 != m_uFrameBufferId && glIsFramebuffer(m_uFrameBufferId))
    {
        glDeleteFramebuffers(1, &m_uFrameBufferId);
        m_uFrameBufferId = 0;
    }

    if(0 != m_uFrameBufferTextureId && glIsTexture(m_uFrameBufferTextureId))
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

