/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageTwoPassTextureSamplingFilter.h"


GPUImageTwoPassTextureSamplingFilter::GPUImageTwoPassTextureSamplingFilter(const char *firstVetex,
                                                                           const char *firstFragment,
                                                                           const char *secondVetex,
                                                                           const char *secondFragment)
    : GPUImageTwoPassFilter(firstVetex, firstFragment, secondVetex, secondFragment)
{

    m_f_verticalTexelSpacing = 1.0f;
    m_f_horizontalTexelSpacing = 1.0f;


    m_iVerticalPassTexelWidthOffsetUniform = -1;
    m_iVerticalPassTexelHeightOffsetUniform = -1;
    m_iHorizontalPassTexelWidthOffsetUniform = -1;
    m_iHorizontalPassTexelHeightOffsetUniform = -1;

    updateTexelSize();
}

GPUImageTwoPassTextureSamplingFilter::~GPUImageTwoPassTextureSamplingFilter()
{

}

bool GPUImageTwoPassTextureSamplingFilter::firstCreateProgramExtra()
{
    m_iVerticalPassTexelWidthOffsetUniform = glGetUniformLocation(m_uProgram, "texelWidthOffset");
    m_iVerticalPassTexelHeightOffsetUniform = glGetUniformLocation(m_uProgram, "texelHeightOffset");
    return GPUImageTwoPassFilter::firstCreateProgramExtra();
}

bool GPUImageTwoPassTextureSamplingFilter::secondCreateProgramExtra()
{
    m_iHorizontalPassTexelWidthOffsetUniform = glGetUniformLocation(m_uSecondProgram, "texelWidthOffset");
    m_iHorizontalPassTexelHeightOffsetUniform = glGetUniformLocation(m_uSecondProgram, "texelHeightOffset");
    return GPUImageTwoPassFilter::secondCreateProgramExtra();
}

bool GPUImageTwoPassTextureSamplingFilter::firstBeforeDraw()
{
    glUniform1f(m_iVerticalPassTexelWidthOffsetUniform, m_fVerticalPassTexelWidthOffset);
    glUniform1f(m_iVerticalPassTexelHeightOffsetUniform, m_fVerticalPassTexelHeightOffset);
    return GPUImageTwoPassFilter::firstBeforeDraw();
}

bool GPUImageTwoPassTextureSamplingFilter::secondBeforeDraw()
{
    glUniform1f(m_iHorizontalPassTexelWidthOffsetUniform, m_fHorizontalPassTexelWidthOffset);
    glUniform1f(m_iHorizontalPassTexelHeightOffsetUniform, m_fHorizontalPassTexelHeightOffset);
    return GPUImageTwoPassFilter::secondBeforeDraw();
}


void GPUImageTwoPassTextureSamplingFilter::setVerticalTexelSpacing(float spacing)
{
    m_f_verticalTexelSpacing = spacing;
}

void GPUImageTwoPassTextureSamplingFilter::setHorizontalTexelSpacing(float spacing)
{
    m_f_horizontalTexelSpacing = spacing;
}

void GPUImageTwoPassTextureSamplingFilter::setVerticalPassTexelWidthOffset(float offset)
{
    m_fVerticalPassTexelWidthOffset = offset;
}

void GPUImageTwoPassTextureSamplingFilter::setVerticalPassTexelHeightOffset(float offset)
{
    m_fVerticalPassTexelHeightOffset = offset;
}

void GPUImageTwoPassTextureSamplingFilter::setHorizontalPassTexelWidthOffset(float offset)
{
    m_fHorizontalPassTexelWidthOffset = offset;
}

void GPUImageTwoPassTextureSamplingFilter::setHorizontalPassTexelHeightOffset(float offset)
{
    m_fHorizontalPassTexelHeightOffset = offset;
}

void GPUImageTwoPassTextureSamplingFilter::setTextureSize(int width, int height)
{
    GPUImageFilter::setTextureSize(width, height);
    updateTexelSize();
}

void GPUImageTwoPassTextureSamplingFilter::setTextureRotation(Rotation rotation)
{
    GPUImageFilter::setTextureRotation(rotation);
    updateTexelSize();
}

void GPUImageTwoPassTextureSamplingFilter::updateTexelSize()
{
    if(0 == m_iTextureWidth){
        m_iTextureWidth = 1280;
    }

    if(0 == m_iTextureHeight){
        m_iTextureHeight = 720;
    }

    // The first pass through the framebuffer may rotate the inbound image, so need to account for that by changing up the kernel ordering for that pass
    if(isRotationSwapWidthAndHeight()
       // the first framebuffer will not rotate, the last framebuffer will rotate
       && false
            ){
        m_fVerticalPassTexelWidthOffset = m_f_verticalTexelSpacing / m_iTextureHeight;
        m_fVerticalPassTexelHeightOffset = 0.0f;
    }else{
        m_fVerticalPassTexelWidthOffset = 0.0f;
        m_fVerticalPassTexelHeightOffset = m_f_verticalTexelSpacing / m_iTextureHeight;
    }

    m_fHorizontalPassTexelWidthOffset = m_f_horizontalTexelSpacing / m_iTextureWidth;
    m_fHorizontalPassTexelHeightOffset = 0.0f;
}

