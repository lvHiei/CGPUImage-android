/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#ifndef CGPUIMAGE_NATIVERENDER_H
#define CGPUIMAGE_NATIVERENDER_H

#include "GPUImage/GPUImageFilter.h"

class NativeRender {
public:
    NativeRender();
    ~NativeRender();

public:
    bool createFilter(int filterType);

    bool draw(int textureId, int viewWidth, int viewHeight);

    bool setFrontCamera(bool front);

private:
    void intenalCreateFilter(int filterType);

private:
    GPUImageFilter* m_pFilter;

    bool m_bFrontCamera;
};


#endif //CGPUIMAGE_NATIVERENDER_H
