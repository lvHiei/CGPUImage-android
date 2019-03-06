/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSketchFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _sketch_fragment_shader[]=SHADER_STR(
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

    uniform float edgeStrength;

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
        float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
        float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

        float mag = 1.0 - (length(vec2(h, v)) * edgeStrength);

        gl_FragColor = vec4(vec3(mag), 1.0);
    }
);


#else


// 片元着色器
extern const char _sketch_fragment_shader[]=SHADER_STR(
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

 uniform float edgeStrength;

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
     float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
     float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

     float mag = 1.0 - (length(vec2(h, v)) * edgeStrength);

     gl_FragColor = vec4(vec3(mag), 1.0);
 }
);


#endif




GPUImageSketchFilter::GPUImageSketchFilter()
    : GPUImageSobelEdgeDetectionFilter(_sketch_fragment_shader)
{

}

GPUImageSketchFilter::~GPUImageSketchFilter()
{

}

