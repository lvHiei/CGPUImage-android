/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageMotionBlurFilter.h"


// 顶点着色器
extern const char _motionBlur_vertex_shader[] = SHADER_STR(
// precision mediump float;
    attribute vec4 position;
    attribute vec4 inputTextureCoordinate;

    uniform vec2 directionalTexelStep;

    varying vec2 textureCoordinate;
    varying vec2 oneStepBackTextureCoordinate;
    varying vec2 twoStepsBackTextureCoordinate;
    varying vec2 threeStepsBackTextureCoordinate;
    varying vec2 fourStepsBackTextureCoordinate;
    varying vec2 oneStepForwardTextureCoordinate;
    varying vec2 twoStepsForwardTextureCoordinate;
    varying vec2 threeStepsForwardTextureCoordinate;
    varying vec2 fourStepsForwardTextureCoordinate;

    void main()
    {
        gl_Position = position;

        textureCoordinate = inputTextureCoordinate.xy;
        oneStepBackTextureCoordinate = inputTextureCoordinate.xy - directionalTexelStep;
        twoStepsBackTextureCoordinate = inputTextureCoordinate.xy - 2.0 * directionalTexelStep;
        threeStepsBackTextureCoordinate = inputTextureCoordinate.xy - 3.0 * directionalTexelStep;
        fourStepsBackTextureCoordinate = inputTextureCoordinate.xy - 4.0 * directionalTexelStep;
        oneStepForwardTextureCoordinate = inputTextureCoordinate.xy + directionalTexelStep;
        twoStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 2.0 * directionalTexelStep;
        threeStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 3.0 * directionalTexelStep;
        fourStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 4.0 * directionalTexelStep;
    }
);

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
const char _motionBlur_fragment_shader[] = SHADER_STR(
    precision highp float;

    uniform sampler2D inputImageTexture;

    varying vec2 textureCoordinate;
    varying vec2 oneStepBackTextureCoordinate;
    varying vec2 twoStepsBackTextureCoordinate;
    varying vec2 threeStepsBackTextureCoordinate;
    varying vec2 fourStepsBackTextureCoordinate;
    varying vec2 oneStepForwardTextureCoordinate;
    varying vec2 twoStepsForwardTextureCoordinate;
    varying vec2 threeStepsForwardTextureCoordinate;
    varying vec2 fourStepsForwardTextureCoordinate;

    void main()
    {
        // Box weights
        //     lowp vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.1111111;
        //     fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.1111111;

        lowp vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;
        fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.15;
        fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) *  0.12;
        fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.09;
        fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.05;
        fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.15;
        fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) *  0.12;
        fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.09;
        fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.05;

        gl_FragColor = fragmentColor;
    }
);

#else

// 片元着色器
const char _motionBlur_fragment_shader[] = SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;

 varying vec2 textureCoordinate;
 varying vec2 oneStepBackTextureCoordinate;
 varying vec2 twoStepsBackTextureCoordinate;
 varying vec2 threeStepsBackTextureCoordinate;
 varying vec2 fourStepsBackTextureCoordinate;
 varying vec2 oneStepForwardTextureCoordinate;
 varying vec2 twoStepsForwardTextureCoordinate;
 varying vec2 threeStepsForwardTextureCoordinate;
 varying vec2 fourStepsForwardTextureCoordinate;

 void main()
 {
     // Box weights
     //     vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.1111111;
     //     fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.1111111;

     vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;
     fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.15;
     fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) *  0.12;
     fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.09;
     fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.05;
     fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.15;
     fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) *  0.12;
     fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.09;
     fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.05;

     gl_FragColor = fragmentColor;
 }
);

#endif





GPUImageMotionBlurFilter::GPUImageMotionBlurFilter()
    : GPUImageFilter(_motionBlur_vertex_shader, _motionBlur_fragment_shader)
{
    m_fBlurSize = 2.5f;
    m_fBlurAngle = 0.0f;

    m_iTexelStepUniformLocation = -1;

    resetTexelStep();
}

GPUImageMotionBlurFilter::~GPUImageMotionBlurFilter()
{

}

void GPUImageMotionBlurFilter::setBlurSize(float blurSize)
{
    m_fBlurSize = blurSize;
    resetTexelStep();
}

void GPUImageMotionBlurFilter::setBlurAngle(float blurAngle)
{
    m_fBlurAngle = blurAngle;
    resetTexelStep();
}

bool GPUImageMotionBlurFilter::createProgramExtra()
{
    m_iTexelStepUniformLocation = glGetUniformLocation(m_uProgram, "directionalTexelStep");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageMotionBlurFilter::beforeDrawExtra()
{
    glUniform2fv(m_iTexelStepUniformLocation, 1, m_pTexelStep);
    return GPUImageFilter::beforeDrawExtra();
}


void GPUImageMotionBlurFilter::resetTexelStep()
{
    int texwidth = 1280;
    int texheight = 720;

    if(0 != m_iTextureWidth){
        texwidth = m_iTextureWidth;
    }

    if(0 != m_iTextureHeight){
        texwidth = m_iTextureHeight;
    }

    if(m_fBlurAngle == 90 || m_fBlurAngle == 270)
    {
        float aspectRatio = 1.0 * texwidth / texheight;
        m_pTexelStep[0] = m_fBlurSize * sin(m_fBlurAngle * M_PI / 180.0) * aspectRatio / texheight;
        m_pTexelStep[1] = m_fBlurSize * cos(m_fBlurAngle * M_PI / 180.0) / texheight;
    }
    else{
        float aspectRatio = 1.0 * texheight / texwidth;
        m_pTexelStep[0] = m_fBlurSize * sin(m_fBlurAngle * M_PI / 180.0) * aspectRatio / texwidth;
        m_pTexelStep[1] = m_fBlurSize * cos(m_fBlurAngle * M_PI / 180.0) / texwidth;
    }
}

