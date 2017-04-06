/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGammaFilter.h"

// 顶点着色器
const char _gamma_vertex_shader[]=
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
const char _gamma_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform float gamma;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   gl_FragColor = vec4(pow(textureColor.rgb, vec3(gamma)), textureColor.w);\n"
"}\n"
;

GPUImageGammaFilter::GPUImageGammaFilter()
{
    m_fGamma = 2.0f;
}


GPUImageGammaFilter::~GPUImageGammaFilter()
{

}

void GPUImageGammaFilter::setGamma(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (3.0f - 1.0f) / 100;

    m_fGamma = 1.0f + incremental * percent;
}

bool GPUImageGammaFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_gamma_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _gamma_vertex_shader);
    length = expLen;

    return true;
}

bool GPUImageGammaFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(_gamma_fragment_shader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

    sprintf(fragment, _gamma_fragment_shader);
    length = expLen;
    return true;
}

bool GPUImageGammaFilter::createProgramExtra()
{
    m_iGammaLocation = glGetUniformLocation(m_uProgram, "gamma");
    return true;
}

bool GPUImageGammaFilter::beforeDrawExtra()
{
    glUniform1f(m_iGammaLocation, m_fGamma);
    return true;
}

bool GPUImageGammaFilter::onDrawExtra()
{
    return true;
}