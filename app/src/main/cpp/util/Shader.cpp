//
// Created by mj on 19-3-5.
//

#include <stdio.h>
#include <string.h>
#include "Shader.h"


Shader::Shader():
        m_uProgram(0)
{
    memset(m_errMsg, 0, sizeof(m_errMsg));
}

bool Shader::createProgram(const char *vertex_shader, const char *fragment_shader) {

    GLint link_status = 0;
    //编译顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    GLint compile_status = -20;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compile_status);
    if (GL_TRUE != compile_status) {
        GLsizei length = 0;
        GLchar infoLog[1024] = {0};
        glGetShaderInfoLog(vertexShader, 1024, &length, infoLog);

        sprintf(m_errMsg, "compile vertex shader failed, status:%d,info:%s",
                compile_status, infoLog);
//        LOGE("%s", m_errMsg);
        return false;
    }

    // 编译片元着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compile_status);
    if (GL_TRUE != compile_status) {
        GLsizei length = 0;
        GLchar infoLog[1024] = {0};
        glGetShaderInfoLog(fragmentShader, 1024, &length,  infoLog);

        sprintf(m_errMsg, "compile fragment shader failed, status:%d,info:%s",
                compile_status, infoLog);
//        LOGE("%s", m_errMsg);
        return false;
    }

    // 创建应用程序，链接着色器
    m_uProgram = glCreateProgram();
    glAttachShader(m_uProgram, vertexShader);
    glAttachShader(m_uProgram, fragmentShader);
    glLinkProgram(m_uProgram);

    glGetProgramiv(m_uProgram, GL_LINK_STATUS, &link_status);
    if (link_status <= 0) {
        sprintf(m_errMsg, "glLinkProgram failed linkstatus : %d", link_status);
//        LOGE("%s", m_errMsg);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}