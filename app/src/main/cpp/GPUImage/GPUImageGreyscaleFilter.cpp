/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageGreyscaleFilter.h"

// 片元着色器
extern const char _greyScale_fragment_shader[]=
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
        : GPUImageFilter(_greyScale_fragment_shader)
{

}

GPUImageGreyscaleFilter::~GPUImageGreyscaleFilter()
{

}