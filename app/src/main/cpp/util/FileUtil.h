/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_FILEUTIL_H
#define CGPUIMAGE_ANDROID_FILEUTIL_H


#include <stdint.h>

#include "const.h"

class FileUtil {
public:
    static uint32_t getFileSize(const char* filename);
    static bool loadFile(const char* filename, uint8_t* data, int length);
    static bool loadABSFile(const char* absfilename, uint8_t* data, int length);

private:
    static const char* getFileAbsPath(const char* filename);

private:
    static char m_pABSFILE[ABS_FLIE_LEN_MAX];
};


#endif //CGPUIMAGE_ANDROID_FILEUTIL_H
