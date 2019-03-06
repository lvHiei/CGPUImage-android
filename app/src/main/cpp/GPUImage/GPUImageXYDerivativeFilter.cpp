/**
 * Created by lvHiei on 17-4-27.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageXYDerivativeFilter.h"



#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _xyDerivative_fragment_shader[]=SHADER_STR(
    precision highp float;

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

    uniform float edgeStrength;

    void main()
    {
        float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
        float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
        float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
        float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
        float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
        float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
        float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
        float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;

        float verticalDerivative = -topLeftIntensity - topIntensity - topRightIntensity + bottomLeftIntensity + bottomIntensity + bottomRightIntensity;
        float horizontalDerivative = -bottomLeftIntensity - leftIntensity - topLeftIntensity + bottomRightIntensity + rightIntensity + topRightIntensity;
        verticalDerivative = verticalDerivative * edgeStrength;
        horizontalDerivative = horizontalDerivative * edgeStrength;

        // Scaling the X * Y operation so that negative numbers are not clipped in the 0..1 range. This will be expanded in the corner detection filter
        gl_FragColor = vec4(horizontalDerivative * horizontalDerivative, verticalDerivative * verticalDerivative, ((verticalDerivative * horizontalDerivative) + 1.0) / 2.0, 1.0);
    }
);

#else

// 片元着色器
extern const char _xyDerivative_fragment_shader[]=SHADER_STR(
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

 uniform float edgeStrength;

 void main()
 {
     float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
     float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
     float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
     float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
     float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
     float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
     float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
     float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;

     float verticalDerivative = -topLeftIntensity - topIntensity - topRightIntensity + bottomLeftIntensity + bottomIntensity + bottomRightIntensity;
     float horizontalDerivative = -bottomLeftIntensity - leftIntensity - topLeftIntensity + bottomRightIntensity + rightIntensity + topRightIntensity;
     verticalDerivative = verticalDerivative * edgeStrength;
     horizontalDerivative = horizontalDerivative * edgeStrength;

     // Scaling the X * Y operation so that negative numbers are not clipped in the 0..1 range. This will be expanded in the corner detection filter
     gl_FragColor = vec4(horizontalDerivative * horizontalDerivative, verticalDerivative * verticalDerivative, ((verticalDerivative * horizontalDerivative) + 1.0) / 2.0, 1.0);
 }
);

#endif





GPUImageXYDerivativeFilter::GPUImageXYDerivativeFilter()
    : GPUImageSobelEdgeDetectionFilter(_xyDerivative_fragment_shader)
{
    m_fEdgeStrength = 1.0f;
}

GPUImageXYDerivativeFilter::~GPUImageXYDerivativeFilter()
{

}



