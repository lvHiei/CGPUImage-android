/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageMosaicFilter.h"
#include "../util/FileUtil.h"


#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _mosaic_fragment_shader[]=SHADER_STR(
    precision highp float;

    varying vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture2;

    uniform vec2 inputTileSize;
    uniform vec2 displayTileSize;
    uniform float numTiles;
    uniform int colorOn;

    void main()
    {
        vec2 xy = textureCoordinate;
        xy = xy - mod(xy, displayTileSize);

        vec4 lumcoeff = vec4(0.299,0.587,0.114,0.0);

        vec4 inputColor = texture2D(inputImageTexture2, xy);
        float lum = dot(inputColor,lumcoeff);
        lum = 1.0 - lum;

        float stepsize = 1.0 / numTiles;
        float lumStep = (lum - mod(lum, stepsize)) / stepsize;

        float rowStep = 1.0 / inputTileSize.x;
        float x = mod(lumStep, rowStep);
        float y = floor(lumStep / rowStep);

        vec2 startCoord = vec2(float(x) *  inputTileSize.x, float(y) * inputTileSize.y);
        vec2 finalCoord = startCoord + ((textureCoordinate - xy) * (inputTileSize / displayTileSize));

        vec4 color = texture2D(inputImageTexture, finalCoord);
        if (colorOn == 1) {
            color = color * inputColor;
        }
        gl_FragColor = color;

    }
);

#else


// 片元着色器
extern const char _mosaic_fragment_shader[]=SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform sampler2D inputImageTexture2;

 uniform vec2 inputTileSize;
 uniform vec2 displayTileSize;
 uniform float numTiles;
 uniform int colorOn;

 void main()
 {
     vec2 xy = textureCoordinate;
     xy = xy - mod(xy, displayTileSize);

     vec4 lumcoeff = vec4(0.299,0.587,0.114,0.0);

     vec4 inputColor = texture2D(inputImageTexture2, xy);
     float lum = dot(inputColor,lumcoeff);
     lum = 1.0 - lum;

     float stepsize = 1.0 / numTiles;
     float lumStep = (lum - mod(lum, stepsize)) / stepsize;

     float rowStep = 1.0 / inputTileSize.x;
     float x = mod(lumStep, rowStep);
     float y = floor(lumStep / rowStep);

     vec2 startCoord = vec2(float(x) *  inputTileSize.x, float(y) * inputTileSize.y);
     vec2 finalCoord = startCoord + ((textureCoordinate - xy) * (inputTileSize / displayTileSize));

     vec4 color = texture2D(inputImageTexture, finalCoord);
     if (colorOn == 1) {
         color = color * inputColor;
     }
     gl_FragColor = color;
//     gl_FragColor = inputColor;
 }
);

#endif



GPUImageMosaicFilter::GPUImageMosaicFilter()
    : GPUImageImageFilter(_mosaic_fragment_shader)
{
    m_fNumTiles = 64.0f;
    m_bColorOn = false;

    memset(m_pTileSet, 0, ABS_FLIE_LEN_MAX);

    m_pInputTileSize[0] = 0.125f;
    m_pInputTileSize[1] = 0.125f;

    m_pDisplayTileSize[0] = 0.025f;
    m_pDisplayTileSize[1] = 0.025f;
}

GPUImageMosaicFilter::~GPUImageMosaicFilter()
{

}

void GPUImageMosaicFilter::setColorOn(bool colorOn)
{
    m_bColorOn = colorOn;
}

void GPUImageMosaicFilter::setDisplaySize(float x, float y)
{
    m_pDisplayTileSize[0] = x;
    m_pDisplayTileSize[1] = y;
}

void GPUImageMosaicFilter::setDisplaySize(int percent)
{
    float max = 2.0f;
    float min = 0.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setDisplaySize(value, value);
}

void GPUImageMosaicFilter::setNumTiles(float numTiles)
{
    m_fNumTiles = numTiles;
}

void GPUImageMosaicFilter::setTileSet(const char *tileSet)
{
    // 这里可以解码对应的图片
    // 这里不写了
}

bool GPUImageMosaicFilter::createProgramExtra()
{
    GPUImageImageFilter::createProgramExtra();

    m_iInputTileSizeUniformLocation = glGetUniformLocation(m_uProgram, "inputTileSize");
    m_iDisplayTileSizeUniformLocation = glGetUniformLocation(m_uProgram, "displayTileSize");
    m_iNumTilesUniformLocation = glGetUniformLocation(m_uProgram, "numTiles");
    m_iColorOnUniformLocation = glGetUniformLocation(m_uProgram, "colorOn");

    return true;
}

bool GPUImageMosaicFilter::beforeDrawExtra()
{
    GPUImageTwoInputFilter::beforeDrawExtra();

    glUniform2fv(m_iInputTileSizeUniformLocation, 1, m_pInputTileSize);
    glUniform2fv(m_iDisplayTileSizeUniformLocation, 1, m_pDisplayTileSize);
    glUniform1f(m_iNumTilesUniformLocation, m_fNumTiles);
    glUniform1i(m_iColorOnUniformLocation, m_bColorOn);

    return true;
}

bool GPUImageMosaicFilter::loadImage()
{
    // this is decode the image of squares.png.
    // in the example we just use the rgba data stored in
    // the file squares.rgba.

    const char* filename = "squares.rgba";

    m_uPicWidth = 640;
    m_uPicHeight = 640;
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


