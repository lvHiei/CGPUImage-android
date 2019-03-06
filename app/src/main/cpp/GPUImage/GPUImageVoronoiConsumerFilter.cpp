/**
 * Created by lvHiei on 17-5-4.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>
#include "GPUImageVoronoiConsumerFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _voronoiConsumer_fragment_shader[]=SHADER_STR(
    precision highp float;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;
    uniform vec2 size;
    varying vec2 textureCoordinate;

    vec2 getCoordFromColor(vec4 color)
    {
        float z = color.z * 256.0;
        float yoff = floor(z / 8.0);
        float xoff = mod(z, 8.0);
        float x = color.x*256.0 + xoff*256.0;
        float y = color.y*256.0 + yoff*256.0;
        return vec2(x,y) / size;
    }

    void main(void) {
        vec4 colorLoc = texture2D(inputImageTexture2, textureCoordinate);
        vec4 color = texture2D(inputImageTexture, getCoordFromColor(colorLoc));

        gl_FragColor = color;
    }
);

#else

// 片元着色器
extern const char _voronoiConsumer_fragment_shader[]=SHADER_STR(
 precision mediump float;
 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;
 uniform vec2 size;
 varying vec2 textureCoordinate;

 vec2 getCoordFromColor(vec4 color)
 {
     float z = color.z * 256.0;
     float yoff = floor(z / 8.0);
     float xoff = mod(z, 8.0);
     float x = color.x*256.0 + xoff*256.0;
     float y = color.y*256.0 + yoff*256.0;
     return vec2(x,y) / size;
 }

 void main(void)
 {
     vec4 colorLoc = texture2D(inputImageTexture2, textureCoordinate);
     vec4 color = texture2D(inputImageTexture, getCoordFromColor(colorLoc));

     gl_FragColor = color;
 }
);

#endif





GPUImageVoronoiConsumerFilter::GPUImageVoronoiConsumerFilter()
    : GPUImageImageFilter(_voronoiConsumer_fragment_shader)
{
    m_iSizeInPixelsUniformLocation = -1;

    m_pSizeInPixels[0] = 1024;
    m_pSizeInPixels[1] = 1024;
}

GPUImageVoronoiConsumerFilter::~GPUImageVoronoiConsumerFilter() {

}

void GPUImageVoronoiConsumerFilter::setSizeInPixels(int w, int h)
{
    float width = log2(w);
    float height = log2(h);

    if(width != height){
        LOGW("Voronoi point texture must be square");
        return;
    }

    if (width != floor(width) || height != floor(height)) {
        LOGW("Voronoi point texture must be a power of 2.  Texture size %f, %f", w, h);
        return;
    }

    m_pSizeInPixels[0] = w;
    m_pSizeInPixels[1] = h;
}

bool GPUImageVoronoiConsumerFilter::createProgramExtra()
{
    m_iSizeInPixelsUniformLocation = glGetUniformLocation(m_uProgram, "size");
    return GPUImageImageFilter::createProgramExtra();
}

bool GPUImageVoronoiConsumerFilter::beforeDrawExtra()
{
    glUniform2iv(m_iSizeInPixelsUniformLocation, 1, m_pSizeInPixels);
    return GPUImageTwoInputFilter::beforeDrawExtra();
}

bool GPUImageVoronoiConsumerFilter::loadImage()
{
    // this is decode the image of voroni_points2.png.
    // in the example we just use the rgba data stored in
    // the file voroni_points2.rgba.

    const char* filename = "voroni_points2.rgba";

    m_uPicWidth = 1024;
    m_uPicHeight = 1024;
    uint32_t fileLen = FileUtil::getFileSize(filename);
    if(fileLen > 0){
        m_pPicDataRGBA = (uint8_t *) malloc(fileLen * sizeof(uint8_t));
        if(!m_pPicDataRGBA){
            return false;
        }

        FileUtil::loadFile(filename, m_pPicDataRGBA, fileLen);
    }

    return true;
}

