/**
 * Created by lvHiei on 17-4-7.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageCGAColorspaceFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _CGAColorspace_fragment_shader[]=
"varying highp vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    highp vec2 sampleDivisor = vec2(1.0 / 200.0, 1.0 / 320.0);\n"
"    //highp vec4 colorDivisor = vec4(colorDepth);\n"
"\n"
"    highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor);\n"
"    highp vec4 color = texture2D(inputImageTexture, samplePos );\n"
"\n"
"    //gl_FragColor = texture2D(inputImageTexture, samplePos );\n"
"    mediump vec4 colorCyan = vec4(85.0 / 255.0, 1.0, 1.0, 1.0);\n"
"    mediump vec4 colorMagenta = vec4(1.0, 85.0 / 255.0, 1.0, 1.0);\n"
"    mediump vec4 colorWhite = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    mediump vec4 colorBlack = vec4(0.0, 0.0, 0.0, 1.0);\n"
"\n"
"    mediump vec4 endColor;\n"
"    highp float blackDistance = distance(color, colorBlack);\n"
"    highp float whiteDistance = distance(color, colorWhite);\n"
"    highp float magentaDistance = distance(color, colorMagenta);\n"
"    highp float cyanDistance = distance(color, colorCyan);\n"
"\n"
"    mediump vec4 finalColor;\n"
"\n"
"    highp float colorDistance = min(magentaDistance, cyanDistance);\n"
"    colorDistance = min(colorDistance, whiteDistance);\n"
"    colorDistance = min(colorDistance, blackDistance);\n"
"\n"
"    if (colorDistance == blackDistance) {\n"
"        finalColor = colorBlack;\n"
"    } else if (colorDistance == whiteDistance) {\n"
"        finalColor = colorWhite;\n"
"    } else if (colorDistance == cyanDistance) {\n"
"        finalColor = colorCyan;\n"
"    } else {\n"
"        finalColor = colorMagenta;\n"
"    }\n"
"\n"
"    gl_FragColor = finalColor;\n"
"}"
;

#else

// 片元着色器
extern const char _CGAColorspace_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"void main()\n"
"{\n"
"    vec2 sampleDivisor = vec2(1.0 / 200.0, 1.0 / 320.0);\n"
"    //highp vec4 colorDivisor = vec4(colorDepth);\n"
"\n"
"    vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor);\n"
"    vec4 color = texture2D(inputImageTexture, samplePos );\n"
"\n"
"    //gl_FragColor = texture2D(inputImageTexture, samplePos );\n"
"    vec4 colorCyan = vec4(85.0 / 255.0, 1.0, 1.0, 1.0);\n"
"    vec4 colorMagenta = vec4(1.0, 85.0 / 255.0, 1.0, 1.0);\n"
"    vec4 colorWhite = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    vec4 colorBlack = vec4(0.0, 0.0, 0.0, 1.0);\n"
"\n"
"    vec4 endColor;\n"
"    float blackDistance = distance(color, colorBlack);\n"
"    float whiteDistance = distance(color, colorWhite);\n"
"    float magentaDistance = distance(color, colorMagenta);\n"
"    float cyanDistance = distance(color, colorCyan);\n"
"\n"
"    vec4 finalColor;\n"
"\n"
"    float colorDistance = min(magentaDistance, cyanDistance);\n"
"    colorDistance = min(colorDistance, whiteDistance);\n"
"    colorDistance = min(colorDistance, blackDistance);\n"
"\n"
"    if (colorDistance == blackDistance) {\n"
"        finalColor = colorBlack;\n"
"    } else if (colorDistance == whiteDistance) {\n"
"        finalColor = colorWhite;\n"
"    } else if (colorDistance == cyanDistance) {\n"
"        finalColor = colorCyan;\n"
"    } else {\n"
"        finalColor = colorMagenta;\n"
"    }\n"
"\n"
"    gl_FragColor = finalColor;\n"
"}"
;

#endif






GPUImageCGAColorspaceFilter::GPUImageCGAColorspaceFilter()
    : GPUImageFilter(_CGAColorspace_fragment_shader)
{

}

GPUImageCGAColorspaceFilter::~GPUImageCGAColorspaceFilter()
{

}