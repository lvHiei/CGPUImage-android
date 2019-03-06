/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSharpenFilter.h"


// 顶点着色器
extern const char _sharpen_vertex_shader[] = SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    uniform float imageWidthFactor;
    uniform float imageHeightFactor;
    uniform float sharpness;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;
    varying vec2 topTextureCoordinate;
    varying vec2 bottomTextureCoordinate;

    varying float centerMultiplier;
    varying float edgeMultiplier;

    void main()
    {
        gl_Position = position;

        vec2 widthStep = vec2(imageWidthFactor, 0.0);
        vec2 heightStep = vec2(0.0, imageHeightFactor);

        textureCoordinate = inputTextureCoordinate.xy;
        leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;
        rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;
        topTextureCoordinate = inputTextureCoordinate.xy + heightStep;
        bottomTextureCoordinate = inputTextureCoordinate.xy - heightStep;

        centerMultiplier = 1.0 + 4.0 * sharpness;
        edgeMultiplier = sharpness;
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _sharpen_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying highp vec2 textureCoordinate;
    varying highp vec2 leftTextureCoordinate;
    varying highp vec2 rightTextureCoordinate;
    varying highp vec2 topTextureCoordinate;
    varying highp vec2 bottomTextureCoordinate;

    varying highp float centerMultiplier;
    varying highp float edgeMultiplier;

    uniform sampler2D inputImageTexture;

    void main()
    {
        mediump vec3 textureColor = texture2D(inputImageTexture, textureCoordinate).rgb;
        mediump vec3 leftTextureColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
        mediump vec3 rightTextureColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
        mediump vec3 topTextureColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;
        mediump vec3 bottomTextureColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;

        gl_FragColor = vec4((textureColor * centerMultiplier - (leftTextureColor * edgeMultiplier + rightTextureColor * edgeMultiplier + topTextureColor * edgeMultiplier + bottomTextureColor * edgeMultiplier)), texture2D(inputImageTexture, bottomTextureCoordinate).w);
    }
);

#else


// 片元着色器
extern const char _sharpen_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;
 varying vec2 topTextureCoordinate;
 varying vec2 bottomTextureCoordinate;

 varying float centerMultiplier;
 varying float edgeMultiplier;

 uniform sampler2D inputImageTexture;

 void main()
 {
     vec3 textureColor = texture2D(inputImageTexture, textureCoordinate).rgb;
     vec3 leftTextureColor = texture2D(inputImageTexture, leftTextureCoordinate).rgb;
     vec3 rightTextureColor = texture2D(inputImageTexture, rightTextureCoordinate).rgb;
     vec3 topTextureColor = texture2D(inputImageTexture, topTextureCoordinate).rgb;
     vec3 bottomTextureColor = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;

     gl_FragColor = vec4((textureColor * centerMultiplier - (leftTextureColor * edgeMultiplier + rightTextureColor * edgeMultiplier + topTextureColor * edgeMultiplier + bottomTextureColor * edgeMultiplier)), texture2D(inputImageTexture, bottomTextureCoordinate).w);
 }
);

#endif




GPUImageSharpenFilter::GPUImageSharpenFilter()
    : GPUImageFilter(_sharpen_vertex_shader, _sharpen_fragment_shader)
{
    updateTexelWidthHeight();
    m_fSharpness = 0.0f;

    m_iImageHeightFactorUniformLocation = -1;
    m_iImageWidthFactorUniformLocation = -1;
    m_iSharpnessUniformLocation = -1;
}

GPUImageSharpenFilter::~GPUImageSharpenFilter()
{

}

void GPUImageSharpenFilter::setImageWidthFactor(float width)
{
    m_fImageWidthFactor = width;
}

void GPUImageSharpenFilter::setImageHeightFactor(float height)
{
    m_fImageHeightFactor = height;
}

void GPUImageSharpenFilter::setSharpness(float sharpness)
{
    m_fSharpness = sharpness;
}

void GPUImageSharpenFilter::setSharpness(int percent)
{
    float max = 4.0f;
    float min = -4.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setSharpness(value);
}

bool GPUImageSharpenFilter::createProgramExtra() {
    m_iImageWidthFactorUniformLocation = glGetUniformLocation(m_uProgram, "imageWidthFactor");
    m_iImageHeightFactorUniformLocation = glGetUniformLocation(m_uProgram, "imageHeightFactor");
    m_iSharpnessUniformLocation = glGetUniformLocation(m_uProgram, "sharpness");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageSharpenFilter::beforeDrawExtra() {
    glUniform1f(m_iImageWidthFactorUniformLocation, m_fImageWidthFactor);
    glUniform1f(m_iImageHeightFactorUniformLocation, m_fImageHeightFactor);
    glUniform1f(m_iSharpnessUniformLocation, m_fSharpness);

    return GPUImageFilter::beforeDrawExtra();
}


void GPUImageSharpenFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelWidthHeight();
}

void GPUImageSharpenFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelWidthHeight();
}

void GPUImageSharpenFilter::updateTexelWidthHeight()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fImageWidthFactor = 1.0 / m_iTextureWidth;
    m_fImageHeightFactor = 1.0 / m_iTextureHeight;
}


