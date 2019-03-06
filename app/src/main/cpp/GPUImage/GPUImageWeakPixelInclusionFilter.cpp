/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageWeakPixelInclusionFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _weakPixelInclusion_fragment_shader[] = SHADER_STR(
    precision lowp float;

    varying vec2 textureCoordinate;
    varying vec2 leftTextureCoordinate;
    varying vec2 rightTextureCoordinate;

    varying vec2 topTextureCoordinate;
    varying vec2 topLeftTextureCoordinate;
    varying vec2 topRightTextureCoordinate;

    varying vec2 bottomTextureCoordinate;
    varying vec2 bottomLeftTextureCoordinate;
    varying vec2 bottomRightTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
        float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
        float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
        float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
        float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;

        float pixelIntensitySum = bottomLeftIntensity + topRightIntensity + topLeftIntensity + bottomRightIntensity + leftIntensity + rightIntensity + bottomIntensity + topIntensity + centerIntensity;
        float sumTest = step(1.5, pixelIntensitySum);
        float pixelTest = step(0.01, centerIntensity);

        gl_FragColor = vec4(vec3(sumTest * pixelTest), 1.0);
    }
);

#else


// 片元着色器
extern const char _weakPixelInclusion_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 varying vec2 leftTextureCoordinate;
 varying vec2 rightTextureCoordinate;

 varying vec2 topTextureCoordinate;
 varying vec2 topLeftTextureCoordinate;
 varying vec2 topRightTextureCoordinate;

 varying vec2 bottomTextureCoordinate;
 varying vec2 bottomLeftTextureCoordinate;
 varying vec2 bottomRightTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
     float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
     float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;

     float pixelIntensitySum = bottomLeftIntensity + topRightIntensity + topLeftIntensity + bottomRightIntensity + leftIntensity + rightIntensity + bottomIntensity + topIntensity + centerIntensity;
     float sumTest = step(1.5, pixelIntensitySum);
     float pixelTest = step(0.01, centerIntensity);

     gl_FragColor = vec4(vec3(sumTest * pixelTest), 1.0);
 }
);

#endif



GPUImageWeakPixelInclusionFilter::GPUImageWeakPixelInclusionFilter()
    : GPUImage3x3TextureSamplingFilter(_weakPixelInclusion_fragment_shader)
{

}

GPUImageWeakPixelInclusionFilter::~GPUImageWeakPixelInclusionFilter()
{

}