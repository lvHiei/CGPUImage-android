/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageColorInvertFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _colorInvert_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

        gl_FragColor = vec4((1.0 - textureColor.rgb), textureColor.w);
    }
);

#else

// 片元着色器
extern const char _colorInvert_fragment_shader[]= SHADER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

     gl_FragColor = vec4((1.0 - textureColor.rgb), textureColor.w);
    }
);

#endif




GPUImageColorInvertFilter::GPUImageColorInvertFilter()
    : GPUImageFilter(_colorInvert_fragment_shader)
{

}

GPUImageColorInvertFilter::~GPUImageColorInvertFilter()
{

}