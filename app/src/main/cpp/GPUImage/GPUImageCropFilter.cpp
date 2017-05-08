/**
 * Created by mj on 17-5-8.
 */

#include "GPUImageCropFilter.h"



GPUImageCropFilter::GPUImageCropFilter()
    : GPUImageFilter()
{
//    m_cropRect = GLRect(0.0f, 0.0f, 1.0f, 1.0f);
    m_cropRect = GLRect(0.0f, 0.0f, 1.0f, 0.5f);
}

GPUImageCropFilter::GPUImageCropFilter(GLRect rect)
    : GPUImageFilter()
{
    m_cropRect = rect;
}

GPUImageCropFilter::~GPUImageCropFilter()
{

}

void GPUImageCropFilter::setCropRegion(GLRect newRect)
{
    m_cropRect = newRect;
    calculateCropTextureCoordinates();
}

void GPUImageCropFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    calculateCropTextureCoordinates();
}


void GPUImageCropFilter::calculateCropTextureCoordinates()
{
    float minX = m_cropRect.x;
    float minY = m_cropRect.y;
    float maxX = getMaxX();
    float maxY = getMaxY();

    switch (m_eRotation){
        case ROTATION_NORMAL:
        {
            m_pTextureCoordinate[0] = minX; // 0,0
            m_pTextureCoordinate[1] = minY;

            m_pTextureCoordinate[2] = maxX; // 1,0
            m_pTextureCoordinate[3] = minY;

            m_pTextureCoordinate[4] = minX; // 0,1
            m_pTextureCoordinate[5] = maxY;

            m_pTextureCoordinate[6] = maxX; // 1,1
            m_pTextureCoordinate[7] = maxY;

            break;
        }

        case ROTATION_90:
        {
            m_pTextureCoordinate[0] = maxY; // 1,0
            m_pTextureCoordinate[1] = 1.0 - maxX;

            m_pTextureCoordinate[2] = maxY; // 1,1
            m_pTextureCoordinate[3] = 1.0 - minX;

            m_pTextureCoordinate[4] = minY; // 0,0
            m_pTextureCoordinate[5] = 1.0 - maxX;

            m_pTextureCoordinate[6] = minY; // 0,1
            m_pTextureCoordinate[7] = 1.0 - minX;

//            m_pTextureCoordinate[0] = maxY; // 1,0
//            m_pTextureCoordinate[1] = 1.0 - minX;
//
//            m_pTextureCoordinate[2] = maxY; // 1,1
//            m_pTextureCoordinate[3] = 1.0 - maxX;
//
//            m_pTextureCoordinate[4] = minY; // 0,0
//            m_pTextureCoordinate[5] = 1.0 - minX;
//
//            m_pTextureCoordinate[6] = minY; // 0,1
//            m_pTextureCoordinate[7] = 1.0 - maxX;

            break;
        }

        case ROTATION_270:
        {
//            m_pTextureCoordinate[0] = minY; // 0,1
//            m_pTextureCoordinate[1] = 1.0 - minX;
//
//            m_pTextureCoordinate[2] = minY; // 0,0
//            m_pTextureCoordinate[3] = 1.0 - maxX;
//
//            m_pTextureCoordinate[4] = maxY; // 1,1
//            m_pTextureCoordinate[5] = 1.0 - minX;
//
//            m_pTextureCoordinate[6] = maxY; // 1,0
//            m_pTextureCoordinate[7] = 1.0 - maxX;

            m_pTextureCoordinate[0] = minY; // 0,0
            m_pTextureCoordinate[1] = 1.0 - maxX;

            m_pTextureCoordinate[2] = minY; // 0,1
            m_pTextureCoordinate[3] = 1.0 - minX;

            m_pTextureCoordinate[4] = maxY; // 1,0
            m_pTextureCoordinate[5] = 1.0 - maxX;

            m_pTextureCoordinate[6] = maxY; // 1,1
            m_pTextureCoordinate[7] = 1.0 - minX;

            break;
        }


        case ROTATION_180:
        {
            m_pTextureCoordinate[0] = maxX; // 1,1
            m_pTextureCoordinate[1] = maxY;

            m_pTextureCoordinate[2] = minX; // 0,1
            m_pTextureCoordinate[3] = maxY;

            m_pTextureCoordinate[4] = maxX; // 1,0
            m_pTextureCoordinate[5] = minY;

            m_pTextureCoordinate[6] = minX; // 0,0
            m_pTextureCoordinate[7] = minY;

            break;
        }
    }
}


void GPUImageCropFilter::setTextureCoordinate(float *textureCoordinate)
{
    GPUImageFilter::setTextureCoordinate(textureCoordinate);
    calculateCropTextureCoordinates();
}


float GPUImageCropFilter::getMaxX()
{
    return m_cropRect.width - m_cropRect.x;;
}

float GPUImageCropFilter::getMaxY() {
    return m_cropRect.height - m_cropRect.y;
}


bool GPUImageCropFilter::draw(GLuint textureId, int viewWidth, int viewHeight)
{
    float maxX = getMaxX();
    float maxY = getMaxY();

    float x = viewWidth * (1.0 - maxX) / 2 ;
    float y = viewHeight * (1.0 - maxY) / 2;

    viewWidth = viewWidth * maxX;
    viewHeight = viewHeight * maxY;


    glUseProgram(m_uProgram);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    this->beforeDraw();

    glActiveTexture(GL_TEXTURE0);
    glViewport(x ,y , viewWidth, viewHeight);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glFlush();

    this->onDraw();

    return !checkGLError("draw");
}



