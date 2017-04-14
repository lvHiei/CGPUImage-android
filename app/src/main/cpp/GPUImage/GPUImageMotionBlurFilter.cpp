/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageMotionBlurFilter.h"


// 顶点着色器
const char _motionBlur_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"
"\n"
"uniform vec2 directionalTexelStep;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 oneStepBackTextureCoordinate;\n"
"varying vec2 twoStepsBackTextureCoordinate;\n"
"varying vec2 threeStepsBackTextureCoordinate;\n"
"varying vec2 fourStepsBackTextureCoordinate;\n"
"varying vec2 oneStepForwardTextureCoordinate;\n"
"varying vec2 twoStepsForwardTextureCoordinate;\n"
"varying vec2 threeStepsForwardTextureCoordinate;\n"
"varying vec2 fourStepsForwardTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = position;\n"
"\n"
"    textureCoordinate = inputTextureCoordinate.xy;\n"
"    oneStepBackTextureCoordinate = inputTextureCoordinate.xy - directionalTexelStep;\n"
"    twoStepsBackTextureCoordinate = inputTextureCoordinate.xy - 2.0 * directionalTexelStep;\n"
"    threeStepsBackTextureCoordinate = inputTextureCoordinate.xy - 3.0 * directionalTexelStep;\n"
"    fourStepsBackTextureCoordinate = inputTextureCoordinate.xy - 4.0 * directionalTexelStep;\n"
"    oneStepForwardTextureCoordinate = inputTextureCoordinate.xy + directionalTexelStep;\n"
"    twoStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 2.0 * directionalTexelStep;\n"
"    threeStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 3.0 * directionalTexelStep;\n"
"    fourStepsForwardTextureCoordinate = inputTextureCoordinate.xy + 4.0 * directionalTexelStep;\n"
"}"
;



// 片元着色器
const char _motionBlur_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 oneStepBackTextureCoordinate;\n"
"varying vec2 twoStepsBackTextureCoordinate;\n"
"varying vec2 threeStepsBackTextureCoordinate;\n"
"varying vec2 fourStepsBackTextureCoordinate;\n"
"varying vec2 oneStepForwardTextureCoordinate;\n"
"varying vec2 twoStepsForwardTextureCoordinate;\n"
"varying vec2 threeStepsForwardTextureCoordinate;\n"
"varying vec2 fourStepsForwardTextureCoordinate;\n"
"\n"
"void main()\n"
"{\n"
"    // Box weights\n"
"    //     vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.1111111;\n"
"    //     fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.1111111;\n"
"\n"
"    vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepBackTextureCoordinate) * 0.15;\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsBackTextureCoordinate) *  0.12;\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsBackTextureCoordinate) * 0.09;\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsBackTextureCoordinate) * 0.05;\n"
"    fragmentColor += texture2D(inputImageTexture, oneStepForwardTextureCoordinate) * 0.15;\n"
"    fragmentColor += texture2D(inputImageTexture, twoStepsForwardTextureCoordinate) *  0.12;\n"
"    fragmentColor += texture2D(inputImageTexture, threeStepsForwardTextureCoordinate) * 0.09;\n"
"    fragmentColor += texture2D(inputImageTexture, fourStepsForwardTextureCoordinate) * 0.05;\n"
"\n"
"    gl_FragColor = fragmentColor;\n"
"}"
;


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

