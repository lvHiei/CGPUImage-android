/**
 * Created by lvHiei on 17-4-6.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <stdio.h>
#include <string.h>
#include "FileUtil.h"

char FileUtil::m_pABSFILE[] = {0};

const char* CGPUIMAGE_FILE_PATH = "/sdcard/cgpuimage/";


uint32_t FileUtil::getFileSize(const char *filename)
{
    uint32_t fileLen = 0;
    const char* absfile = getFileAbsPath(filename);

    FILE* pFile = fopen(absfile, "rb");
    if(!pFile){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    fileLen = ftell(pFile);
    fclose(pFile);

    return fileLen;
}

bool FileUtil::loadFile(const char *filename, uint8_t *data, int length)
{
    if(!filename || !data){
        return false;
    }

    const char* absFile = getFileAbsPath(filename);
    return loadABSFile(absFile, data, length);
}


bool FileUtil::loadABSFile(const char *absfilename, uint8_t *data, int length)
{
    if(!absfilename || !data){
        return false;
    }

    FILE* pFile = fopen(absfilename, "rb");
    if(!pFile){
        return false;
    }

    fread(data, 1, length, pFile);

    fclose(pFile);
    return true;
}


const char* FileUtil::getFileAbsPath(const char *filename)
{
    memset(m_pABSFILE, 0, ABS_FLIE_LEN_MAX);

    strcpy(m_pABSFILE, CGPUIMAGE_FILE_PATH);
    strcat(m_pABSFILE, filename);
    return m_pABSFILE;
}