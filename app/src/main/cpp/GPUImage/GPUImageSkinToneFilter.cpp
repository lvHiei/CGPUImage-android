/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSkinToneFilter.h"


// 片元着色器
const char _skinTone_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"// [-1;1] <=> [pink;orange]\n"
"uniform float skinToneAdjust; // will make reds more pink\n"
"\n"
"// Other parameters\n"
"uniform float skinHue;\n"
"uniform float skinHueThreshold;\n"
"uniform float maxHueShift;\n"
"uniform float maxSaturationShift;\n"
"uniform int upperSkinToneColor;\n"
"\n"
"// RGB <-> HSV conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl\n"
"highp vec3 rgb2hsv(highp vec3 c)\n"
"{\n"
"vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);\n"
"vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));\n"
"vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));\n"
"\n"
"float d = q.x - min(q.w, q.y);\n"
"float e = 1.0e-10;\n"
"return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);\n"
"}\n"
"\n"
"// HSV <-> RGB conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl\n"
"highp vec3 hsv2rgb(highp vec3 c)\n"
"{\n"
"vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);\n"
"vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);\n"
"return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);\n"
"}\n"
"\n"
"// Main\n"
"void main ()\n"
"{\n"
"\n"
"    // Sample the input pixel\n"
"    vec4 colorRGB = texture2D(inputImageTexture, textureCoordinate);\n"
"\n"
"    // Convert color to HSV, extract hue\n"
"    vec3 colorHSV = rgb2hsv(colorRGB.rgb);\n"
"    float hue = colorHSV.x;\n"
"\n"
"    // check how far from skin hue\n"
"    float dist = hue - skinHue;\n"
"    if (dist > 0.5)\n"
"        dist -= 1.0;\n"
"    if (dist < -0.5)\n"
"        dist += 1.0;\n"
"    dist = abs(dist)/0.5; // normalized to [0,1]\n"
"\n"
"    // Apply Gaussian like filter\n"
"    float weight = exp(-dist*dist*skinHueThreshold);\n"
"    weight = clamp(weight, 0.0, 1.0);\n"
"\n"
"    // Using pink/green, so only adjust hue\n"
"    if (upperSkinToneColor == 0) {\n"
"        colorHSV.x += skinToneAdjust * weight * maxHueShift;\n"
"        // Using pink/orange, so adjust hue < 0 and saturation > 0\n"
"    } else if (upperSkinToneColor == 1) {\n"
"        // We want more orange, so increase saturation\n"
"        if (skinToneAdjust > 0.0)\n"
"            colorHSV.y += skinToneAdjust * weight * maxSaturationShift;\n"
"            // we want more pinks, so decrease hue\n"
"        else\n"
"            colorHSV.x += skinToneAdjust * weight * maxHueShift;\n"
"    }\n"
"\n"
"    // final color\n"
"    vec3 finalColorRGB = hsv2rgb(colorHSV.rgb);\n"
"\n"
"    // display\n"
"    gl_FragColor = vec4(finalColorRGB, 1.0);\n"
"}"
;


GPUImageSkinToneFilter::GPUImageSkinToneFilter()
    : GPUImageFilter(_skinTone_fragment_shader)
{

    m_fSkinToneAdjust = 0.0f;
    m_fSkinHue = 0.05f;
    m_fSkinHueThreshold = 40.0f;
    m_fMaxHueShift = 0.25f;
    m_fMaxSaturationShift = 0.4f;
    m_iUpperSkinToneColor = 0;


    m_iSkinToneAdjustUniformLocation = -1;
    m_iSkinHueUniformLocation = -1;
    m_iSkinHueThresholdUniformLocation = -1;
    m_iMaxHueShiftUniformLocation = -1;
    m_iMaxSaturationShiftUniformLocation = -1;
    m_iUpperSkinToneColorUniformLocation = -1;
}

GPUImageSkinToneFilter::~GPUImageSkinToneFilter()
{

}

void GPUImageSkinToneFilter::setSkinToneAdjust(float skinToneAdjust)
{
    m_fSkinToneAdjust = skinToneAdjust;
}

void GPUImageSkinToneFilter::setSkinHue(float skinHue)
{
    m_fSkinHue = skinHue;
}

void GPUImageSkinToneFilter::setSkinHueShreshold(float skinHueThreshold)
{
    m_fSkinHueThreshold = skinHueThreshold;
}

void GPUImageSkinToneFilter::setMaxHueShift(float maxHueShift)
{
    m_fMaxHueShift = maxHueShift;
}

void GPUImageSkinToneFilter::setMaxSaturationShift(float maxSaturationShift)
{
    m_fMaxSaturationShift = maxSaturationShift;
}

void GPUImageSkinToneFilter::setUpperSkinToneColor(int upperSkinToneColor)
{
    m_iUpperSkinToneColor = upperSkinToneColor;
}

bool GPUImageSkinToneFilter::createProgramExtra()
{
    m_iSkinToneAdjustUniformLocation = glGetUniformLocation(m_uProgram, "skinToneAdjust");
    m_iSkinHueUniformLocation = glGetUniformLocation(m_uProgram, "skinHue");
    m_iSkinHueThresholdUniformLocation = glGetUniformLocation(m_uProgram, "skinHueThreshold");
    m_iMaxHueShiftUniformLocation = glGetUniformLocation(m_uProgram, "maxHueShift");
    m_iMaxSaturationShiftUniformLocation = glGetUniformLocation(m_uProgram, "maxSaturationShift");
    m_iUpperSkinToneColorUniformLocation = glGetUniformLocation(m_uProgram, "upperSkinToneColor");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageSkinToneFilter::beforeDrawExtra()
{
    glUniform1f(m_iSkinToneAdjustUniformLocation, m_fSkinToneAdjust);
    glUniform1f(m_iSkinHueUniformLocation, m_fSkinHue);
    glUniform1f(m_iSkinHueThresholdUniformLocation, m_fSkinHueThreshold);
    glUniform1f(m_iMaxHueShiftUniformLocation, m_fMaxHueShift);
    glUniform1f(m_iMaxSaturationShiftUniformLocation, m_fMaxSaturationShift);
    glUniform1i(m_iUpperSkinToneColorUniformLocation, m_iUpperSkinToneColor);

    return GPUImageFilter::beforeDrawExtra();
}


