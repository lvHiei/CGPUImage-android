/**
 * Created by lvHiei on 17-4-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <string.h>
#include "TextureRotateUtil.h"

float TEXTURE_NO_ROTATION[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
};

float TEXTURE_ROTATED_90[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
};

float TEXTURE_ROTATED_180[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
};

float TEXTURE_ROTATED_270[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};


float TextureRotateUtil::m_pTextureCoordinate[] = {
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
};

float* TextureRotateUtil::getTextureCoordinate(Rotation rotation, bool flipHorizontal, bool flipVertical)
{
    switch (rotation){
        case ROTATION_90:
            memcpy(m_pTextureCoordinate, TEXTURE_ROTATED_90, 8*sizeof(float));
            break;
        case ROTATION_180:
            memcpy(m_pTextureCoordinate, TEXTURE_ROTATED_180, 8*sizeof(float));
            break;
        case ROTATION_270:
            memcpy(m_pTextureCoordinate, TEXTURE_ROTATED_270, 8*sizeof(float));
            break;
        case ROTATION_NORMAL:
        default:
            memcpy(m_pTextureCoordinate, TEXTURE_NO_ROTATION, 8*sizeof(float));
            break;
    }

    if (flipHorizontal) {
        for(int i = 0; i < 8; i = i + 2){
            m_pTextureCoordinate[i] = flip(m_pTextureCoordinate[i]);
        }
    }

    if (flipVertical) {
        for(int i = 1; i < 8; i = i + 2){
            m_pTextureCoordinate[i] = flip(m_pTextureCoordinate[i]);
        }
    }

    return m_pTextureCoordinate;
}

float TextureRotateUtil::flip(float x)
{
    if(0.0f== x){
        return 1.0f;
    }
    return 0.0f;
}