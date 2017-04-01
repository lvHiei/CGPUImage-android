/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_LOGUTIL_H_H
#define CGPUIMAGE_LOGUTIL_H_H

#ifdef __ANDROID__GPUIMAGE__

#include <android/log.h>

#define TAG "CGPUImage"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

#else

#include <stdio.h>
#define LOGD printf
#define LOGI printf
#define LOGW printf
#define LOGE printf
#define LOGF printf

#endif


#endif //CGPUIMAGE_LOGUTIL_H_H
