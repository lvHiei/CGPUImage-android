/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePureTiltShiftFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _pureTiltShift_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform highp float topFocusLevel;\n"
"uniform highp float bottomFocusLevel;\n"
"uniform highp float focusFallOffRate;\n"
"\n"
"void main()\n"
"{\n"
//"    lowp vec4 sharpImageColor = texture2D(inputImageTexture2, textureCoordinate2);\n"
//"    lowp vec4 blurredImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    lowp vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    lowp vec4 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    lowp float blurIntensity = 1.0 - smoothstep(topFocusLevel - focusFallOffRate, topFocusLevel, textureCoordinate2.y);\n"
"    blurIntensity += smoothstep(bottomFocusLevel, bottomFocusLevel + focusFallOffRate, textureCoordinate2.y);\n"
"\n"
"    gl_FragColor = mix(sharpImageColor, blurredImageColor, blurIntensity);\n"
"}"
;

#else

// 片元着色器
extern const char _pureTiltShift_fragment_shader[]=
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform float topFocusLevel;\n"
"uniform float bottomFocusLevel;\n"
"uniform float focusFallOffRate;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec4 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2);\n"
"\n"
"    float blurIntensity = 1.0 - smoothstep(topFocusLevel - focusFallOffRate, topFocusLevel, textureCoordinate2.y);\n"
"    blurIntensity += smoothstep(bottomFocusLevel, bottomFocusLevel + focusFallOffRate, textureCoordinate2.y);\n"
"\n"
"    gl_FragColor = mix(sharpImageColor, blurredImageColor, blurIntensity);\n"
"}"
;

#endif



GPUImagePureTiltShiftFilter::GPUImagePureTiltShiftFilter()
    : GPUImageTwoInputFilter(_pureTiltShift_fragment_shader)
{
    m_fTopFocusLevel = 0.4f;
    m_fBottomFocusLevel = 0.6f;
    m_fFocusFallOffRate = 0.2f;
}

GPUImagePureTiltShiftFilter::~GPUImagePureTiltShiftFilter()
{

}

void GPUImagePureTiltShiftFilter::setTopFocusLevel(float newValue)
{
    m_fTopFocusLevel = newValue;
}

void GPUImagePureTiltShiftFilter::setBottomFocusLevel(float newValue)
{
    m_fBottomFocusLevel = newValue;
}

void GPUImagePureTiltShiftFilter::setFocusFallOffRate(float newValue)
{
    m_fFocusFallOffRate = newValue;
}

bool GPUImagePureTiltShiftFilter::createProgramExtra()
{
    m_iTopFocusLevelUniformLocation = glGetUniformLocation(m_uProgram, "topFocusLevel");
    m_iBottomFocusLevelUniformLocation = glGetUniformLocation(m_uProgram, "bottomFocusLevel");
    m_iFocusFallOffRateUniformLocation = glGetUniformLocation(m_uProgram, "focusFallOffRate");

    return GPUImageTwoInputFilter::createProgramExtra();
}

bool GPUImagePureTiltShiftFilter::beforeDrawExtra()
{
    glUniform1f(m_iTopFocusLevelUniformLocation, m_fTopFocusLevel);
    glUniform1f(m_iBottomFocusLevelUniformLocation, m_fBottomFocusLevel);
    glUniform1f(m_iFocusFallOffRateUniformLocation, m_fFocusFallOffRate);

    return GPUImageTwoInputFilter::beforeDrawExtra();
}



