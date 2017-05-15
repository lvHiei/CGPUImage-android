/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTwoPassFilter.h"
#include "../util/TextureRotateUtil.h"

GPUImageTwoPassFilter::GPUImageTwoPassFilter(const char *firstVertex, const char *fisrtFragment,
                                             const char *secondVertex, const char *secondFragment)
{

    m_uSecondProgram = 0;
    m_uSecondFragmentShader = 0;
    m_uSecondVertexShader = 0;


    m_uFrameBufferId = 0;
    m_uFrameTextureId = 0;

    int fvLen = strlen(firstVertex) + 1;
    int ffLen = strlen(fisrtFragment) + 1;
    int svLen = strlen(secondVertex) + 1;
    int sfLen = strlen(secondFragment) + 1;

    m_pVertexShader = (char *) malloc(fvLen);
    m_pFragmnetShader = (char *) malloc(ffLen);
    m_pSecondVertexShader = (char *) malloc(svLen);
    m_pSecondFragShader = (char *) malloc(sfLen);


    strcpy(m_pVertexShader, firstVertex);
    strcpy(m_pFragmnetShader, fisrtFragment);
    strcpy(m_pSecondVertexShader, secondVertex);
    strcpy(m_pSecondFragShader, secondFragment);
}

GPUImageTwoPassFilter::~GPUImageTwoPassFilter()
{
    this->release();
}

bool GPUImageTwoPassFilter::createProgram()
{
    // create framebuffer
    createFrameBuffer();

    // create first program
    //编译顶点着色器
    const char*vertex_shader = m_pVertexShader;
    const char*fragment_shader = m_pFragmnetShader;

    m_uVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_uVertexShader, 1, &vertex_shader, NULL);
    glCompileShader(m_uVertexShader);
    GLint compile_status = -20;
    glGetShaderiv( m_uVertexShader, GL_COMPILE_STATUS,  &compile_status);
    if(GL_TRUE != compile_status )
    {
        GLsizei length = 0;
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_uVertexShader,
                           1024,
                           &length,
                           infoLog);
        LOGE("GPUImageTwoPassFilter : compile vertexShader failed : error msg = %s", infoLog);

        return false;
    }

    // 编译片元着色器
    m_uFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_uFragmentShader,1,&fragment_shader,NULL);
    glCompileShader(m_uFragmentShader);
    glGetShaderiv( m_uFragmentShader, GL_COMPILE_STATUS,  &compile_status);
    if(GL_TRUE != compile_status )
    {
        GLsizei length = 0;
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_uFragmentShader,
                           1024,
                           &length,
                           infoLog);
        LOGE("GPUImageTwoPassFilter : compile fragmentShader failed : error msg = %s", infoLog);
        return false;
    }

    // 创建应用程序，链接着色器
    m_uProgram = glCreateProgram();
    glAttachShader(m_uProgram, m_uVertexShader);
    glAttachShader(m_uProgram, m_uFragmentShader);
    glLinkProgram(m_uProgram);

    m_uPositionLocation = glGetAttribLocation(m_uProgram, "position");
    m_uTextureCoordLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate");

    this->firstCreateProgramExtra();


    // create second program
    //编译顶点着色器
    vertex_shader = m_pSecondVertexShader;
    fragment_shader = m_pSecondFragShader;

    m_uSecondVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_uSecondVertexShader, 1, &vertex_shader, NULL);
    glCompileShader(m_uSecondVertexShader);
    compile_status = -20;
    glGetShaderiv( m_uSecondVertexShader, GL_COMPILE_STATUS,  &compile_status);
    if(GL_TRUE != compile_status )
    {
        GLsizei length = 0;
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_uSecondVertexShader,
                           1024,
                           &length,
                           infoLog);
        LOGE("GPUImageTwoPassFilter : compile vertexShader failed : error msg = %s", infoLog);

        return false;
    }

    // 编译片元着色器
    m_uSecondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_uSecondFragmentShader,1,&fragment_shader,NULL);
    glCompileShader(m_uSecondFragmentShader);
    glGetShaderiv( m_uSecondFragmentShader, GL_COMPILE_STATUS,  &compile_status);
    if(GL_TRUE != compile_status )
    {
        GLsizei length = 0;
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_uSecondFragmentShader,
                           1024,
                           &length,
                           infoLog);
        LOGE("GPUImageTwoPassFilter : compile fragmentShader failed : error msg = %s", infoLog);
        return false;
    }

    // 创建应用程序，链接着色器
    m_uSecondProgram = glCreateProgram();
    glAttachShader(m_uSecondProgram, m_uSecondVertexShader);
    glAttachShader(m_uSecondProgram, m_uSecondFragmentShader);
    glLinkProgram(m_uSecondProgram);

    m_iSecondPositionAttrLocation = glGetAttribLocation(m_uSecondProgram, "position");
    m_iSecondTextureCoordAttrLocation = glGetAttribLocation(m_uSecondProgram, "inputTextureCoordinate");

    this->secondCreateProgramExtra();

    return !checkGLError("createProgram");
}

