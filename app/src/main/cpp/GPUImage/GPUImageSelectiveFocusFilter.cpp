/**
 * Created by lvHiei on 17-5-9.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSelectiveFocusFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _selectiveFocus_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;
    varying highp vec2 textureCoordinate2;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    uniform lowp float excludeCircleRadius;
    uniform lowp vec2 excludeCirclePoint;
    uniform lowp float excludeBlurSize;
    uniform highp float aspectRatio;

    void main()
    {
        lowp vec4 sharpImageColor = texture2D(inputImageTexture2, textureCoordinate2);
        lowp vec4 blurredImageColor = texture2D(inputImageTexture, textureCoordinate);

        highp vec2 textureCoordinateToUse = vec2(textureCoordinate2.x, (textureCoordinate2.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
        highp float distanceFromCenter = distance(excludeCirclePoint, textureCoordinateToUse);

        gl_FragColor = mix(sharpImageColor, blurredImageColor, smoothstep(excludeCircleRadius - excludeBlurSize, excludeCircleRadius, distanceFromCenter));
    }
);

#else

// 片元着色器
extern const char _selectiveFocus_fragment_shader[] = SHADER_STR(
 varying vec2 textureCoordinate;
 varying vec2 textureCoordinate2;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 uniform float excludeCircleRadius;
 uniform vec2 excludeCirclePoint;
 uniform float excludeBlurSize;
 uniform float aspectRatio;

 void main()
 {
     vec4 sharpImageColor = texture2D(inputImageTexture2, textureCoordinate2);
     vec4 blurredImageColor = texture2D(inputImageTexture, textureCoordinate);

     vec2 textureCoordinateToUse = vec2(textureCoordinate2.x, (textureCoordinate2.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
     float distanceFromCenter = distance(excludeCirclePoint, textureCoordinateToUse);

     gl_FragColor = mix(sharpImageColor, blurredImageColor, smoothstep(excludeCircleRadius - excludeBlurSize, excludeCircleRadius, distanceFromCenter));
 }
);

#endif




GPUImageSelectiveFocusFilter::GPUImageSelectiveFocusFilter()
    : GPUImageTwoInputFilter(_selectiveFocus_fragment_shader)
{
    m_fExcludeCircleRadius = 60.0f/320.0f;
    m_fExcludeCircleRadius = 40.0f/320.0f;
    m_fExcludeBlurSize = 30.0f/320.0f;

    m_pExcludeCirclePoint[0] = 0.5f;
    m_pExcludeCirclePoint[1] = 0.5f;

    updateAsepctRatio();
}

GPUImageSelectiveFocusFilter::~GPUImageSelectiveFocusFilter()
{

}

void GPUImageSelectiveFocusFilter::setExcludeCircleRadius(float newValue)
{
    m_fExcludeCircleRadius = newValue;
}

void GPUImageSelectiveFocusFilter::setExcludeCirclePoint(float x, float y)
{
    m_pExcludeCirclePoint[0] = x;
    m_pExcludeCirclePoint[1] = y;
}

void GPUImageSelectiveFocusFilter::setExcludeBlurSize(float newValue)
{
    m_fExcludeBlurSize = newValue;
}

void GPUImageSelectiveFocusFilter::setAspectRatio(float newValue)
{
    m_fAspectRatio = newValue;
}

bool GPUImageSelectiveFocusFilter::createProgramExtra()
{
    m_iExcludeCircleRadiusUniformLocation = glGetUniformLocation(m_uProgram, "excludeCircleRadius");
    m_iExcludeCirclePointUniformLocation = glGetUniformLocation(m_uProgram, "excludeCirclePoint");
    m_iExcludeBlurSizeUniformLocation = glGetUniformLocation(m_uProgram, "excludeBlurSize");
    m_iAspectRatioUniformLocation = glGetUniformLocation(m_uProgram, "aspectRatio");

    return GPUImageTwoInputFilter::createProgramExtra();
}

bool GPUImageSelectiveFocusFilter::beforeDrawExtra()
{
    glUniform1f(m_iExcludeCircleRadiusUniformLocation, m_fExcludeCircleRadius);
    glUniform1f(m_iExcludeBlurSizeUniformLocation, m_fExcludeBlurSize);
    glUniform1f(m_iAspectRatioUniformLocation, m_fAspectRatio);
    glUniform2fv(m_iExcludeCirclePointUniformLocation, 1, m_pExcludeCirclePoint);

    return GPUImageTwoInputFilter::beforeDrawExtra();
}


void GPUImageSelectiveFocusFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateAsepctRatio();
}

void GPUImageSelectiveFocusFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateAsepctRatio();
}

void GPUImageSelectiveFocusFilter::updateAsepctRatio()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    m_fAspectRatio = isRotationSwapWidthAndHeight() ?
                     1.0 * m_iTextureHeight / m_iTextureWidth :
                     1.0 * m_iTextureWidth / m_iTextureHeight;
}

