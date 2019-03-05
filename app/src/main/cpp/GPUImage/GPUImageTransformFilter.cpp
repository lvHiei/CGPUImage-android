//
// Created by mj on 19-3-5.
//

#include "GPUImageTransformFilter.h"


// 顶点着色器
extern const char _transfrom_vertex_shader[] = SHADER_STR(
//    precision mediump float;
attribute vec4 position;
attribute vec4 inputTextureCoordinate;

varying vec2 textureCoordinate;

uniform mat4 transformMatrix;

void main()
{
    gl_Position = transformMatrix * position;
    textureCoordinate = inputTextureCoordinate.xy;
}
);


// 片元着色器
extern const char _transfrom_fragment_shader[] = SHADER_STR(
precision mediump float;
uniform sampler2D inputImageTexture;
varying vec2 textureCoordinate;

void main()
{
    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
    gl_FragColor = textureColor;
}
);


GPUImageTransformFilter::GPUImageTransformFilter()
        : GPUImageFilter(_transfrom_vertex_shader, _transfrom_fragment_shader)
{
    m_iTransUnionLocation = -1;
    reset();
}

GPUImageTransformFilter::~GPUImageTransformFilter() {

}

bool GPUImageTransformFilter::createProgramExtra() {
    m_iTransUnionLocation = glGetUniformLocation(m_uProgram, "transformMatrix");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageTransformFilter::beforeDrawExtra() {
    updateMatrix();
//    glUniformMatrix4fv(m_iTransUnionLocation, 1, GL_FALSE, &mTransformMatrix[0][0]);
    glUniformMatrix4fv(m_iTransUnionLocation, 1, GL_FALSE, (const GLfloat *) mTransformMatrix);
    return GPUImageFilter::beforeDrawExtra();
}

void GPUImageTransformFilter::reset() {
    mat4x4_identity(mTransformMatrix);
    mat4x4_identity(mTranslateMatrix);
    mat4x4_identity(mScaleMatrix);
    mat4x4_identity(mRotateMatrix);
}

void GPUImageTransformFilter::setTranslate(float x, float y) {
    setTranslate(x, y, 0.0f);
}

void GPUImageTransformFilter::setTranslate(float x, float y, float z) {
    mat4x4_identity(mTranslateMatrix);
    mat4x4_translate(mTranslateMatrix, x, y, z);
}

void GPUImageTransformFilter::setScale(float s) {
    if(VERTEX_COORDINATE_SIZE == 8){
        setScale(s, s);
    }else{
        setScale(s, s, s);
    }
}

void GPUImageTransformFilter::setScale(float x, float y) {
    setScale(x, y, 1.0f);
}

void GPUImageTransformFilter::setScale(float x, float y, float z) {
    mat4x4_identity(mScaleMatrix);
    mat4x4_scale_aniso(mScaleMatrix, mScaleMatrix, x, y, z);
}

void GPUImageTransformFilter::setRotate(float angle, float x, float y, float z) {
    mat4x4_identity(mRotateMatrix);
    mat4x4_rotate(mRotateMatrix, mRotateMatrix, x, y, z, angle);
}

void GPUImageTransformFilter::updateMatrix() {
    // 先旋转 在缩放 在平移
    mat4x4_identity(mTransformMatrix);
    mat4x4_mul(mTransformMatrix, mScaleMatrix, mRotateMatrix);
    mat4x4_mul(mTransformMatrix, mTranslateMatrix, mTransformMatrix);
}
