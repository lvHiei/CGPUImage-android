/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageZoomBlurFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _zoomBlur_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp vec2 blurCenter;
    uniform highp float blurSize;

    void main()
    {
        // TODO: Do a more intelligent scaling based on resolution here
        highp vec2 samplingOffset = 1.0/100.0 * (blurCenter - textureCoordinate) * blurSize;

        lowp vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate + samplingOffset) * 0.15;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate + (2.0 * samplingOffset)) *  0.12;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate + (3.0 * samplingOffset)) * 0.09;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate + (4.0 * samplingOffset)) * 0.05;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate - samplingOffset) * 0.15;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate - (2.0 * samplingOffset)) *  0.12;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate - (3.0 * samplingOffset)) * 0.09;
        fragmentColor += texture2D(inputImageTexture, textureCoordinate - (4.0 * samplingOffset)) * 0.05;

        gl_FragColor = fragmentColor;
    }
);


#else


// 片元着色器
extern const char _zoomBlur_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform vec2 blurCenter;
 uniform float blurSize;

 void main()
 {
     // TODO: Do a more intelligent scaling based on resolution here
     vec2 samplingOffset = 1.0/100.0 * (blurCenter - textureCoordinate) * blurSize;

     vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate + samplingOffset) * 0.15;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate + (2.0 * samplingOffset)) *  0.12;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate + (3.0 * samplingOffset)) * 0.09;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate + (4.0 * samplingOffset)) * 0.05;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate - samplingOffset) * 0.15;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate - (2.0 * samplingOffset)) *  0.12;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate - (3.0 * samplingOffset)) * 0.09;
     fragmentColor += texture2D(inputImageTexture, textureCoordinate - (4.0 * samplingOffset)) * 0.05;

     gl_FragColor = fragmentColor;
 }
);


#endif


GPUImageZoomBlurFilter::GPUImageZoomBlurFilter()
    : GPUImageFilter(_zoomBlur_fragment_shader)
{
    m_fBlurSize = 1.0f;

    m_pBlurCenter[0] = 0.5f;
    m_pBlurCenter[1] = 0.5f;

    m_iBlurSizeUniformLocation = -1;
    m_iBlurCenterUniformLocation = -1;
}

GPUImageZoomBlurFilter::~GPUImageZoomBlurFilter()
{

}

void GPUImageZoomBlurFilter::setBlurSize(float blursize)
{
    m_fBlurSize = blursize;
}

void GPUImageZoomBlurFilter::setBlurCenter(float x, float y)
{
    m_pBlurCenter[0] = x;
    m_pBlurCenter[1] = y;
}

bool GPUImageZoomBlurFilter::createProgramExtra()
{
    m_iBlurCenterUniformLocation = glGetUniformLocation(m_uProgram, "blurCenter");
    m_iBlurSizeUniformLocation = glGetUniformLocation(m_uProgram, "blurSize");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageZoomBlurFilter::beforeDrawExtra()
{
    glUniform1f(m_iBlurSizeUniformLocation, m_fBlurSize);
    glUniform2fv(m_iBlurCenterUniformLocation, 1, m_pBlurCenter);
    return GPUImageFilter::beforeDrawExtra();
}

