/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMedianFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _median_fragment_shader[]=
"precision highp float;\n"
"\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"#define s2(a, b)\t\t\t\ttemp = a; a = min(a, b); b = max(temp, b);\n"
"#define mn3(a, b, c)\t\t\ts2(a, b); s2(a, c);\n"
"#define mx3(a, b, c)\t\t\ts2(b, c); s2(a, c);\n"
"\n"
"#define mnmx3(a, b, c)\t\t\tmx3(a, b, c); s2(a, b);                                   // 3 exchanges\n"
"#define mnmx4(a, b, c, d)\t\ts2(a, b); s2(c, d); s2(a, c); s2(b, d);                   // 4 exchanges\n"
"#define mnmx5(a, b, c, d, e)\ts2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e);           // 6 exchanges\n"
"#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); mn3(a, b, c); mx3(d, e, f); // 7 exchanges\n"
"\n"
"void main()\n"
"{\n"
"    vec3 v[6];\n"
"\n"
"    v[0] = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;\n"
"    v[1] = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;\n"
"    v[2] = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;\n"
"    v[3] = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;\n"
"    v[4] = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    v[5] = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"//     v[6] = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"//     v[7] = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"    vec3 temp;\n"
"\n"
"    mnmx6(v[0], v[1], v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"\n"
"    mnmx5(v[1], v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"\n"
"    mnmx4(v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, textureCoordinate).rgb;\n"
"\n"
"    mnmx3(v[3], v[4], v[5]);\n"
"\n"
"    gl_FragColor = vec4(v[4], 1.0);\n"
"}"
;

#else


// 片元着色器
extern const char _median_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"varying vec2 leftTextureCoordinate;\n"
"varying vec2 rightTextureCoordinate;\n"
"\n"
"varying vec2 topTextureCoordinate;\n"
"varying vec2 topLeftTextureCoordinate;\n"
"varying vec2 topRightTextureCoordinate;\n"
"\n"
"varying vec2 bottomTextureCoordinate;\n"
"varying vec2 bottomLeftTextureCoordinate;\n"
"varying vec2 bottomRightTextureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"\n"
"#define s2(a, b)                temp = a; a = min(a, b); b = max(temp, b);\n"
"#define mn3(a, b, c)            s2(a, b); s2(a, c);\n"
"#define mx3(a, b, c)            s2(b, c); s2(a, c);\n"
"\n"
"#define mnmx3(a, b, c)          mx3(a, b, c); s2(a, b);                                   // 3 exchanges\n"
"#define mnmx4(a, b, c, d)       s2(a, b); s2(c, d); s2(a, c); s2(b, d);                   // 4 exchanges\n"
"#define mnmx5(a, b, c, d, e)    s2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e);           // 6 exchanges\n"
"#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); mn3(a, b, c); mx3(d, e, f); // 7 exchanges\n"
"\n"
"void main()\n"
"{\n"
"    vec3 v[6];\n"
"\n"
"    v[0] = texture2D(inputImageTexture, bottomLeftTextureCoordinate).rgb;\n"
"    v[1] = texture2D(inputImageTexture, topRightTextureCoordinate).rgb;\n"
"    v[2] = texture2D(inputImageTexture, topLeftTextureCoordinate).rgb;\n"
"    v[3] = texture2D(inputImageTexture, bottomRightTextureCoordinate).rgb;\n"
"    v[4] = texture2D(inputImageTexture, leftTextureCoordinate).rgb;\n"
"    v[5] = texture2D(inputImageTexture, rightTextureCoordinate).rgb;\n"
"    //     v[6] = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"    //     v[7] = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"    vec3 temp;\n"
"\n"
"    mnmx6(v[0], v[1], v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, bottomTextureCoordinate).rgb;\n"
"\n"
"    mnmx5(v[1], v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, topTextureCoordinate).rgb;\n"
"\n"
"    mnmx4(v[2], v[3], v[4], v[5]);\n"
"\n"
"    v[5] = texture2D(inputImageTexture, textureCoordinate).rgb;\n"
"\n"
"    mnmx3(v[3], v[4], v[5]);\n"
"\n"
"    gl_FragColor = vec4(v[4], 1.0);\n"
"}"
;

#endif



GPUImageMedianFilter::GPUImageMedianFilter()
    : GPUImage3x3TextureSamplingFilter(_median_fragment_shader)
{

}

GPUImageMedianFilter::~GPUImageMedianFilter()
{

}