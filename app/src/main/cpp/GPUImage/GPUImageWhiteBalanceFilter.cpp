/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageWhiteBalanceFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _whiteBalance_fragment_shader[] = SHADER_STR(
    uniform sampler2D inputImageTexture;
    varying highp vec2 textureCoordinate;

    uniform lowp float temperature;
    uniform lowp float tint;

    const lowp vec3 warmFilter = vec3(0.93, 0.54, 0.0);

    const mediump mat3 RGBtoYIQ = mat3(0.299, 0.587, 0.114, 0.596, -0.274, -0.322, 0.212, -0.523, 0.311);
    const mediump mat3 YIQtoRGB = mat3(1.0, 0.956, 0.621, 1.0, -0.272, -0.647, 1.0, -1.105, 1.702);

    void main()
    {
        lowp vec4 source = texture2D(inputImageTexture, textureCoordinate);

        mediump vec3 yiq = RGBtoYIQ * source.rgb; //adjusting tint
        yiq.b = clamp(yiq.b + tint*0.5226*0.1, -0.5226, 0.5226);
        lowp vec3 rgb = YIQtoRGB * yiq;

        lowp vec3 processed = vec3(
                (rgb.r < 0.5 ? (2.0 * rgb.r * warmFilter.r) : (1.0 - 2.0 * (1.0 - rgb.r) * (1.0 - warmFilter.r))), //adjusting temperature
                (rgb.g < 0.5 ? (2.0 * rgb.g * warmFilter.g) : (1.0 - 2.0 * (1.0 - rgb.g) * (1.0 - warmFilter.g))),
                (rgb.b < 0.5 ? (2.0 * rgb.b * warmFilter.b) : (1.0 - 2.0 * (1.0 - rgb.b) * (1.0 - warmFilter.b))));

        gl_FragColor = vec4(mix(rgb, processed, temperature), source.a);
    }
);


#else

// 片元着色器
extern const char _whiteBalance_fragment_shader[] = SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;
 varying vec2 textureCoordinate;

 uniform float temperature;
 uniform float tint;

 const vec3 warmFilter = vec3(0.93, 0.54, 0.0);

 const mat3 RGBtoYIQ = mat3(0.299, 0.587, 0.114, 0.596, -0.274, -0.322, 0.212, -0.523, 0.311);
 const mat3 YIQtoRGB = mat3(1.0, 0.956, 0.621, 1.0, -0.272, -0.647, 1.0, -1.105, 1.702);

 void main()
 {
     vec4 source = texture2D(inputImageTexture, textureCoordinate);

     vec3 yiq = RGBtoYIQ * source.rgb; //adjusting tint
     yiq.b = clamp(yiq.b + tint*0.5226*0.1, -0.5226, 0.5226);
     vec3 rgb = YIQtoRGB * yiq;

     vec3 processed = vec3(
             (rgb.r < 0.5 ? (2.0 * rgb.r * warmFilter.r) : (1.0 - 2.0 * (1.0 - rgb.r) * (1.0 - warmFilter.r))), //adjusting temperature
             (rgb.g < 0.5 ? (2.0 * rgb.g * warmFilter.g) : (1.0 - 2.0 * (1.0 - rgb.g) * (1.0 - warmFilter.g))),
             (rgb.b < 0.5 ? (2.0 * rgb.b * warmFilter.b) : (1.0 - 2.0 * (1.0 - rgb.b) * (1.0 - warmFilter.b))));

     gl_FragColor = vec4(mix(rgb, processed, temperature), source.a);
 }
);


#endif



GPUImageWhiteBalanceFilter::GPUImageWhiteBalanceFilter()
    : GPUImageFilter(_whiteBalance_fragment_shader)
{
//    m_fTemperature = 5000.0f;
    m_fTemperature = 0.0f;
    m_fTint = 0.0f;

    m_iTemperatureUniformLocation = -1;
    m_iTintUniformLocation = -1;
}

GPUImageWhiteBalanceFilter::~GPUImageWhiteBalanceFilter()
{

}

void GPUImageWhiteBalanceFilter::setTemperature(float temperature)
{
    temperature = temperature < 5000.0 ? 0.0004 * (temperature - 5000.0f) : 0.00006f * (temperature - 5000.0f);

    m_fTemperature = temperature;
}

void GPUImageWhiteBalanceFilter::setTint(float tint)
{
    m_fTint = tint;
}


bool GPUImageWhiteBalanceFilter::createProgramExtra()
{
    m_iTemperatureUniformLocation = glGetUniformLocation(m_uProgram, "temperature");
    m_iTintUniformLocation = glGetUniformLocation(m_uProgram, "tint");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageWhiteBalanceFilter::beforeDrawExtra()
{
    glUniform1f(m_iTemperatureUniformLocation, m_fTemperature);
    glUniform1f(m_iTintUniformLocation, m_fTint);
    return GPUImageFilter::beforeDrawExtra();
}



