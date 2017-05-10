/**
 * Created by lvHiei on 17-5-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePureUnsharpMaskFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _pureUnsharpMask_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"varying highp vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform highp float intensity;\n"
"\n"
"void main()\n"
"{\n"
"    lowp vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    lowp vec3 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2).rgb;\n"
"\n"
"    gl_FragColor = vec4(sharpImageColor.rgb * intensity + blurredImageColor * (1.0 - intensity), sharpImageColor.a);\n"
"//     gl_FragColor = mix(blurredImageColor, sharpImageColor, intensity);\n"
"//     gl_FragColor = vec4(sharpImageColor.rgb - (blurredImageColor.rgb * intensity), 1.0);\n"
"}"
;

#else

// 片元着色器
extern const char _pureUnsharpMask_fragment_shader[]=
"varying vec2 textureCoordinate;\n"
"varying vec2 textureCoordinate2;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform sampler2D inputImageTexture2;\n"
"\n"
"uniform float intensity;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 sharpImageColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    vec3 blurredImageColor = texture2D(inputImageTexture2, textureCoordinate2).rgb;\n"
"\n"
"    gl_FragColor = vec4(sharpImageColor.rgb * intensity + blurredImageColor * (1.0 - intensity), sharpImageColor.a);\n"
"    //     gl_FragColor = mix(blurredImageColor, sharpImageColor, intensity);\n"
"    //     gl_FragColor = vec4(sharpImageColor.rgb - (blurredImageColor.rgb * intensity), 1.0);\n"
"}"
;

#endif


GPUImagePureUnsharpMaskFilter::GPUImagePureUnsharpMaskFilter()
    : GPUImageTwoInputFilter(_pureUnsharpMask_fragment_shader)
{
    m_fIntensity = 1.0f;

    m_iIntensityUniformLocation = -1;
}

GPUImagePureUnsharpMaskFilter::~GPUImagePureUnsharpMaskFilter()
{

}

void GPUImagePureUnsharpMaskFilter::setIntensity(float intensity)
{
    m_fIntensity = intensity;
}

bool GPUImagePureUnsharpMaskFilter::createProgramExtra()
{
    m_iIntensityUniformLocation = glGetUniformLocation(m_uProgram, "intensity");
    return GPUImageTwoInputFilter::createProgramExtra();
}

bool GPUImagePureUnsharpMaskFilter::beforeDrawExtra()
{
    glUniform1f(m_iIntensityUniformLocation, m_fIntensity);
    return GPUImageTwoInputFilter::beforeDrawExtra();
}

