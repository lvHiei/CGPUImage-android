/**
* Created by lvHiei on 17-5-3.
* This is a project of GPUImage implemented with c++, you can
* use it free. if you find some bug please send me a email.
* My Email is majun_1523@163.com.
*/

#include "GPUImageErosionFilter.h"



extern const char _dilationRadiusOne_vertex_shader[];
extern const char _dilationRadiusTwo_vertex_shader[];
extern const char _dilationRadiusThree_vertex_shader[];
extern const char _dilationRadiusFour_vertex_shader[];


// 片元着色器
extern const char _erosionRadiusOne_fragment_shader[]=
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
"    float minValue = min(centerIntensity, oneStepPositiveIntensity);\n"
"    minValue = min(minValue, oneStepNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(minValue), 1.0);\n"
"}"
;

// 片元着色器
extern const char _erosionRadiusTwo_fragment_shader[]=
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
"    float minValue = min(centerIntensity, oneStepPositiveIntensity);\n"
"    minValue = min(minValue, oneStepNegativeIntensity);\n"
"    minValue = min(minValue, twoStepsPositiveIntensity);\n"
"    minValue = min(minValue, twoStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(minValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _erosionRadiusThree_fragment_shader[]=
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
"    float minValue = min(centerIntensity, oneStepPositiveIntensity);\n"
"    minValue = min(minValue, oneStepNegativeIntensity);\n"
"    minValue = min(minValue, twoStepsPositiveIntensity);\n"
"    minValue = min(minValue, twoStepsNegativeIntensity);\n"
"    minValue = min(minValue, threeStepsPositiveIntensity);\n"
"    minValue = min(minValue, threeStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(minValue), 1.0);\n"
"}"
;


// 片元着色器
extern const char _erosionRadiusFour_fragment_shader[]=
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
"    float minValue = min(centerIntensity, oneStepPositiveIntensity);\n"
"    minValue = min(minValue, oneStepNegativeIntensity);\n"
"    minValue = min(minValue, twoStepsPositiveIntensity);\n"
"    minValue = min(minValue, twoStepsNegativeIntensity);\n"
"    minValue = min(minValue, threeStepsPositiveIntensity);\n"
"    minValue = min(minValue, threeStepsNegativeIntensity);\n"
"    minValue = min(minValue, fourStepsPositiveIntensity);\n"
"    minValue = min(minValue, fourStepsNegativeIntensity);\n"
"\n"
"    gl_FragColor = vec4(vec3(minValue), 1.0);\n"
"}"
;


GPUImageErosionFilter::GPUImageErosionFilter()
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _erosionRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _erosionRadiusOne_fragment_shader)
{

}

GPUImageErosionFilter::GPUImageErosionFilter(int radius)
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _erosionRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _erosionRadiusOne_fragment_shader)
{
    const char* vertexShaderForThisRadius = NULL;
    const char* fragmentShaderForThisRadius = NULL;
    switch (radius)
    {
        case 0:
        case 1:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _erosionRadiusOne_fragment_shader;
            break;
        }
        case 2:
        {
            vertexShaderForThisRadius = _dilationRadiusTwo_vertex_shader;
            fragmentShaderForThisRadius = _erosionRadiusTwo_fragment_shader;
            break;
        }
        case 3:
        {
            vertexShaderForThisRadius = _dilationRadiusThree_vertex_shader;
            fragmentShaderForThisRadius = _erosionRadiusThree_fragment_shader;
            break;
        }
        case 4:
        {
            vertexShaderForThisRadius = _dilationRadiusFour_vertex_shader;
            fragmentShaderForThisRadius = _erosionRadiusFour_fragment_shader;
            break;
        }
        default:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _erosionRadiusOne_fragment_shader;
            break;
        }
    }

    resetShader(vertexShaderForThisRadius, fragmentShaderForThisRadius, vertexShaderForThisRadius, fragmentShaderForThisRadius);
}

GPUImageErosionFilter::~GPUImageErosionFilter() {

}



