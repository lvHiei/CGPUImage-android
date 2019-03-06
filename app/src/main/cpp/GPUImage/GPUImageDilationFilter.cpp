/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageDilationFilter.h"



// 顶点着色器
extern const char _dilationRadiusOne_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec2 inputTextureCoordinate;

    uniform float texelWidthOffset;
    uniform float texelHeightOffset;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;

    void main()
    {
        gl_Position = position;

        vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

        centerTextureCoordinate = inputTextureCoordinate;
        oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
        oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
    }
);

// 顶点着色器
extern const char _dilationRadiusTwo_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec2 inputTextureCoordinate;

    uniform float texelWidthOffset;
    uniform float texelHeightOffset;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;

    void main()
    {
        gl_Position = position;

        vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

        centerTextureCoordinate = inputTextureCoordinate;
        oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
        oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
        twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
        twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
    }
);

// 顶点着色器
extern const char _dilationRadiusThree_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec2 inputTextureCoordinate;

    uniform float texelWidthOffset;
    uniform float texelHeightOffset;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;

    void main()
    {
        gl_Position = position;

        vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

        centerTextureCoordinate = inputTextureCoordinate;
        oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
        oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
        twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
        twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
        threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);
        threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);
    }
);



// 顶点着色器
extern const char _dilationRadiusFour_vertex_shader[]=SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec2 inputTextureCoordinate;

    uniform float texelWidthOffset;
    uniform float texelHeightOffset;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;
    varying vec2 fourStepsPositiveTextureCoordinate;
    varying vec2 fourStepsNegativeTextureCoordinate;

    void main()
    {
        gl_Position = position;

        vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

        centerTextureCoordinate = inputTextureCoordinate;
        oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;
        oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;
        twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);
        twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);
        threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);
        threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);
        fourStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 4.0);
        fourStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 4.0);
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _dilationRadiusOne_fragment_shader[]=SHADER_STR(
    precision lowp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
        float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
        float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;

        lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
        maxValue = max(maxValue, oneStepNegativeIntensity);

        gl_FragColor = vec4(vec3(maxValue), 1.0);
    }
);


// 片元着色器
extern const char _dilationRadiusTwo_fragment_shader[]=SHADER_STR(
    precision lowp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
        float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
        float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
        float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
        float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;

        lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
        maxValue = max(maxValue, oneStepNegativeIntensity);
        maxValue = max(maxValue, twoStepsPositiveIntensity);
        maxValue = max(maxValue, twoStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(maxValue), 1.0);
    }
);




// 片元着色器
extern const char _dilationRadiusThree_fragment_shader[]= SHADER_STR(
    precision lowp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
        float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
        float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
        float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
        float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
        float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
        float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;

        lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
        maxValue = max(maxValue, oneStepNegativeIntensity);
        maxValue = max(maxValue, twoStepsPositiveIntensity);
        maxValue = max(maxValue, twoStepsNegativeIntensity);
        maxValue = max(maxValue, threeStepsPositiveIntensity);
        maxValue = max(maxValue, threeStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(maxValue), 1.0);
    }
);


// 片元着色器
extern const char _dilationRadiusFour_fragment_shader[]=SHADER_STR(
    precision lowp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;
    varying vec2 fourStepsPositiveTextureCoordinate;
    varying vec2 fourStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
        float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
        float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
        float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
        float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
        float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
        float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;
        float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;
        float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;

        lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);
        maxValue = max(maxValue, oneStepNegativeIntensity);
        maxValue = max(maxValue, twoStepsPositiveIntensity);
        maxValue = max(maxValue, twoStepsNegativeIntensity);
        maxValue = max(maxValue, threeStepsPositiveIntensity);
        maxValue = max(maxValue, threeStepsNegativeIntensity);
        maxValue = max(maxValue, fourStepsPositiveIntensity);
        maxValue = max(maxValue, fourStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(maxValue), 1.0);
    }
);

#else