bool GPUImageTwoPassFilter::draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId)
{
    // 绘制第一个到framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFrameBufferId);
    glUseProgram(m_uProgram);

    this->firstBeforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(0 ,0 , m_iTextureWidth, m_iTextureHeight);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->firstOnDraw();

    // 绘制第二个
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
    glUseProgram(m_uSecondProgram);

    this->secondBeforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(0 ,0 , viewWidth, viewHeight);
    glBindTexture(GL_TEXTURE_2D, m_uFrameTextureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->secondOnDraw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return !checkGLError("draw");
}

bool GPUImageTwoPassFilter::release()
{
    if(NULL != m_pVertexShader)
    {
        free(m_pVertexShader);
        m_pVertexShader = NULL;
    }

    if(NULL != m_pFragmnetShader)
    {
        free(m_pFragmnetShader);
        m_pFragmnetShader = NULL;
    }

    if(NULL != m_pSecondVertexShader)
    {
        free(m_pSecondVertexShader);
        m_pSecondVertexShader = NULL;
    }

    if(NULL != m_pSecondFragShader)
    {
        free(m_pSecondFragShader);
        m_pSecondFragShader = NULL;
    }

    if(0 != m_uFrameBufferId)
    {
        glDeleteFramebuffers(1, &m_uFrameBufferId);
        m_uFrameBufferId = 0;
    }

    if(0 != m_uFrameTextureId)
    {
        glDeleteTextures(1, &m_uFrameTextureId);
        m_uFrameTextureId = 0;
    }

    if(m_uVertexShader != 0){
        glDeleteShader(m_uVertexShader);
        m_uVertexShader = 0;
    }

    if(m_uFragmentShader != 0){
        glDeleteShader(m_uFragmentShader);
        m_uFragmentShader = 0;
    }

    if(m_uSecondVertexShader != 0){
        glDeleteShader(m_uSecondVertexShader);
        m_uSecondVertexShader = 0;
    }

    if(m_uSecondFragmentShader != 0){
        glDeleteShader(m_uSecondFragmentShader);
        m_uSecondFragmentShader = 0;
    }

    if(m_uSecondProgram != 0){
        glDeleteProgram(m_uSecondProgram);
        m_uSecondProgram = 0;
    }

    return checkGLError("GPUImageTwoPassFilter::release");
}

bool GPUImageTwoPassFilter::firstCreateProgramExtra()
{

    return true;
}

bool GPUImageTwoPassFilter::secondCreateProgramExtra()
{
    return true;
}

bool GPUImageTwoPassFilter::firstBeforeDraw()
{
    float* textureCoord = TextureRotateUtil::getTextureCoordinate(ROTATION_NORMAL, false, false);

    glVertexAttribPointer(m_uPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, m_pVertexCoordinate);
    glEnableVertexAttribArray(m_uPositionLocation);

    glVertexAttribPointer(m_uTextureCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoord);
    glEnableVertexAttribArray(m_uTextureCoordLocation);

    return true;
}

bool GPUImageTwoPassFilter::firstOnDraw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(m_uPositionLocation);
    glDisableVertexAttribArray(m_uTextureCoordLocation);

    return true;
}

bool GPUImageTwoPassFilter::secondBeforeDraw()
{
    glVertexAttribPointer(m_iSecondPositionAttrLocation, 2, GL_FLOAT, GL_FALSE, 0, m_pVertexCoordinate);
    glEnableVertexAttribArray(m_iSecondPositionAttrLocation);

    glVertexAttribPointer(m_iSecondTextureCoordAttrLocation, 2, GL_FLOAT, GL_FALSE, 0, m_pTextureCoordinate);
    glEnableVertexAttribArray(m_iSecondTextureCoordAttrLocation);

    return true;
}

bool GPUImageTwoPassFilter::secondOnDraw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(m_iSecondPositionAttrLocation);
    glDisableVertexAttribArray(m_iSecondTextureCoordAttrLocation);

    return true;
}

bool GPUImageTwoPassFilter::createFrameBuffer()
{
    glGenFramebuffers(1, &m_uFrameBufferId);
    glGenTextures(1, &m_uFrameTextureId);

    glBindTexture(GL_TEXTURE_2D, m_uFrameTextureId);
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
                           GL_TEXTURE_2D, m_uFrameTextureId, 0);

    bool ret = GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return ret;
}

void GPUImageTwoPassFilter::setTextureCoordinate(float *textureCoordinate)
{
    int idx = 0;
    for(int i=0; i<8; i++)
    {
        if(i % 2 == 0){
            m_pTextureCoordinate[idx++] = textureCoordinate[i];
        }else{
            m_pTextureCoordinate[idx++] = textureCoordinate[i] == 0.0f ? 1.0f : 0.0f;
        }
    }
}


void GPUImageTwoPassFilter::resetShader(const char *firstVertex, const char *fisrtFragment,
                                        const char *secondVertex, const char *secondFragment)
{

    if(m_pVertexShader){
        free(m_pVertexShader);
    }

    if(m_pFragmnetShader){
        free(m_pFragmnetShader);
    }

    if(m_pSecondVertexShader){
        free(m_pSecondVertexShader);
    }

    if(m_pSecondFragShader){
        free(m_pSecondFragShader);
    }

    int fvLen = strlen(firstVertex) + 1;
    int ffLen = strlen(fisrtFragment) + 1;
    int svLen = strlen(secondVertex) + 1;
    int sfLen = strlen(secondFragment) + 1;

    m_pVertexShader = (char *) malloc(fvLen);
    m_pFragmnetShader = (char *) malloc(ffLen);
    m_pSecondVertexShader = (char *) malloc(svLen);
    m_pSecondFragShader = (char *) malloc(sfLen);


    strcpy(m_pVertexShader, firstVertex);
    strcpy(m_pFragmnetShader, fisrtFragment);
    strcpy(m_pSecondVertexShader, secondVertex);
    strcpy(m_pSecondFragShader, secondFragment);
}

