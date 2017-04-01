#include <jni.h>
#include <string>

#include "NativeRender.h"

NativeRender* g_pRender = NULL;

extern "C"
jstring
Java_com_lvhiei_cgpuimage_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
bool
Java_com_lvhiei_cgpuimage_CGPUImageRender_nativeCreateFilter(
        JNIEnv *env,
        jobject, int filter ) {

    if(NULL == g_pRender){
        g_pRender = new NativeRender();
    }

    return g_pRender->createFilter(filter);
}


extern "C"
bool
Java_com_lvhiei_cgpuimage_CGPUImageRender_nativeDraw(
        JNIEnv *env, jobject, int textureId, int viewWidth, int viewHeight) {

    if(NULL == g_pRender){
        return false;
    }

    return g_pRender->draw(textureId, viewWidth, viewHeight);
}


extern "C"
void
Java_com_lvhiei_cgpuimage_MainActivity_nativeSetFrontCamera(
        JNIEnv *env, jobject, jboolean isfront) {

    if(NULL == g_pRender){
        return ;
    }

    g_pRender->setFrontCamera(isfront);
}