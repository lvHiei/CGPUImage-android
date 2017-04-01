/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageFilter.h"
#include "logUtil.h"


// 顶点着色器
const char _base_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"

"varying vec2 textureCoordinate;\n"

"void main()\n"
"{\n"
"	gl_Position = position;\n"
"	textureCoordinate = inputTextureCoordinate.xy;\n"
"}\n"
;

// 片元着色器
const char _base_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   gl_FragColor = textureColor;\n"
"}\n"
;

const int VERTEX_COORDINATE_SIZE = 8;
const int TEXTURE_COORDINATE_SIZE = 8;

GPUImageFilter::GPUImageFilter()
{
    m_uProgram = 0;
    m_uPositionLocation = 0;
    m_uTextureCoordLocation = 0;

    m_uVertexShader = 0;
    m_uFragmentShader = 0;

    m_uTextureId = 0;
    m_iTextureWidth = 0;
    m_iTextureHeight = 0;

    m_pVertexCoordinate = (float *) malloc(sizeof(float) * VERTEX_COORDINATE_SIZE);
    m_pTextureCoordinate = (float *) malloc(sizeof(float) * TEXTURE_COORDINATE_SIZE);
}

GPUImageFilter::~GPUImageFilter()
{
    this->release();
    m_uProgram = 0;
    m_uPositionLocation = 0;
    m_uTextureCoordLocation = 0;
}

bool GPUImageFilter::createProgram()
{
    int vertexLen = 2048;
    int fragmentLen = 8196;
    char vertex[2048];
    char fragment[8196];

    this->createVertexShader(vertex, vertexLen);
    this->createFragmentShader(fragment, fragmentLen);

    const char*vertex_shader = vertex;
    const char*fragment_shader = fragment;

    //    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    // 清除颜色
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //编译顶点着色器
    m_uVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_uVertexShader,1,&vertex_shader,NULL);
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
        LOGE("OpenGLHelper : compile vertexShader failed : error msg = %s", infoLog);

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
        LOGE("OpenGLHelper : compile fragmentShader failed : error msg = %s", infoLog);
        return false;
    }

    // 创建应用程序，链接着色器
    m_uProgram = glCreateProgram();
    glAttachShader(m_uProgram, m_uVertexShader);
    glAttachShader(m_uProgram, m_uFragmentShader);
    glLinkProgram(m_uProgram);
//    glUseProgram(m_uProgram);

    m_uPositionLocation = glGetAttribLocation(m_uProgram, "position");
    m_uTextureCoordLocation = glGetAttribLocation(m_uProgram, "inputTextureCoordinate");

    this->createProgramExtra();

    if(GL_NO_ERROR != glGetError())
    {
        LOGE("createProgram : some opengl error occured");
        return false;
    }

    return true;
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

bool GPUImageFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_base_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _base_vertex_shader);
    length = expLen;

    return true;
}

bool GPUImageFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(_base_fragment_shader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

    sprintf(fragment, _base_fragment_shader);
    length = expLen;
    return true;
}

bool GPUImageFilter::draw(GLuint textureId, int viewWidth, int viewHeight)
{
    glUseProgram(m_uProgram);
    this->beforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(0 ,0 , viewWidth, viewHeight);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->onDraw();
    return true;
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

    if(m_uTextureId != 0){
        glDeleteTextures(1, &m_uTextureId);
        m_uTextureId = 0;
    }

    if(m_uVertexShader != 0){
        glDeleteShader(m_uVertexShader);
        m_uVertexShader = 0;
    }

    if(m_uFragmentShader != 0){
        glDeleteShader(m_uFragmentShader);
        m_uFragmentShader = 0;
    }

    if(m_uProgram != 0){
        glDeleteProgram(m_uProgram);
        m_uProgram = 0;
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

    return true;
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

    return true;
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
