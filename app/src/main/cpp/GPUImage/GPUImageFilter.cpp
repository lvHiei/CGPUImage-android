/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageFilter.h"
#include "../util/Shader.h"


// 顶点着色器
extern const char _base_vertex_shader[] = SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    varying vec2 textureCoordinate;

    void main()
    {
        gl_Position = position;
        textureCoordinate = inputTextureCoordinate.xy;
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _base_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
    }
);

#else

// 片元着色器
extern const char _base_fragment_shader[] = SHADER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;

    void main()
    {
        gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
    }
);

#endif





GPUImageFilter::GPUImageFilter()
{
    init(_base_vertex_shader, _base_fragment_shader);
}

GPUImageFilter::GPUImageFilter(const char *fragment)
{
    init(_base_vertex_shader, fragment);
}

GPUImageFilter::GPUImageFilter(const char *vertex, const char *fragment)
{
    init(vertex, fragment);
}


GPUImageFilter::~GPUImageFilter()
{
    this->release();
    m_uProgram = 0;
    m_uPositionLocation = 0;
    m_uTextureCoordLocation = 0;
}

bool GPUImageFilter::init(const char *vertex, const char *fragment)
{
    m_uProgram = 0;
    m_uPositionLocation = 0;
    m_uTextureCoordLocation = 0;

    m_uTextureId = 0;
    m_iTextureWidth = 0;
    m_iTextureHeight = 0;

    m_pVertexCoordinate = (float *) malloc(sizeof(float) * VERTEX_COORDINATE_SIZE);
    m_pTextureCoordinate = (float *) malloc(sizeof(float) * TEXTURE_COORDINATE_SIZE);

    m_pVertexShader = NULL;
    m_pFragmnetShader = NULL;

    uint32_t vertex_len = strlen(vertex) + 1;
    uint32_t fragment_len = strlen(fragment) + 1;

    m_pVertexShader = (char *) malloc(vertex_len);
    m_pFragmnetShader = (char *) malloc(fragment_len);

    strcpy(m_pVertexShader, vertex);
    strcpy(m_pFragmnetShader, fragment);

    return true;
}

bool GPUImageFilter::createProgram()
{
    //    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    // 清除颜色
    glClearColor(0.0, 0.0, 0.0, 0.0);

    Shader shader;
    if(!shader.createProgram(m_pVertexShader, m_pFragmnetShader)){
        LOGE("create program failed, errmsg:%s,func:%s", shader.getErrMsg(), __FUNCTION__);
        return false;
    }

    m_uProgram = shader.getProgram();

    m_uPositionLocation = glGetAttribLocation(m_uProgram, "position");
    m_uTextureCoordLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate");
    m_iInputTextureUniformLocation = glGetUniformLocation(m_uProgram, "inputImageTexture");
    this->createProgramExtra();

    return !checkGLError("createProgram");
}

bool GPUImageFilter::createProgramExtra()
{
    return true;
}

void GPUImageFilter::setVertexCoordinate(float *vertexCoordinate)
{
    if(!vertexCoordinate){
        return;
    }

    memcpy(m_pVertexCoordinate, vertexCoordinate, sizeof(float)*VERTEX_COORDINATE_SIZE);
}

void GPUImageFilter::setTextureCoordinate(float *textureCoordinate)
{
    if(!textureCoordinate){
        return;
    }

    memcpy(m_pTextureCoordinate, textureCoordinate, sizeof(float)*TEXTURE_COORDINATE_SIZE);
}

bool GPUImageFilter::draw(GLuint textureId, int viewWidth, int viewHeight, GLuint frameBufferId)
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
    glUseProgram(m_uProgram);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    this->beforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(0 ,0 , viewWidth, viewHeight);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(m_iInputTextureUniformLocation, 0);


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->onDraw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return !checkGLError("draw");
}

bool GPUImageFilter::beforeDraw()
{
    glVertexAttribPointer(m_uPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, m_pVertexCoordinate);
    glEnableVertexAttribArray(m_uPositionLocation);

    glVertexAttribPointer(m_uTextureCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, m_pTextureCoordinate);
    glEnableVertexAttribArray(m_uTextureCoordLocation);

    this->beforeDrawExtra();

    return true;
}

bool GPUImageFilter::onDraw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(m_uPositionLocation);
    glDisableVertexAttribArray(m_uTextureCoordLocation);

    this->onDrawExtra();

    return true;
}

bool GPUImageFilter::beforeDrawExtra()
{
    return true;
}

bool GPUImageFilter::onDrawExtra()
{
    return true;
}

bool GPUImageFilter::release()
{
    if(NULL != m_pVertexCoordinate){
        free(m_pVertexCoordinate);
        m_pVertexCoordinate = NULL;
    }

    if(NULL != m_pTextureCoordinate){
        free(m_pTextureCoordinate);
        m_pTextureCoordinate = NULL;
    }

    if(m_uProgram != 0){
        glDeleteProgram(m_uProgram);
        m_uProgram = 0;
    }

    if(m_uTextureId != 0){
        glDeleteTextures(1, &m_uTextureId);
        m_uTextureId = 0;
    }

    if(NULL != m_pVertexShader){
        free(m_pVertexShader);
        m_pVertexShader = NULL;
    }

    if(NULL != m_pFragmnetShader){
        free(m_pFragmnetShader);
        m_pFragmnetShader = NULL;
    }

    LOGI("GPUImageFilter::released");
    return true;
}

bool GPUImageFilter::createTexture(int textureWidth, int textureHeight)
{
    m_iTextureWidth = textureWidth;
    m_iTextureHeight = textureHeight;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_uTextureId);
    glBindTexture(GL_TEXTURE_2D, m_uTextureId);
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    return checkGLError("createTexture");
}

bool GPUImageFilter::draw(GLubyte *rgbaData, int viewWidth, int viewHeight)
{
    glUseProgram(m_uProgram);

    glViewport(0 ,0 , viewWidth, viewHeight);

    this->beforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_uTextureId);


    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    m_iTextureWidth,
                    m_iTextureHeight,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    rgbaData);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->onDraw();

    return checkGLError("draw");
}

bool GPUImageFilter::checkGLError(const char* funName)
{
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        LOGE("GL error after %s(): 0x%08x\n", funName, err);
        return true;
    }
    return false;
}


void GPUImageFilter::setTextureSize(int width, int height)
{
    m_iTextureWidth = width;
    m_iTextureHeight = height;
}

void GPUImageFilter::setTextureRotation(Rotation rotation)
{
    m_eRotation = rotation;
}

bool GPUImageFilter::isRotationSwapWidthAndHeight()
{
    return ROTATION_90 == m_eRotation || ROTATION_270 == m_eRotation;
}

