/**
 * Created by lvHiei on 17-4-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_TEXTUREROTATEUTIL_H
#define CGPUIMAGE_ANDROID_TEXTUREROTATEUTIL_H


#include "const.h"

class TextureRotateUtil {
public:
    static float* getTextureCoordinate(Rotation rotation, bool flipHorizontal, bool flipVertical);

private:
    static float flip(float x);

private:
    static float m_pTextureCoordinate[8];
};


#endif //CGPUIMAGE_ANDROID_TEXTUREROTATEUTIL_H
