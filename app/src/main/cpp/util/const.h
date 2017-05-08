/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_CONST_H
#define CGPUIMAGE_ANDROID_CONST_H

#define __GLSL_SUPPORT_HIGHP__      1

const int ABS_FLIE_LEN_MAX = 1024;

const int VERTEX_COORDINATE_SIZE = 8;
const int TEXTURE_COORDINATE_SIZE = 8;


enum Rotation{
    ROTATION_NORMAL = 0,
    ROTATION_90 = 90,
    ROTATION_180 = 180,
    ROTATION_270 = 270,
};

#endif //CGPUIMAGE_ANDROID_CONST_H
