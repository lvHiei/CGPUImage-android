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


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _erosionRadiusOne_fragment_shader[] = SHADER_STR(
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

        lowp float minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);

        gl_FragColor = vec4(vec3(minValue), 1.0);
    }
);

// 片元着色器
extern const char _erosionRadiusTwo_fragment_shader[] = SHADER_STR(
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

        lowp float minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);
        minValue = min(minValue, twoStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(minValue), 1.0);
    }
);


// 片元着色器
extern const char _erosionRadiusThree_fragment_shader[] = SHADER_STR(
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

        lowp float minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);
        minValue = min(minValue, twoStepsNegativeIntensity);
        minValue = min(minValue, threeStepsPositiveIntensity);
        minValue = min(minValue, threeStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(minValue), 1.0);
    }
);

// 片元着色器
extern const char _erosionRadiusFour_fragment_shader[] = SHADER_STR(
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

        lowp float minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);
        minValue = min(minValue, twoStepsNegativeIntensity);
        minValue = min(minValue, threeStepsPositiveIntensity);
        minValue = min(minValue, threeStepsNegativeIntensity);
        minValue = min(minValue, fourStepsPositiveIntensity);
        minValue = min(minValue, fourStepsNegativeIntensity);

        gl_FragColor = vec4(vec3(minValue), 1.0);
    }
);


#else


// 片元着色器
extern const char _erosionRadiusOne_fragment_shader[] = SHADER_STR(
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

            float minValue = min(centerIntensity, oneStepPositiveIntensity);
            minValue = min(minValue, oneStepNegativeIntensity);

            gl_FragColor = vec4(vec3(minValue), 1.0);
        }
);

// 片元着色器
extern const char _erosionRadiusTwo_fragment_shader[] = SHADER_STR(
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

            float minValue = min(centerIntensity, oneStepPositiveIntensity);
            minValue = min(minValue, oneStepNegativeIntensity);
            minValue = min(minValue, twoStepsPositiveIntensity);
            minValue = min(minValue, twoStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(minValue), 1.0);
        }
);


// 片元着色器
extern const char _erosionRadiusThree_fragment_shader[] = SHADER_STR(
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

            float minValue = min(centerIntensity, oneStepPositiveIntensity);
            minValue = min(minValue, oneStepNegativeIntensity);
            minValue = min(minValue, twoStepsPositiveIntensity);
            minValue = min(minValue, twoStepsNegativeIntensity);
            minValue = min(minValue, threeStepsPositiveIntensity);
            minValue = min(minValue, threeStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(minValue), 1.0);
        }
);


// 片元着色器
extern const char _erosionRadiusFour_fragment_shader[] = SHADER_STR(
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

            float minValue = min(centerIntensity, oneStepPositiveIntensity);
            minValue = min(minValue, oneStepNegativeIntensity);
            minValue = min(minValue, twoStepsPositiveIntensity);
            minValue = min(minValue, twoStepsNegativeIntensity);
            minValue = min(minValue, threeStepsPositiveIntensity);
            minValue = min(minValue, threeStepsNegativeIntensity);
            minValue = min(minValue, fourStepsPositiveIntensity);
            minValue = min(minValue, fourStepsNegativeIntensity);

            gl_FragColor = vec4(vec3(minValue), 1.0);
        }
);


#endif



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



