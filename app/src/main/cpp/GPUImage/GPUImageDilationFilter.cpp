/**
 * Created by lvHiei on 17-4-14.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageDilationFilter.h"



// 顶点着色器
extern const char _dilationRadiusOne_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 offset = vec2(texelWidthOffset, texelHeightOffset);\n"
"\n"
"    centerTextureCoordinate = inputTextureCoordinate;\n"
"    oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;\n"
"    oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;\n"
"}"
;

// 顶点着色器
extern const char _dilationRadiusTwo_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 offset = vec2(texelWidthOffset, texelHeightOffset);\n"
"\n"
"    centerTextureCoordinate = inputTextureCoordinate;\n"
"    oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;\n"
"    oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;\n"
"    twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);\n"
"    twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);\n"
"}"
;

// 顶点着色器
extern const char _dilationRadiusThree_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 offset = vec2(texelWidthOffset, texelHeightOffset);\n"
"\n"
"    centerTextureCoordinate = inputTextureCoordinate;\n"
"    oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;\n"
"    oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;\n"
"    twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);\n"
"    twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);\n"
"    threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);\n"
"    threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);\n"
"}"
;



// 顶点着色器
extern const char _dilationRadiusFour_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec2 inputTextureCoordinate;\n"
"\n"
"uniform float texelWidthOffset;\n"
"uniform float texelHeightOffset;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"varying vec2 fourStepsPositiveTextureCoordinate;\n"
"varying vec2 fourStepsNegativeTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    vec2 offset = vec2(texelWidthOffset, texelHeightOffset);\n"
"\n"
"    centerTextureCoordinate = inputTextureCoordinate;\n"
"    oneStepNegativeTextureCoordinate = inputTextureCoordinate - offset;\n"
"    oneStepPositiveTextureCoordinate = inputTextureCoordinate + offset;\n"
"    twoStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 2.0);\n"
"    twoStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 2.0);\n"
"    threeStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 3.0);\n"
"    threeStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 3.0);\n"
"    fourStepsNegativeTextureCoordinate = inputTextureCoordinate - (offset * 4.0);\n"
"    fourStepsPositiveTextureCoordinate = inputTextureCoordinate + (offset * 4.0);\n"
"}"
;



#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _dilationRadiusOne_fragment_shader[]=
"precision lowp float;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"\n"
"    lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _dilationRadiusTwo_fragment_shader[]=
"precision lowp float;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"\n"
"    lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;



// 片元着色器
extern const char _dilationRadiusThree_fragment_shader[]=
"precision lowp float;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"    float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;\n"
"    float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;\n"
"\n"
"    lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _dilationRadiusFour_fragment_shader[]=
"precision lowp float;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"varying vec2 fourStepsPositiveTextureCoordinate;\n"
"varying vec2 fourStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"    float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;\n"
"    float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;\n"
"    float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;\n"
"    float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;\n"
"\n"
"    lowp float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, fourStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, fourStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;

#else


// 片元着色器
extern const char _dilationRadiusOne_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"\n"
"    float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _dilationRadiusTwo_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"\n"
"    float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;



// 片元着色器
extern const char _dilationRadiusThree_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"    float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;\n"
"    float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;\n"
"\n"
"    float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _dilationRadiusFour_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"varying vec2 twoStepsPositiveTextureCoordinate;\n"
"varying vec2 twoStepsNegativeTextureCoordinate;\n"
"varying vec2 threeStepsPositiveTextureCoordinate;\n"
"varying vec2 threeStepsNegativeTextureCoordinate;\n"
"varying vec2 fourStepsPositiveTextureCoordinate;\n"
"varying vec2 fourStepsNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;\n"
"    float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;\n"
"    float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;\n"
"    float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;\n"
"    float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;\n"
"    float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;\n"
"    float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;\n"
"    float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;\n"
"    float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;\n"
"\n"
"    float maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, fourStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, fourStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(maxValue), 1.0);\n"
"}"
;

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

