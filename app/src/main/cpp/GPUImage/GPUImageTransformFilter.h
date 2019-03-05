//
// Created by mj on 19-3-5.
//

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETRANSFORMFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETRANSFORMFILTER_H

#include "../util/linmath.h"
#include "GPUImageFilter.h"

class GPUImageTransformFilter : public GPUImageFilter {
public:
    GPUImageTransformFilter();
    virtual ~GPUImageTransformFilter();

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

public:
    /**
     * 恢复单位矩阵，删除转换参数
     */
    void reset();

    /**
     * 设置平移参数
     * @param x x方向平移参数
     * @param y y方向平移参数
     * @param z z方向平移参数
     */
    void setTranslate(float x, float y);
    void setTranslate(float x, float y, float z);

    /**
     * 设置缩放参数
     * @param s 缩放比例
     */
    void setScale(float s);

    /**
     * 设置缩放参数
     * @param x x方向缩放比例
     * @param y y方向缩放比例
     * @param z z方向缩放比例
     */
    void setScale(float x, float y);
    void setScale(float x, float y, float z);

    /**
     * 设置旋转参数
     * @param angle 旋转角度 单位 度数
     * @param x     旋转轴的x分量
     * @param y     旋转轴的y分量
     * @param z     旋转轴的z分量
     */
    void setRotate(float angle, float x, float y, float z);

    void updateMatrix();

private:
    mat4x4 mTransformMatrix;
    mat4x4 mTranslateMatrix;
    mat4x4 mScaleMatrix;
    mat4x4 mRotateMatrix;
    GLint m_iTransUnionLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETRANSFORMFILTER_H
