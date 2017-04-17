/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorInvertFilter.h"

// 片元着色器
extern const char _colorInvert_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4((1.0 - textureColor.rgb), textureColor.w);\n"
"}"
;

GPUImageColorInvertFilter::GPUImageColorInvertFilter()
    : GPUImageFilter(_colorInvert_fragment_shader)
{

}

GPUImageColorInvertFilter::~GPUImageColorInvertFilter()
{

}