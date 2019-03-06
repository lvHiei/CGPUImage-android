/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMonochromeFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _monochrome_fragment_shader[] = SHADER_STR(
    precision lowp float;

    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform float intensity;
    uniform vec3 filterColor;

    const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main()
    {
        //desat, then apply overlay blend
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        float luminance = dot(textureColor.rgb, luminanceWeighting);

        lowp vec4 desat = vec4(vec3(luminance), 1.0);

        //overlay
        lowp vec4 outputColor = vec4(
                (desat.r < 0.5 ? (2.0 * desat.r * filterColor.r) : (1.0 - 2.0 * (1.0 - desat.r) * (1.0 - filterColor.r))),
                (desat.g < 0.5 ? (2.0 * desat.g * filterColor.g) : (1.0 - 2.0 * (1.0 - desat.g) * (1.0 - filterColor.g))),
                (desat.b < 0.5 ? (2.0 * desat.b * filterColor.b) : (1.0 - 2.0 * (1.0 - desat.b) * (1.0 - filterColor.b))),
                1.0
        );

        //which is better, or are they equal?
        gl_FragColor = vec4( mix(textureColor.rgb, outputColor.rgb, intensity), textureColor.a);
    }
);


#else


// 片元着色器
extern const char _monochrome_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float intensity;
 uniform vec3 filterColor;

 const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

 void main()
 {
     //desat, then apply overlay blend
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
     float luminance = dot(textureColor.rgb, luminanceWeighting);

     vec4 desat = vec4(vec3(luminance), 1.0);

     //overlay
     vec4 outputColor = vec4(
             (desat.r < 0.5 ? (2.0 * desat.r * filterColor.r) : (1.0 - 2.0 * (1.0 - desat.r) * (1.0 - filterColor.r))),
             (desat.g < 0.5 ? (2.0 * desat.g * filterColor.g) : (1.0 - 2.0 * (1.0 - desat.g) * (1.0 - filterColor.g))),
             (desat.b < 0.5 ? (2.0 * desat.b * filterColor.b) : (1.0 - 2.0 * (1.0 - desat.b) * (1.0 - filterColor.b))),
             1.0
     );

     //which is better, or are they equal?
     gl_FragColor = vec4( mix(textureColor.rgb, outputColor.rgb, intensity), textureColor.a);
 }
);


#endif


GPUImageMonochromeFilter::GPUImageMonochromeFilter()
    : GPUImageFilter(_monochrome_fragment_shader)
{
    m_fIntensity = 1.0f;

    m_iIntensityUniformLocation = -1;
    m_iColorUniformLocation = -1;

    m_pColor[0] = 0.6f;
    m_pColor[1] = 0.45f;
    m_pColor[2] = 0.3f;
}

GPUImageMonochromeFilter::~GPUImageMonochromeFilter()
{

}

void GPUImageMonochromeFilter::setIntensity(float intensity)
{
    m_fIntensity = intensity;
}

void GPUImageMonochromeFilter::setIntensity(int percent)
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
    setIntensity(value);
}

void GPUImageMonochromeFilter::setColorRed(float red, float green, float blue)
{
    m_pColor[0] = red;
    m_pColor[1] = green;
    m_pColor[2] = blue;
}

bool GPUImageMonochromeFilter::createProgramExtra()
{
    m_iIntensityUniformLocation = glGetUniformLocation(m_uProgram, "intensity");
    m_iColorUniformLocation = glGetUniformLocation(m_uProgram, "filterColor");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageMonochromeFilter::beforeDrawExtra()
{
    glUniform1f(m_iIntensityUniformLocation, m_fIntensity);
    glUniform3fv(m_iColorUniformLocation, 1, m_pColor);
    return GPUImageFilter::beforeDrawExtra();
}

