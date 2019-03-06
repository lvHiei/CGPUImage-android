/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageHazeFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _haze_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform lowp float hazeDistance;
    uniform highp float slope;

    void main()
    {
        //todo reconsider precision modifiers\t
        highp vec4 color = vec4(1.0);//todo reimplement as a parameter

        highp float  d = textureCoordinate.y * slope  +  hazeDistance;

        highp vec4 c = texture2D(inputImageTexture, textureCoordinate) ; // consider using unpremultiply

        c = (c - d * color) / (1.0 -d);

        gl_FragColor = c; //consider using premultiply(c);
    }
);

#else

// 片元着色器
extern const char _haze_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 uniform float hazeDistance;
 uniform float slope;

 void main()
 {
     //todo reconsider precision modifiers
     vec4 color = vec4(1.0);//todo reimplement as a parameter

     float  d = textureCoordinate.y * slope  +  hazeDistance;

     vec4 c = texture2D(inputImageTexture, textureCoordinate) ; // consider using unpremultiply

     c = (c - d * color) / (1.0 -d);

     gl_FragColor = c; //consider using premultiply(c);
 }
);

#endif




GPUImageHazeFilter::GPUImageHazeFilter()
    : GPUImageFilter(_haze_fragment_shader)
{

    m_fDistance = 0.0f;
    m_fSlope = 0.0f;

//    m_fDistance = 0.2f;
//    m_fSlope = 0.0f;

    m_iDistanceUniformLocation = -1;
    m_iSlopeUniformLocation = -1;
}

GPUImageHazeFilter::~GPUImageHazeFilter() {

}

void GPUImageHazeFilter::setDistance(float distance)
{
    m_fDistance = distance;
}

void GPUImageHazeFilter::setSlope(float slope)
{
    m_fSlope = slope;
}

void GPUImageHazeFilter::setDistance(int percent)
{
    float max = 0.3f;
    float min = -0.3f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setDistance(value);
}

void GPUImageHazeFilter::setSlope(int percent)
{
    float max = 0.3f;
    float min = -0.3f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setSlope(value);
}

bool GPUImageHazeFilter::createProgramExtra()
{
    m_iDistanceUniformLocation = glGetUniformLocation(m_uProgram, "hazeDistance");
    m_iSlopeUniformLocation = glGetUniformLocation(m_uProgram, "slope");
    return true;
}

bool GPUImageHazeFilter::beforeDrawExtra()
{
    glUniform1f(m_iDistanceUniformLocation, m_fDistance);
    glUniform1f(m_iSlopeUniformLocation, m_fSlope);
    return true;
}



