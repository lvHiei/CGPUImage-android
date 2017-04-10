/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLevelsFilter.h"


#define GammaCorrection(color, gamma)								pow(color, 1.0 / gamma)

/*
 ** Levels control (input (+gamma), output)
 ** Details: http://blog.mouaif.org/2009/01/28/levels-control-shader/
 */

#define LevelsControlInputRange(color, minInput, maxInput)				min(max(color - minInput, vec3(0.0)) / (maxInput - minInput), vec3(1.0))
#define LevelsControlInput(color, minInput, gamma, maxInput)				GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
#define LevelsControlOutputRange(color, minOutput, maxOutput) 			mix(minOutput, maxOutput, color)
#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) 	LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)


// 片元着色器
const char _levels_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform vec3 levelMinimum;\n"
"uniform vec3 levelMiddle;\n"
"uniform vec3 levelMaximum;\n"
"uniform vec3 minOutput;\n"
"uniform vec3 maxOutput;\n"
"\n"
"#define GammaCorrection(color, gamma)\t\t\t\t\t\t\t\tpow(color, 1.0 / gamma)\n"
"\n"
"/*\n"
" ** Levels control (input (+gamma), output)\n"
" ** Details: http://blog.mouaif.org/2009/01/28/levels-control-shader/\n"
" */\n"
"\n"
"#define LevelsControlInputRange(color, minInput, maxInput)\t\t\t\tmin(max(color - minInput, vec3(0.0)) / (maxInput - minInput), vec3(1.0))\n"
"#define LevelsControlInput(color, minInput, gamma, maxInput)\t\t\t\tGammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)\n"
"#define LevelsControlOutputRange(color, minOutput, maxOutput) \t\t\tmix(minOutput, maxOutput, color)\n"
"#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) \tLevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)\n"
""
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    gl_FragColor = vec4(LevelsControl(textureColor.rgb, levelMinimum, levelMiddle, levelMaximum, minOutput, maxOutput), textureColor.a);\n"
"}"
;


GPUImageLevelsFilter::GPUImageLevelsFilter()
    : GPUImageFilter(_levels_fragment_shader)
{
    m_iMaxOutputVectorUniformLocation = -1;
    m_iMinOutputVectorUniformLocation = -1;
    m_iMaxVectorUniformLocation = -1;
    m_iMinVectorUniformLocation = -1;
    m_iMidVectorUniformLocation = -1;

    setRedMin(0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    setGreenMin(0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    setBlueMin(0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
}

GPUImageLevelsFilter::~GPUImageLevelsFilter()
{

}

void GPUImageLevelsFilter::setRedMin(float min, float mid, float max, float minOut, float maxOut)
{
    m_pMinVector[0] = min;
    m_pMidVector[0] = mid;
    m_pMaxVector[0] = max;
    m_pMinOutputVector[0] = minOut;
    m_pMaxOutputVector[0] = maxOut;
}

void GPUImageLevelsFilter::setRedMin(float min, float mid, float max)
{
    setRedMin(min, mid, max, 0.0f, 1.0f);
}

void GPUImageLevelsFilter::setGreenMin(float min, float mid, float max, float minOut,
                                       float maxOut)
{
    m_pMinVector[1] = min;
    m_pMidVector[1] = mid;
    m_pMaxVector[1] = max;
    m_pMinOutputVector[1] = minOut;
    m_pMaxOutputVector[1] = maxOut;
}

void GPUImageLevelsFilter::setGreenMin(float min, float mid, float max)
{
    setGreenMin(min, mid, max, 0.0f, 1.0f);
}

void GPUImageLevelsFilter::setBlueMin(float min, float mid, float max, float minOut, float maxOut)
{
    m_pMinVector[2] = min;
    m_pMidVector[2] = mid;
    m_pMaxVector[2] = max;
    m_pMinOutputVector[2] = minOut;
    m_pMaxOutputVector[2] = maxOut;
}

void GPUImageLevelsFilter::setBlueMin(float min, float mid, float max)
{
    setBlueMin(min, mid, max, 0.0f, 1.0f);
}

void GPUImageLevelsFilter::setMin(float min, float mid, float max, float minOut, float maxOut)
{
    setRedMin(min, mid, max, minOut, maxOut);
    setGreenMin(min, mid, max, minOut, maxOut);
    setBlueMin(min, mid, max, minOut, maxOut);
}

void GPUImageLevelsFilter::setMin(float min, float mid, float max)
{
    setMin(min, mid, max, 0.0f, 1.0f);
}

bool GPUImageLevelsFilter::createProgramExtra()
{
    m_iMinVectorUniformLocation = glGetUniformLocation(m_uProgram, "levelMinimum");
    m_iMidVectorUniformLocation = glGetUniformLocation(m_uProgram, "levelMiddle");
    m_iMaxVectorUniformLocation = glGetUniformLocation(m_uProgram, "levelMaximum");
    m_iMinOutputVectorUniformLocation = glGetUniformLocation(m_uProgram, "minOutput");
    m_iMaxOutputVectorUniformLocation = glGetUniformLocation(m_uProgram, "maxOutput");
    return true;
}

bool GPUImageLevelsFilter::beforeDrawExtra()
{
    glUniform3fv(m_iMinVectorUniformLocation, 1, m_pMinVector);
    glUniform3fv(m_iMidVectorUniformLocation, 1, m_pMidVector);
    glUniform3fv(m_iMaxVectorUniformLocation, 1, m_pMaxVector);
    glUniform3fv(m_iMinOutputVectorUniformLocation, 1, m_pMinOutputVector);
    glUniform3fv(m_iMaxOutputVectorUniformLocation, 1, m_pMaxOutputVector);

    return true;
}

