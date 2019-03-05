//
// Created by mj on 19-3-5.
//

#ifndef CGPUIMAGE_ANDROID_SHADER_H
#define CGPUIMAGE_ANDROID_SHADER_H


#include "openglHeader.h"

class Shader {
public:
    Shader();

public:
    bool createProgram(const char *vertex_shader, const char *fragment_shader);
    GLuint getProgram(){ return m_uProgram;}
    const char* getErrMsg(){return m_errMsg;}

private:
    GLuint m_uProgram;
    char m_errMsg[1024];
};


#endif //CGPUIMAGE_ANDROID_SHADER_H
