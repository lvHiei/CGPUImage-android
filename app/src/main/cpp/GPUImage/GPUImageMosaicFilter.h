/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEMOSAICFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEMOSAICFILTER_H


#include "GPUImageImageFilter.h"
#include "../util/const.h"

// This needs a little more work, it's rotating the input tileset and there are some artifacts (I think from GL_LINEAR interpolation), but it's working
class GPUImageMosaicFilter : public GPUImageImageFilter{
public:
    GPUImageMosaicFilter();
    virtual ~GPUImageMosaicFilter();

    void setColorOn(bool colorOn);
    void setDisplaySize(float x, float y);
    void setDisplaySize(int percent);
    void setNumTiles(float numTiles);
    void setTileSet(const char* tileSet);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

    virtual bool loadImage();

protected:

    //  This filter takes an input tileset, the tiles must ascend in luminance
    //  It looks at the input image and replaces each display tile with an input tile
    //  according to the luminance of that tile.  The idea was to replicate the ASCII
    //  video filters seen in other apps, but the tileset can be anything.
    GLfloat m_pInputTileSize[2];
    GLfloat m_pDisplayTileSize[2];
    GLfloat m_fNumTiles;
    GLboolean m_bColorOn;
    GLchar m_pTileSet[ABS_FLIE_LEN_MAX];

    GLint m_iInputTileSizeUniformLocation;
    GLint m_iDisplayTileSizeUniformLocation;
    GLint m_iNumTilesUniformLocation;
    GLint m_iColorOnUniformLocation;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEMOSAICFILTER_H
