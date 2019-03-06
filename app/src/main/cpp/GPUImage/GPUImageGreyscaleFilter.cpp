/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageGreyscaleFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _greyScale_fragment_shader[]=SHADER_STR(
    precision highp float;

    varying vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        float luminance = dot(textureColor.rgb, W);

        gl_FragColor = vec4(vec3(luminance), textureColor.a);
    }
);

#else

// 片元着色器
extern const char _greyScale_fragment_shader[]=SHADER_STR(
    precision mediump float;
    uniform sampler2D inputImageTexture;
    varying vec2 textureCoordinate;

    void main()
    {
    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
    float grey;
    grey = dot(textureColor.rgb, vec3(0.299, 0.587, 0.114));
    gl_FragColor = vec4(grey, grey, grey, 1.0);
    }
);

#endif




GPUImageGreyscaleFilter::GPUImageGreyscaleFilter()
        : GPUImageFilter(_greyScale_fragment_shader)
{

}

GPUImageGreyscaleFilter::~GPUImageGreyscaleFilter()
{

}