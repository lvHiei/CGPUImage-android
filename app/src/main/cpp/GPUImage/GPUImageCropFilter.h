/**
 * Created by mj on 17-5-8.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGECROPFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGECROPFILTER_H


#include "GPUImageFilter.h"

struct GLRect{
    GLRect(){
        this->x = 0.0f;
        this->y = 0.0f;
        this->width = 1.0f;
        this->height = 1.0f;
    }

    GLRect(float a, float b, float w, float h){
        this->x = a;
        this->y = b;
        this->width = w;
        this->height = h;
    }
    float x;
    float y;
    float width;
    float height;
};

class GPUImageCropFilter : public GPUImageFilter{
public:
    GPUImageCropFilter();
    GPUImageCropFilter(GLRect rect);
    virtual ~GPUImageCropFilter();

    void setCropRegion(GLRect newRect);

    virtual void setTextureCoordinate(float *textureCoordinate);

    virtual void setTextureRotation(Rotation rotation);

    virtual bool draw(GLuint textureId, int viewWidth, int viewHeight);

protected:
    void calculateCropTextureCoordinates();

    float getMaxX();
    float getMaxY();

protected:
    GLRect m_cropRect;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGECROPFILTER_H
