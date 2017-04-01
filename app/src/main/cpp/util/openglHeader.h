/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */



#ifndef CGPUIMAGE_OPENGLHEADER_H_H
#define CGPUIMAGE_OPENGLHEADER_H_H

// this include the opengl header
// my test project is android, so I use Android GLES2
//#ifdef __ANDROID__GPUIMAGE__
#if 1

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else


#endif

#endif //CGPUIMAGE_OPENGLHEADER_H_H
