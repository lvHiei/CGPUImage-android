/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageChromaKeyFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _chromakey_fragment_shader[]=
"precision highp float;\n"
"\n"
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform float thresholdSensitivity;\n"
"uniform float smoothing;\n"
"uniform vec3 colorToReplace;\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    float maskY = 0.2989 * colorToReplace.r + 0.5866 * colorToReplace.g + 0.1145 * colorToReplace.b;\n"
"    float maskCr = 0.7132 * (colorToReplace.r - maskY);\n"
"    float maskCb = 0.5647 * (colorToReplace.b - maskY);\n"
"\n"
"    float Y = 0.2989 * textureColor.r + 0.5866 * textureColor.g + 0.1145 * textureColor.b;\n"
"    float Cr = 0.7132 * (textureColor.r - Y);\n"
"    float Cb = 0.5647 * (textureColor.b - Y);\n"
"\n"
"    //     float blendValue = 1.0 - smoothstep(thresholdSensitivity - smoothing, thresholdSensitivity , abs(Cr - maskCr) + abs(Cb - maskCb));\n"
"    float blendValue = smoothstep(thresholdSensitivity, thresholdSensitivity + smoothing, distance(vec2(Cr, Cb), vec2(maskCr, maskCb)));\n"
"    gl_FragColor = vec4(textureColor.rgb, textureColor.a * blendValue);\n"
"}"
;


#else


// 片元着色器
extern const char _chromakey_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform float thresholdSensitivity;\n"
"uniform float smoothing;\n"
"uniform vec3 colorToReplace;\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    float maskY = 0.2989 * colorToReplace.r + 0.5866 * colorToReplace.g + 0.1145 * colorToReplace.b;\n"
"    float maskCr = 0.7132 * (colorToReplace.r - maskY);\n"
"    float maskCb = 0.5647 * (colorToReplace.b - maskY);\n"
"\n"
"    float Y = 0.2989 * textureColor.r + 0.5866 * textureColor.g + 0.1145 * textureColor.b;\n"
"    float Cr = 0.7132 * (textureColor.r - Y);\n"
"    float Cb = 0.5647 * (textureColor.b - Y);\n"
"\n"
"    //     float blendValue = 1.0 - smoothstep(thresholdSensitivity - smoothing, thresholdSensitivity , abs(Cr - maskCr) + abs(Cb - maskCb));\n"
"    float blendValue = smoothstep(thresholdSensitivity, thresholdSensitivity + smoothing, distance(vec2(Cr, Cb), vec2(maskCr, maskCb)));\n"
"    gl_FragColor = vec4(textureColor.rgb, textureColor.a * blendValue);\n"
"}"
;


#endif



GPUImageChromaKeyFilter::GPUImageChromaKeyFilter()
    : GPUImageFilter(_chromakey_fragment_shader)
{
    m_fThresholdSensitivity = 0.4f;
    m_fSmoothing = 0.1f;

    m_pColorToReplace[0] = 0.0f;
    m_pColorToReplace[1] = 1.0f;
    m_pColorToReplace[2] = 0.0f;
}

GPUImageChromaKeyFilter::~GPUImageChromaKeyFilter()
{

}

bool GPUImageChromaKeyFilter::createProgramExtra()
{
    m_iThresholdSensitivityUniformLocation = glGetUniformLocation(m_uProgram, "thresholdSensitivity");
    m_iSmoothingUniformLocation = glGetUniformLocation(m_uProgram, "smoothing");
    m_iColorToReplaceUniformLocation = glGetUniformLocation(m_uProgram, "colorToReplace");

    return true;
}

bool GPUImageChromaKeyFilter::beforeDrawExtra()
{
    glUniform1f(m_iThresholdSensitivityUniformLocation, m_fThresholdSensitivity);
    glUniform1f(m_iSmoothingUniformLocation, m_fSmoothing);
    glUniform3fv(m_iColorToReplaceUniformLocation, 1, m_pColorToReplace);
    return true;
}


void GPUImageChromaKeyFilter::setThresholdSensitivity(float thresholdSensitivity)
{
    m_fThresholdSensitivity = thresholdSensitivity;
}

void GPUImageChromaKeyFilter::setThresholdSensitivity(int percent)
{
    float max = 1.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setThresholdSensitivity(value);
}

void GPUImageChromaKeyFilter::setSmoothing(float smoothing)
{
    m_fSmoothing = smoothing;
}

void GPUImageChromaKeyFilter::setColorToReplace(float red, float green, float blue)
{
    m_pColorToReplace[0] = red;
    m_pColorToReplace[1] = green;
    m_pColorToReplace[2] = blue;
}