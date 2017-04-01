/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageGreyscaleFilter.h"


// 顶点着色器
const char _greyScale_vertex_shader[]=
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
const char _greyScale_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   float grey;\n"
"   grey = dot(textureColor.rgb, vec3(0.299, 0.587, 0.114));\n"
"   gl_FragColor = vec4(grey, grey, grey, 1.0);\n"
"}\n"
;


GPUImageGreyscaleFilter::GPUImageGreyscaleFilter()
        :GPUImageFilter()
{

}

GPUImageGreyscaleFilter::~GPUImageGreyscaleFilter()
{

}

bool GPUImageGreyscaleFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_greyScale_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _greyScale_vertex_shader);
    length = expLen;

    return true;
}

bool GPUImageGreyscaleFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(_greyScale_fragment_shader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

    sprintf(fragment, _greyScale_fragment_shader);
    length = expLen;
    return true;
}