/**
* Created by lvHiei on 17-5-3.
* This is a project of GPUImage implemented with c++, you can
* use it free. if you find some bug please send me a email.
* My Email is majun_1523@163.com.
*/

#include "GPUImageRGBDilationFilter.h"


extern const char _dilationRadiusOne_vertex_shader[];
extern const char _dilationRadiusTwo_vertex_shader[];
extern const char _dilationRadiusThree_vertex_shader[];
extern const char _dilationRadiusFour_vertex_shader[];


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _rgbDilationRadiusOne_fragment_shader[]=
"precision highp float;\n"
"\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"\n"
"    lowp vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, oneStepNegativeIntensity);\n"
"}"
;


// 片元着色器
extern const char _rgbDilationRadiusTwo_fragment_shader[]=
"precision highp float;\n"
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
"    lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"    lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"    lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"\n"
"    lowp vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, twoStepsNegativeIntensity);\n"
"}"
;

// 片元着色器
extern const char _rgbDilationRadiusThree_fragment_shader[]=
"precision highp float;\n"
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
"    lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"    lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"    lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"    lowp vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);\n"
"    lowp vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);\n"
"\n"
"    lowp vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, threeStepsNegativeIntensity);\n"
"}"
;


// 片元着色器
extern const char _rgbDilationRadiusFour_fragment_shader[]=
"precision highp float;\n"
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
"    lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"    lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"    lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"    lowp vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);\n"
"    lowp vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);\n"
"    lowp vec4 fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate);\n"
"    lowp vec4 fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate);\n"
"\n"
"    lowp vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, fourStepsPositiveIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, fourStepsNegativeIntensity);\n"
"}"
;


#else

// 片元着色器
extern const char _rgbDilationRadiusOne_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 centerTextureCoordinate;\n"
"varying vec2 oneStepPositiveTextureCoordinate;\n"
"varying vec2 oneStepNegativeTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"\n"
"    vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, oneStepNegativeIntensity);\n"
"}"
;


// 片元着色器
extern const char _rgbDilationRadiusTwo_fragment_shader[]=
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
"    vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"    vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"    vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"\n"
"    vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, twoStepsNegativeIntensity);\n"
"}"
;

// 片元着色器
extern const char _rgbDilationRadiusThree_fragment_shader[]=
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
"    vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"    vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"    vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"    vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"    vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"    vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);\n"
"    vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);\n"
"\n"
"    vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"    maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"    maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"    maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"    maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"\n"
"    gl_FragColor = max(maxValue, threeStepsNegativeIntensity);\n"
"}"
;


// 片元着色器
extern const char _rgbDilationRadiusFour_fragment_shader[]=
"precision mediump float;\n"
" varying vec2 centerTextureCoordinate;\n"
" varying vec2 oneStepPositiveTextureCoordinate;\n"
" varying vec2 oneStepNegativeTextureCoordinate;\n"
" varying vec2 twoStepsPositiveTextureCoordinate;\n"
" varying vec2 twoStepsNegativeTextureCoordinate;\n"
" varying vec2 threeStepsPositiveTextureCoordinate;\n"
" varying vec2 threeStepsNegativeTextureCoordinate;\n"
" varying vec2 fourStepsPositiveTextureCoordinate;\n"
" varying vec2 fourStepsNegativeTextureCoordinate;\n"
" \n"
" uniform sampler2D inputImageTexture;\n"
" \n"
" void main()\n"
" {\n"
"     vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);\n"
"     vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);\n"
"     vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);\n"
"     vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);\n"
"     vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);\n"
"     vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);\n"
"     vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);\n"
"     vec4 fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate);\n"
"     vec4 fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate);\n"
"     \n"
"     vec4 maxValue = max(centerIntensity, oneStepPositiveIntensity);\n"
"     maxValue = max(maxValue, oneStepNegativeIntensity);\n"
"     maxValue = max(maxValue, twoStepsPositiveIntensity);\n"
"     maxValue = max(maxValue, twoStepsNegativeIntensity);\n"
"     maxValue = max(maxValue, threeStepsPositiveIntensity);\n"
"     maxValue = max(maxValue, threeStepsNegativeIntensity);\n"
"     maxValue = max(maxValue, fourStepsPositiveIntensity);\n"
"     \n"
"     gl_FragColor = max(maxValue, fourStepsNegativeIntensity);\n"
" }"
;


#endif




GPUImageRGBDilationFilter::GPUImageRGBDilationFilter()
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _rgbDilationRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _rgbDilationRadiusOne_fragment_shader)
{

}

GPUImageRGBDilationFilter::GPUImageRGBDilationFilter(int radius)
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _rgbDilationRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _rgbDilationRadiusOne_fragment_shader)

{
    const char* vertexShaderForThisRadius = NULL;
    const char* fragmentShaderForThisRadius = NULL;
    switch (radius)
    {
        case 0:
        case 1:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _rgbDilationRadiusOne_fragment_shader;
            break;
        }
        case 2:
        {
            vertexShaderForThisRadius = _dilationRadiusTwo_vertex_shader;
            fragmentShaderForThisRadius = _rgbDilationRadiusTwo_fragment_shader;
            break;
        }
        case 3:
        {
            vertexShaderForThisRadius = _dilationRadiusThree_vertex_shader;
            fragmentShaderForThisRadius = _rgbDilationRadiusThree_fragment_shader;
            break;
        }
        case 4:
        {
            vertexShaderForThisRadius = _dilationRadiusFour_vertex_shader;
            fragmentShaderForThisRadius = _rgbDilationRadiusFour_fragment_shader;
            break;
        }
        default:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _rgbDilationRadiusOne_fragment_shader;
            break;
        }
    }

    resetShader(vertexShaderForThisRadius, fragmentShaderForThisRadius, vertexShaderForThisRadius, fragmentShaderForThisRadius);
}

GPUImageRGBDilationFilter::~GPUImageRGBDilationFilter()
{

}