// 片元着色器
extern const char _dilationRadiusOne_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
     float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
     float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;

     float maxValue = max(centerIntensity, oneStepPositiveIntensity);
     maxValue = max(maxValue, oneStepNegativeIntensity);

     gl_FragColor = vec4(vec3(maxValue), 1.0);
 }
);


// 片元着色器
extern const char _dilationRadiusTwo_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
     float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
     float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
     float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
     float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;

     float maxValue = max(centerIntensity, oneStepPositiveIntensity);
     maxValue = max(maxValue, oneStepNegativeIntensity);
     maxValue = max(maxValue, twoStepsPositiveIntensity);
     maxValue = max(maxValue, twoStepsNegativeIntensity);

     gl_FragColor = vec4(vec3(maxValue), 1.0);
 }
);



// 片元着色器
extern const char _dilationRadiusThree_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;
 varying vec2 threeStepsPositiveTextureCoordinate;
 varying vec2 threeStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
     float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
     float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
     float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
     float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
     float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
     float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;

     float maxValue = max(centerIntensity, oneStepPositiveIntensity);
     maxValue = max(maxValue, oneStepNegativeIntensity);
     maxValue = max(maxValue, twoStepsPositiveIntensity);
     maxValue = max(maxValue, twoStepsNegativeIntensity);
     maxValue = max(maxValue, threeStepsPositiveIntensity);
     maxValue = max(maxValue, threeStepsNegativeIntensity);

     gl_FragColor = vec4(vec3(maxValue), 1.0);
 }
);


// 片元着色器
extern const char _dilationRadiusFour_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;
 varying vec2 threeStepsPositiveTextureCoordinate;
 varying vec2 threeStepsNegativeTextureCoordinate;
 varying vec2 fourStepsPositiveTextureCoordinate;
 varying vec2 fourStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
     float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
     float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
     float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
     float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
     float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
     float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;
     float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;
     float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;

     float maxValue = max(centerIntensity, oneStepPositiveIntensity);
     maxValue = max(maxValue, oneStepNegativeIntensity);
     maxValue = max(maxValue, twoStepsPositiveIntensity);
     maxValue = max(maxValue, twoStepsNegativeIntensity);
     maxValue = max(maxValue, threeStepsPositiveIntensity);
     maxValue = max(maxValue, threeStepsNegativeIntensity);
     maxValue = max(maxValue, fourStepsPositiveIntensity);
     maxValue = max(maxValue, fourStepsNegativeIntensity);

     gl_FragColor = vec4(vec3(maxValue), 1.0);
 }
);

#endif
GPUImageDilationFilter::GPUImageDilationFilter()
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _dilationRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _dilationRadiusOne_fragment_shader)
{

}

GPUImageDilationFilter::GPUImageDilationFilter(int radius)
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _dilationRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _dilationRadiusOne_fragment_shader)
{
    const char* vertexShaderForThisRadius = NULL;
    const char* fragmentShaderForThisRadius = NULL;
    switch (radius)
    {
        case 0:
        case 1:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _dilationRadiusOne_fragment_shader;
            break;
        }
        case 2:
        {
            vertexShaderForThisRadius = _dilationRadiusTwo_vertex_shader;
            fragmentShaderForThisRadius = _dilationRadiusTwo_fragment_shader;
            break;
        }
        case 3:
        {
            vertexShaderForThisRadius = _dilationRadiusThree_vertex_shader;
            fragmentShaderForThisRadius = _dilationRadiusThree_fragment_shader;
            break;
        }
        case 4:
        {
            vertexShaderForThisRadius = _dilationRadiusFour_vertex_shader;
            fragmentShaderForThisRadius = _dilationRadiusFour_fragment_shader;
            break;
        }
        default:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _dilationRadiusOne_fragment_shader;
            break;
        }
    }

    resetShader(vertexShaderForThisRadius, fragmentShaderForThisRadius, vertexShaderForThisRadius, fragmentShaderForThisRadius);
}

GPUImageDilationFilter::~GPUImageDilationFilter()
{

}

