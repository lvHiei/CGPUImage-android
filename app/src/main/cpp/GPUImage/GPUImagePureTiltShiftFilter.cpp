/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePureTiltShiftFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _pureTiltShift_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    uniform highp float topFocusLevel;
    uniform highp float bottomFocusLevel;
    uniform highp float focusFallOffRate;

    void main()
    {
//     lowp vec4 sharpImageColor = texture2D(inputImageTexture2, textureCoordinate2);
//     lowp vec4 blurredImageColor = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);
        lowp vec4 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2);

        lowp float blurIntensity = 1.0 - smoothstep(topFocusLevel - focusFallOffRate, topFocusLevel, textureCoordinate2.y);
        blurIntensity += smoothstep(bottomFocusLevel, bottomFocusLevel + focusFallOffRate, textureCoordinate2.y);

        gl_FragColor = mix(sharpImageColor, blurredImageColor, blurIntensity);
    }
);

#else

// 片元着色器
extern const char _pureTiltShift_fragment_shader[] = SHADER_STR(
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 uniform float topFocusLevel;
 uniform float bottomFocusLevel;
 uniform float focusFallOffRate;

 void main()
 {
     vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);
     vec4 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2);

     float blurIntensity = 1.0 - smoothstep(topFocusLevel - focusFallOffRate, topFocusLevel, textureCoordinate2.y);
     blurIntensity += smoothstep(bottomFocusLevel, bottomFocusLevel + focusFallOffRate, textureCoordinate2.y);

     gl_FragColor = mix(sharpImageColor, blurredImageColor, blurIntensity);
 }
);

#endif



GPUImagePureTiltShiftFilter::GPUImagePureTiltShiftFilter()
    : GPUImageTwoInputFilter(_pureTiltShift_fragment_shader)
{
    m_fTopFocusLevel = 0.4f;
    m_fBottomFocusLevel = 0.6f;
    m_fFocusFallOffRate = 0.2f;

    m_iTopFocusLevelUniformLocation = -1;
    m_iBottomFocusLevelUniformLocation = -1;
    m_iFocusFallOffRateUniformLocation = -1;
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



