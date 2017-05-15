/**
 * Created by lvHiei on 17-5-3.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageGaussianBlurFilter.h"

extern const char _base_vertex_shader[];
extern const char _base_fragment_shader[];



GPUImageGaussianBlurFilter::GPUImageGaussianBlurFilter()
    : GPUImageTwoPassTextureSamplingFilter("","","","")
{
    initWithBlurSigma(4, 2.0);

    m_fTexelSpacingMutiplier = 1.0f;
    m_fBlurRadiusInPexels = 2.0;
    m_bShouldResizeBlurRadiusWidthImageWidth = false;
}

GPUImageGaussianBlurFilter::GPUImageGaussianBlurFilter(float blurRadiusInPixels)
    : GPUImageTwoPassTextureSamplingFilter("","","","")
{
    m_fBlurRadiusInPexels = round(blurRadiusInPixels);

    int calculatedSampleRadius = 0;
    if(m_fBlurRadiusInPexels >= 1.0f){
        // Calculate the number of pixels to sample from by setting a bottom limit for the contribution of the outermost pixel
        float minimumWeightToFindEdgeOfSamplingArea = 1.0/256.0;
        calculatedSampleRadius = floor(sqrt(-2.0 * pow(m_fBlurRadiusInPexels, 2.0) * log(minimumWeightToFindEdgeOfSamplingArea * sqrt(2.0 * M_PI * pow(m_fBlurRadiusInPexels, 2.0))) ));
        calculatedSampleRadius += calculatedSampleRadius % 2; // There's nothing to gain from handling odd radius sizes, due to the optimizations I use
    }

    initWithBlurSigma(calculatedSampleRadius, m_fBlurRadiusInPexels);

    m_fTexelSpacingMutiplier = 1.0f;
    m_bShouldResizeBlurRadiusWidthImageWidth = false;
}


void GPUImageGaussianBlurFilter::initWithBlurSigma(int blurRadius, float sigma)
{
    this->genVertexShaderForOptimizedBlurOfRadius(blurRadius, sigma);
    this->genFragmentShaderForOptimizedBlurOfRadius(blurRadius, sigma);
}


GPUImageGaussianBlurFilter::~GPUImageGaussianBlurFilter()
{

}

void GPUImageGaussianBlurFilter::setTexelSpacingMultiplier(float mutiplier)
{
    m_fTexelSpacingMutiplier = mutiplier;

    m_f_verticalTexelSpacing = m_fTexelSpacingMutiplier;
    m_f_horizontalTexelSpacing = m_fTexelSpacingMutiplier;

    updateBlurRadiusInPixels();
}


void GPUImageGaussianBlurFilter::setBlurRadiusInPixels(float blurRadiusInPixels)
{
    if(m_fBlurRadiusInPexels == blurRadiusInPixels){
        return;
    }

    m_fBlurRadiusInPexels = blurRadiusInPixels;
    m_bWantChangeBlurRadius = true;
}



void GPUImageGaussianBlurFilter::setBlurRadiusAsFractionOfImageWidth(
        float blurRadiusAsFractionOfImageWidth)
{
    if(blurRadiusAsFractionOfImageWidth < 0){
        return;
    }

    m_bShouldResizeBlurRadiusWidthImageWidth = m_fBlurRadiusAsFractionOfImageWidth != blurRadiusAsFractionOfImageWidth && blurRadiusAsFractionOfImageWidth > 0;
    m_fBlurRadiusAsFractionOfImageWidth = blurRadiusAsFractionOfImageWidth;
    m_fBlurRadiusAsFractionOfImageHeight = 0.0f;
}

void GPUImageGaussianBlurFilter::setBlurRadiusAsFractionOfImageHeight(
        float blurRadiusAsFractionOfImageHeight)
{
    if(blurRadiusAsFractionOfImageHeight < 0){
        return;
    }

    m_fBlurRadiusAsFractionOfImageHeight = m_fBlurRadiusAsFractionOfImageHeight != blurRadiusAsFractionOfImageHeight && blurRadiusAsFractionOfImageHeight > 0;
    m_fBlurRadiusAsFractionOfImageHeight = blurRadiusAsFractionOfImageHeight;
    m_fBlurRadiusAsFractionOfImageWidth = 0.0f;
}

void GPUImageGaussianBlurFilter::genVertexShaderForStandardBlurOfRadius(int blurRadius, float sigma)
{
    if(blurRadius < 1){
        resetShader(_base_vertex_shader, _base_fragment_shader, _base_vertex_shader, _base_fragment_shader);
        return;
    }

    char tempShader[20480] = {0};

    const char* part1 =
    "attribute vec4 position;\n"
    "attribute vec4 inputTextureCoordinate;\n"
    "\n"
    "uniform float texelWidthOffset;\n"
    "uniform float texelHeightOffset;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "  gl_Position = position;\n"
    "\n"
    "  vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n"
    ;

    sprintf(tempShader + strlen(tempShader), part1, blurRadius * 2 + 1);

    for(int idx = 0; idx < (blurRadius * 2 + 1); ++idx){
        int offsetFromCenter = idx - blurRadius;

        if(offsetFromCenter < 0)
        {
            sprintf(tempShader + strlen(tempShader), "blurCoordinates[%d] = inputTextureCoordinate.xy - singleStepOffset * %f;\n", idx, (float)(-offsetFromCenter));
        }
        else if (offsetFromCenter > 0)
        {
            sprintf(tempShader + strlen(tempShader), "blurCoordinates[%d] = inputTextureCoordinate.xy + singleStepOffset * %f;\n", idx, (float)(offsetFromCenter));
        }
        else
        {
            sprintf(tempShader + strlen(tempShader), "blurCoordinates[%d] = inputTextureCoordinate.xy;\n", idx);
        }
    }

    sprintf(tempShader + strlen(tempShader), "}\n");

    resetFirstVertexShader(tempShader);
    resetSecondVertexShader(tempShader);
}

void GPUImageGaussianBlurFilter::genFragmentShaderForStandardBlurOfRadius(int blurRadius,
                                                                                 float sigma)
{
    if(blurRadius < 1){
        resetShader(_base_vertex_shader, _base_fragment_shader, _base_vertex_shader, _base_fragment_shader);
        return;
    }

    // First, generate the normal Gaussian weights for a given sigma
    GLfloat *standardGaussianWeights = (GLfloat *) malloc((blurRadius + 1) * sizeof(GLfloat));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));

        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    // Next, normalize these weights to prevent the clipping of the Gaussian curve at the end of the discrete samples from reducing luminance
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }

    // Finally, generate the shader from these weights
    char tempShader[20480] = {0};

    // Header
#ifdef __GLSL_SUPPORT_HIGHP__
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "\n"
    "varying highp vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp vec4 sum = vec4(0.0);\n"
    ;
#else
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp vec4 sum = vec4(0.0);\n"
    ;
#endif

    sprintf(tempShader + strlen(tempShader), part1, blurRadius * 2 + 1);

    // Inner texture loop
    for (int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < (blurRadius * 2 + 1); currentBlurCoordinateIndex++)
    {
        int offsetFromCenter = currentBlurCoordinateIndex - blurRadius;
        if (offsetFromCenter < 0)
        {
            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", currentBlurCoordinateIndex, standardGaussianWeights[-offsetFromCenter]);
        }
        else
        {
            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", currentBlurCoordinateIndex, standardGaussianWeights[offsetFromCenter]);
        }
    }

    // Footer
    const char* part2 =
    "   gl_FragColor = sum;\n"
    "}\n"
    ;

    strcpy(tempShader + strlen(tempShader), part2);

    free(standardGaussianWeights);

    resetFirstFragmentShader(tempShader);
    resetSecondFragmentShader(tempShader);
}

void GPUImageGaussianBlurFilter::genVertexShaderForOptimizedBlurOfRadius(int blurRadius,
                                                                                float sigma)
{
    if(blurRadius < 1){
        resetShader(_base_vertex_shader, _base_fragment_shader, _base_vertex_shader, _base_fragment_shader);
        return;
    }


    // First, generate the normal Gaussian weights for a given sigma
    GLfloat *standardGaussianWeights = (GLfloat *) malloc((blurRadius + 1) * sizeof(GLfloat));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));

        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    // Next, normalize these weights to prevent the clipping of the Gaussian curve at the end of the discrete samples from reducing luminance
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }

    // From these weights we calculate the offsets to read interpolated values from
    int curOffset = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = curOffset > 7 ? 7 : curOffset;
    GLfloat *optimizedGaussianOffsets = (GLfloat *) malloc(numberOfOptimizedOffsets * sizeof(GLfloat));

    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        GLfloat firstWeight = standardGaussianWeights[currentOptimizedOffset*2 + 1];
        GLfloat secondWeight = standardGaussianWeights[currentOptimizedOffset*2 + 2];

        GLfloat optimizedWeight = firstWeight + secondWeight;

        optimizedGaussianOffsets[currentOptimizedOffset] = (firstWeight * (currentOptimizedOffset*2 + 1) + secondWeight * (currentOptimizedOffset*2 + 2)) / optimizedWeight;
    }


    char tempShader[20480] = {0};
    const char* part1 =
    "attribute vec4 position;\n"
    "attribute vec4 inputTextureCoordinate;\n"
    "\n"
    "uniform float texelWidthOffset;\n"
    "uniform float texelHeightOffset;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = position;\n"
    "    vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n"
    ;


    sprintf(tempShader + strlen(tempShader), part1, 1 + (numberOfOptimizedOffsets * 2));

    // Inner offset loop
    sprintf(tempShader + strlen(tempShader), "blurCoordinates[0] = inputTextureCoordinate.xy;\n");

    const char* part2 =
    "   blurCoordinates[%d] = inputTextureCoordinate.xy + singleStepOffset * %f;\n"
    "   blurCoordinates[%d] = inputTextureCoordinate.xy - singleStepOffset * %f;\n"
    ;

    for (int currentOptimizedOffset = 0; currentOptimizedOffset < numberOfOptimizedOffsets; currentOptimizedOffset++)
    {
        sprintf(tempShader + strlen(tempShader), part2, (currentOptimizedOffset * 2) + 1,
                optimizedGaussianOffsets[currentOptimizedOffset], (currentOptimizedOffset * 2) + 2, optimizedGaussianOffsets[currentOptimizedOffset]);
    }

    // Footer
    sprintf(tempShader + strlen(tempShader), "}\n");

    free(optimizedGaussianOffsets);
    free(standardGaussianWeights);

    resetFirstVertexShader(tempShader);
    resetSecondVertexShader(tempShader);
}

void GPUImageGaussianBlurFilter::genFragmentShaderForOptimizedBlurOfRadius(int blurRadius,
                                                                                  float sigma)
{
    if(blurRadius < 1){
        resetShader(_base_vertex_shader, _base_fragment_shader, _base_vertex_shader, _base_fragment_shader);
        return;
    }

    // First, generate the normal Gaussian weights for a given sigma
    GLfloat *standardGaussianWeights = (GLfloat *) malloc((blurRadius + 1) * sizeof(GLfloat));
    GLfloat sumOfWeights = 0.0;
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = (1.0 / sqrt(2.0 * M_PI * pow(sigma, 2.0))) * exp(-pow(currentGaussianWeightIndex, 2.0) / (2.0 * pow(sigma, 2.0)));

        if (currentGaussianWeightIndex == 0)
        {
            sumOfWeights += standardGaussianWeights[currentGaussianWeightIndex];
        }
        else
        {
            sumOfWeights += 2.0 * standardGaussianWeights[currentGaussianWeightIndex];
        }
    }

    // Next, normalize these weights to prevent the clipping of the Gaussian curve at the end of the discrete samples from reducing luminance
    for (int currentGaussianWeightIndex = 0; currentGaussianWeightIndex < blurRadius + 1; currentGaussianWeightIndex++)
    {
        standardGaussianWeights[currentGaussianWeightIndex] = standardGaussianWeights[currentGaussianWeightIndex] / sumOfWeights;
    }

    // From these weights we calculate the offsets to read interpolated values from
    int curOffset = blurRadius / 2 + (blurRadius % 2);
    int numberOfOptimizedOffsets = curOffset > 7 ? 7 : curOffset;
    int trueNumberOfOptimizedOffsets = blurRadius / 2 + (blurRadius % 2);


    char tempShader[20480] = {0};
    // Header

#ifdef __GLSL_SUPPORT_HIGHP__
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "uniform highp float texelWidthOffset;\n"
    "uniform highp float texelHeightOffset;\n"
    "\n"
    "varying highp vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp vec4 sum = vec4(0.0);\n"
    ;
#else
    const char* part1 =
    "uniform sampler2D inputImageTexture;\n"
    "uniform float texelWidthOffset;\n"
    "uniform float texelHeightOffset;\n"
    "\n"
    "varying vec2 blurCoordinates[%d];\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp vec4 sum = vec4(0.0);\n"
    ;
#endif

    sprintf(tempShader + strlen(tempShader), part1, 1 + (numberOfOptimizedOffsets * 2));


    // Inner texture loop
    sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0]) * %f;\n", standardGaussianWeights[0]);

    for (int currentBlurCoordinateIndex = 0; currentBlurCoordinateIndex < numberOfOptimizedOffsets; currentBlurCoordinateIndex++)
    {
        GLfloat firstWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 1];
        GLfloat secondWeight = standardGaussianWeights[currentBlurCoordinateIndex * 2 + 2];
        GLfloat optimizedWeight = firstWeight + secondWeight;

        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", (currentBlurCoordinateIndex * 2) + 1, optimizedWeight);
        sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[%d]) * %f;\n", (currentBlurCoordinateIndex * 2) + 2, optimizedWeight);
    }

    // If the number of required samples exceeds the amount we can pass in via varyings, we have to do dependent texture reads in the fragment shader
    if (trueNumberOfOptimizedOffsets > numberOfOptimizedOffsets)
    {
#ifdef __GLSL_SUPPORT_HIGHP__
        sprintf(tempShader + strlen(tempShader), "highp vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n");
#else
        sprintf(tempShader + strlen(tempShader), "vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);\n");
#endif

        for (int currentOverlowTextureRead = numberOfOptimizedOffsets; currentOverlowTextureRead < trueNumberOfOptimizedOffsets; currentOverlowTextureRead++)
        {
            GLfloat firstWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 1];
            GLfloat secondWeight = standardGaussianWeights[currentOverlowTextureRead * 2 + 2];

            GLfloat optimizedWeight = firstWeight + secondWeight;
            GLfloat optimizedOffset = (firstWeight * (currentOverlowTextureRead * 2 + 1) + secondWeight * (currentOverlowTextureRead * 2 + 2)) / optimizedWeight;

            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] + singleStepOffset * %f) * %f;\n", optimizedOffset, optimizedWeight);
            sprintf(tempShader + strlen(tempShader), "sum += texture2D(inputImageTexture, blurCoordinates[0] - singleStepOffset * %f) * %f;\n", optimizedOffset, optimizedWeight);
        }
    }

    // Footer

    const char* part2 =
    "    gl_FragColor = sum;\n"
    "}\n"
    ;

    strcpy(tempShader + strlen(tempShader), part2);

    free(standardGaussianWeights);

    resetFirstFragmentShader(tempShader);
    resetSecondFragmentShader(tempShader);
}

void GPUImageGaussianBlurFilter::setTextureSize(int width, int height)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureSize(width, height);
    updateBlurRadiusInPixels();
}

void GPUImageGaussianBlurFilter::setTextureRotation(Rotation rotation)
{
    GPUImageTwoPassTextureSamplingFilter::setTextureRotation(rotation);
    updateBlurRadiusInPixels();
}


void GPUImageGaussianBlurFilter::updateBlurRadiusInPixels()
{
    if(m_bShouldResizeBlurRadiusWidthImageWidth){
        if (m_fBlurRadiusAsFractionOfImageWidth > 0)
        {
            m_fBlurRadiusInPexels = m_iTextureWidth * m_fBlurRadiusAsFractionOfImageWidth;
        }
        else
        {
            m_fBlurRadiusInPexels = m_iTextureHeight * m_fBlurRadiusAsFractionOfImageHeight;
        }
    }
}


void GPUImageGaussianBlurFilter::resetFirstVertexShader(const char *shader)
{
    if(m_pVertexShader){
        free(m_pVertexShader);
    }

    int vLen = strlen(shader) + 1;

    m_pVertexShader = (char *) malloc(vLen);
    strcpy(m_pVertexShader, shader);
}

void GPUImageGaussianBlurFilter::resetFirstFragmentShader(const char *shader)
{
    if(m_pFragmnetShader){
        free(m_pFragmnetShader);
    }

    int vLen = strlen(shader) + 1;

    m_pFragmnetShader = (char *) malloc(vLen);
    strcpy(m_pFragmnetShader, shader);
}

void GPUImageGaussianBlurFilter::resetSecondVertexShader(const char *shader)
{
    if(m_pSecondVertexShader){
        free(m_pSecondVertexShader);
    }

    int vLen = strlen(shader) + 1;

    m_pSecondVertexShader = (char *) malloc(vLen);
    strcpy(m_pSecondVertexShader, shader);
}

void GPUImageGaussianBlurFilter::resetSecondFragmentShader(const char *shader)
{
    if(m_pSecondFragShader){
        free(m_pSecondFragShader);
    }

    int vLen = strlen(shader) + 1;

    m_pSecondFragShader = (char *) malloc(vLen);
    strcpy(m_pSecondFragShader, shader);
}


bool GPUImageGaussianBlurFilter::draw(GLuint textureId, int viewWidth, int viewHeight,
                                      GLuint frameBufferId)
{
    if(m_bWantChangeBlurRadius){
        m_bWantChangeBlurRadius = false;
        changeBlurRadius();
    }

    return GPUImageTwoPassFilter::draw(textureId, viewWidth, viewHeight, frameBufferId);
}


void GPUImageGaussianBlurFilter::changeBlurRadius()
{
    // todo not implement
    int t_w = m_iTextureWidth;
    int t_h = m_iTextureHeight;
    Rotation rotation = m_eRotation;
    float vertex_coord[8];
    float textureCoord[8];
    memcpy(vertex_coord, m_pVertexCoordinate, VERTEX_COORDINATE_SIZE* sizeof(float));
    memcpy(textureCoord, m_pTextureCoordinate, TEXTURE_COORDINATE_SIZE* sizeof(float));

    this->recreateFilter();
    this->setTextureSize(t_w, t_h);
    this->setTextureRotation(rotation);
    this->setVertexCoordinate(vertex_coord);
    memcpy(m_pTextureCoordinate, textureCoord, TEXTURE_COORDINATE_SIZE* sizeof(float));

    this->createProgram();
}


void GPUImageGaussianBlurFilter::recreateFilter()
{
    this->~GPUImageGaussianBlurFilter();
    new(this)GPUImageGaussianBlurFilter(m_fBlurRadiusInPexels);
}


