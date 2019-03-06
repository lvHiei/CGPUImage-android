/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageSkinToneFilter.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _skinTone_fragment_shader[]=SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    // [-1;1] <=> [pink;orange]
    uniform highp float skinToneAdjust; // will make reds more pink

    // Other parameters
    uniform mediump float skinHue;
    uniform mediump float skinHueThreshold;
    uniform mediump float maxHueShift;
    uniform mediump float maxSaturationShift;
    uniform int upperSkinToneColor;

    // RGB <-> HSV conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
    highp vec3 rgb2hsv(highp vec3 c)
    {
        highp vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
        highp vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
        highp vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

        highp float d = q.x - min(q.w, q.y);
        highp float e = 1.0e-10;
        return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
    }

    // HSV <-> RGB conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
    highp vec3 hsv2rgb(highp vec3 c)
    {
        highp vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
        highp vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
        return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    }

    // Main
    void main ()
    {

        // Sample the input pixel
        highp vec4 colorRGB = texture2D(inputImageTexture, textureCoordinate);

        // Convert color to HSV, extract hue
        highp vec3 colorHSV = rgb2hsv(colorRGB.rgb);
        highp float hue = colorHSV.x;

        // check how far from skin hue
        highp float dist = hue - skinHue;
        if (dist > 0.5)
            dist -= 1.0;
        if (dist < -0.5)
            dist += 1.0;
        dist = abs(dist)/0.5; // normalized to [0,1]

        // Apply Gaussian like filter
        highp float weight = exp(-dist*dist*skinHueThreshold);
        weight = clamp(weight, 0.0, 1.0);

        // Using pink/green, so only adjust hue
        if (upperSkinToneColor == 0) {
            colorHSV.x += skinToneAdjust * weight * maxHueShift;
            // Using pink/orange, so adjust hue < 0 and saturation > 0
        } else if (upperSkinToneColor == 1) {
            // We want more orange, so increase saturation
            if (skinToneAdjust > 0.0)
                colorHSV.y += skinToneAdjust * weight * maxSaturationShift;
                // we want more pinks, so decrease hue
            else
                colorHSV.x += skinToneAdjust * weight * maxHueShift;
        }

        // final color
        highp vec3 finalColorRGB = hsv2rgb(colorHSV.rgb);

        // display
        gl_FragColor = vec4(finalColorRGB, 1.0);
    }
);


#else

// 片元着色器
extern const char _skinTone_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;

 // [-1;1] <=> [pink;orange]
 uniform float skinToneAdjust; // will make reds more pink

 // Other parameters
 uniform float skinHue;
 uniform float skinHueThreshold;
 uniform float maxHueShift;
 uniform float maxSaturationShift;
 uniform int upperSkinToneColor;

 // RGB <-> HSV conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
 highp vec3 rgb2hsv(highp vec3 c)
 {
 vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
 vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
 vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

 float d = q.x - min(q.w, q.y);
 float e = 1.0e-10;
 return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
 }

 // HSV <-> RGB conversion, thanks to http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
 highp vec3 hsv2rgb(highp vec3 c)
 {
 vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
 vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
 return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
 }

 // Main
 void main ()
 {

     // Sample the input pixel
     vec4 colorRGB = texture2D(inputImageTexture, textureCoordinate);

     // Convert color to HSV, extract hue
     vec3 colorHSV = rgb2hsv(colorRGB.rgb);
     float hue = colorHSV.x;

     // check how far from skin hue
     float dist = hue - skinHue;
     if (dist > 0.5)
         dist -= 1.0;
     if (dist < -0.5)
         dist += 1.0;
     dist = abs(dist)/0.5; // normalized to [0,1]

     // Apply Gaussian like filter
     float weight = exp(-dist*dist*skinHueThreshold);
     weight = clamp(weight, 0.0, 1.0);

     // Using pink/green, so only adjust hue
     if (upperSkinToneColor == 0) {
         colorHSV.x += skinToneAdjust * weight * maxHueShift;
         // Using pink/orange, so adjust hue < 0 and saturation > 0
     } else if (upperSkinToneColor == 1) {
         // We want more orange, so increase saturation
         if (skinToneAdjust > 0.0)
             colorHSV.y += skinToneAdjust * weight * maxSaturationShift;
             // we want more pinks, so decrease hue
         else
             colorHSV.x += skinToneAdjust * weight * maxHueShift;
     }

     // final color
     vec3 finalColorRGB = hsv2rgb(colorHSV.rgb);

     // display
     gl_FragColor = vec4(finalColorRGB, 1.0);
 }
);


#endif




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


