/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePerlinNoiseFilter.h"


// 片元着色器
const char _perlinNoise_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"uniform float scale;\n"
"\n"
"uniform vec4 colorStart;\n"
"uniform vec4 colorFinish;\n"
"\n"
"//\n"
"// Description : Array and textureless GLSL 2D/3D/4D simplex\n"
"// noise functions.\n"
"// Author : Ian McEwan, Ashima Arts.\n"
"// Maintainer : ijm\n"
"// Lastmod : 20110822 (ijm)\n"
"// License : Copyright (C) 2011 Ashima Arts. All rights reserved.\n"
"// Distributed under the MIT License. See LICENSE file.\n"
"// https://github.com/ashima/webgl-noise\n"
"//\n"
"\n"
"vec4 mod289(vec4 x)\n"
"{\n"
"return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
"}\n"
"\n"
"vec4 permute(vec4 x)\n"
"{\n"
"return mod289(((x*34.0)+1.0)*x);\n"
"}\n"
"\n"
"vec4 taylorInvSqrt(vec4 r)\n"
"{\n"
"return 1.79284291400159 - 0.85373472095314 * r;\n"
"}\n"
"\n"
"vec2 fade(vec2 t) {\n"
"return t*t*t*(t*(t*6.0-15.0)+10.0);\n"
"}\n"
"\n"
"// Classic Perlin noise\n"
"float cnoise(vec2 P)\n"
"{\n"
"vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);\n"
"vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);\n"
"Pi = mod289(Pi); // To avoid truncation effects in permutation\n"
"vec4 ix = Pi.xzxz;\n"
"vec4 iy = Pi.yyww;\n"
"vec4 fx = Pf.xzxz;\n"
"vec4 fy = Pf.yyww;\n"
"\n"
"vec4 i = permute(permute(ix) + iy);\n"
"\n"
"vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;\n"
"vec4 gy = abs(gx) - 0.5 ;\n"
"vec4 tx = floor(gx + 0.5);\n"
"gx = gx - tx;\n"
"\n"
"vec2 g00 = vec2(gx.x,gy.x);\n"
"vec2 g10 = vec2(gx.y,gy.y);\n"
"vec2 g01 = vec2(gx.z,gy.z);\n"
"vec2 g11 = vec2(gx.w,gy.w);\n"
"\n"
"vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));\n"
"g00 *= norm.x;\n"
"g01 *= norm.y;\n"
"g10 *= norm.z;\n"
"g11 *= norm.w;\n"
"\n"
"float n00 = dot(g00, vec2(fx.x, fy.x));\n"
"float n10 = dot(g10, vec2(fx.y, fy.y));\n"
"float n01 = dot(g01, vec2(fx.z, fy.z));\n"
"float n11 = dot(g11, vec2(fx.w, fy.w));\n"
"\n"
"vec2 fade_xy = fade(Pf.xy);\n"
"vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);\n"
"float n_xy = mix(n_x.x, n_x.y, fade_xy.y);\n"
"return 2.3 * n_xy;\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"\n"
"    float n1 = (cnoise(textureCoordinate * scale) + 1.0) / 2.0;\n"
"\n"
"    vec4 colorDiff = colorFinish - colorStart;\n"
"    vec4 color = colorStart + colorDiff * n1;\n"
"\n"
"    gl_FragColor = color;\n"
"}"
;


GPUImagePerlinNoiseFilter::GPUImagePerlinNoiseFilter()
    : GPUImageFilter(_perlinNoise_fragment_shader)
{
    m_fScale = 8.0f;

    m_pColorStart[0] = 0.0f;
    m_pColorStart[1] = 0.0f;
    m_pColorStart[2] = 0.0f;
    m_pColorStart[3] = 1.0f;

    m_pColorFinish[0] = 1.0f;
    m_pColorFinish[1] = 1.0f;
    m_pColorFinish[2] = 1.0f;
    m_pColorFinish[3] = 1.0f;

    m_iColorStartUniformLocation = -1;
    m_iColorFinishUniformLocation = -1;
    m_iScaleUniformLocation = -1;
}

GPUImagePerlinNoiseFilter::~GPUImagePerlinNoiseFilter()
{

}

void GPUImagePerlinNoiseFilter::setColorStart(float red, float green, float blue, float alpha)
{
    m_pColorStart[0] = red;
    m_pColorStart[1] = green;
    m_pColorStart[2] = blue;
    m_pColorStart[3] = alpha;
}

void GPUImagePerlinNoiseFilter::setColorFinish(float red, float green, float blue, float alpha)
{
    m_pColorFinish[0] = red;
    m_pColorFinish[1] = green;
    m_pColorFinish[2] = blue;
    m_pColorFinish[3] = alpha;
}

void GPUImagePerlinNoiseFilter::setScale(float scale)
{
    m_fScale = scale;
}

bool GPUImagePerlinNoiseFilter::createProgramExtra()
{
    m_iColorStartUniformLocation = glGetUniformLocation(m_uProgram, "colorStart");
    m_iColorFinishUniformLocation = glGetUniformLocation(m_uProgram, "colorFinish");
    m_iScaleUniformLocation = glGetUniformLocation(m_uProgram, "scale");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePerlinNoiseFilter::beforeDrawExtra()
{
    glUniform1f(m_iScaleUniformLocation, m_fScale);
    glUniform4fv(m_iColorStartUniformLocation, 1, m_pColorStart);
    glUniform4fv(m_iColorFinishUniformLocation, 1, m_pColorFinish);

    return GPUImageFilter::beforeDrawExtra();
}




