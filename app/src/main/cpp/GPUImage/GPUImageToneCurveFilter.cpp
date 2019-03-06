/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>

#include "GPUImageToneCurveFilter.h"
#include "../util/FileUtil.h"

#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _toneCurve_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D toneCurveTexture;

    void main()
    {
        lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
        lowp float redCurveValue = texture2D(toneCurveTexture, vec2(textureColor.r, 0.0)).r;
        lowp float greenCurveValue = texture2D(toneCurveTexture, vec2(textureColor.g, 0.0)).g;
        lowp float blueCurveValue = texture2D(toneCurveTexture, vec2(textureColor.b, 0.0)).b;

        gl_FragColor = vec4(redCurveValue, greenCurveValue, blueCurveValue, textureColor.a);
    }
);

#else

// 片元着色器
extern const char _toneCurve_fragment_shader[] = SHADER_STR(
 varying vec2 textureCoordinate;
 uniform sampler2D inputImageTexture;
 uniform sampler2D toneCurveTexture;

 void main()
 {
     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
     float redCurveValue = texture2D(toneCurveTexture, vec2(textureColor.r, 0.0)).r;
     float greenCurveValue = texture2D(toneCurveTexture, vec2(textureColor.g, 0.0)).g;
     float blueCurveValue = texture2D(toneCurveTexture, vec2(textureColor.b, 0.0)).b;

     gl_FragColor = vec4(redCurveValue, greenCurveValue, blueCurveValue, textureColor.a);
 }
);

#endif


GPUImageACVFile::GPUImageACVFile()
{

}

GPUImageACVFile::~GPUImageACVFile()
{
    clear();
}

void GPUImageACVFile::initWithACVFileData(uint8_t *data, uint32_t length)
{
    if(0 == length){
        return;
    }

    uint8_t * rawBytes = data;

    m_iVersion = int16WithBytes(rawBytes);
    rawBytes += 2;

    m_iTotalCurves = int16WithBytes(rawBytes);
    rawBytes += 2;

    float pointRate = (1.0 / 255);
    // The following is the data for each curve specified by count above
    for (int x = 0; x < m_iTotalCurves; x++)
    {
        unsigned short pointCount = int16WithBytes(rawBytes);
        rawBytes+=2;

        CurvePointArray array = getCurvePointArrya(x);
        // point count * 4
        // Curve points. Each curve point is a pair of short integers where
        // the first number is the output value (vertical coordinate on the
        // Curves dialog graph) and the second is the input value. All coordinates have range 0 to 255.
        for (int y = 0; y<pointCount; y++)
        {
            unsigned short yy = int16WithBytes(rawBytes);
            rawBytes += 2;
            unsigned short xx = int16WithBytes(rawBytes);
            rawBytes += 2;
            array.push_back(Point(xx * pointRate, yy * pointRate));
        }
    }
}


CurvePointArray GPUImageACVFile::getCurvePointArrya(int idx)
{
    switch (idx){
        case 0:
            return m_vRGBCompositeControlPoints;
        case 1:
            return m_vRedControlPoints;
        case 2:
            return m_vGreenControlPoints;
        case 3:
            return m_vBlueControlPoints;
        default:
            return std::vector<GLPoint>();
    }

    return std::vector<GLPoint>();
}


void GPUImageACVFile::clear()
{
    m_vRGBCompositeControlPoints.clear();
    m_vRedControlPoints.clear();
    m_vBlueControlPoints.clear();
    m_vGreenControlPoints.clear();
}


uint16_t GPUImageACVFile::int16WithBytes(uint8_t *bytes)
{
    if(isHostBigendian()){
        return big_byte2short(bytes);
    }else{
        return little_byte2short(bytes);
    }

    return 0;
}


bool GPUImageACVFile::isHostBigendian()
{
    short i = 0x1;
    bool bRet = ((i >> 8) == 0x1);
    return bRet;
}

uint16_t GPUImageACVFile::little_byte2short(uint8_t *bytes)
{
    uint16_t ret = 0;
    uint16_t high = bytes[1];
    uint8_t low = bytes[0];
    ret = low;
    ret |= (high << 8) & 0xFF00;
    return ret;
}

uint16_t GPUImageACVFile::big_byte2short(uint8_t *bytes)
{
    uint16_t ret = 0;
    uint16_t high = bytes[0];
    uint8_t low = bytes[1];
    ret = low;
    ret |= (high << 8) & 0xFF00;
    return ret;
}


GPUImageToneCurveFilter::GPUImageToneCurveFilter()
    : GPUImageFilter(_toneCurve_fragment_shader)
{
    initValue();
    initDefalutCurve();
}


GPUImageToneCurveFilter::GPUImageToneCurveFilter(const char *acvfilenmae)
    : GPUImageFilter(_toneCurve_fragment_shader)
{
    initValue();

    uint32_t fileSize = FileUtil::getFileSize(acvfilenmae);
    uint8_t *data = (uint8_t *) malloc(fileSize * sizeof(uint8_t));
    if(!data){
        return ;
    }

    FileUtil::loadABSFile(acvfilenmae, data, fileSize);

    initACVCurve(data, fileSize);

    free(data);
}

GPUImageToneCurveFilter::GPUImageToneCurveFilter(uint8_t *data, uint32_t length)
    : GPUImageFilter(_toneCurve_fragment_shader)
{
    initValue();
    initACVCurve(data, length);
}


GPUImageToneCurveFilter::~GPUImageToneCurveFilter()
{
    this->release();
}


void GPUImageToneCurveFilter::initValue()
{
    m_pACVFile = NULL;

    m_iToneCurveTextureUnifomLocation = -1;

    m_uToneCurveTextureId = 0;

    m_pToneCurveByteArray = (GLubyte *) malloc(256 * 4 * sizeof(GLubyte));
    if(!m_pToneCurveByteArray){
        return ;
    }
}


void GPUImageToneCurveFilter::initDefalutCurve()
{
    CurvePointArray defaultCurve;
    GLPoint point1 = GLPoint(0.0f, 0.0f);
    GLPoint point2 = GLPoint(0.5f, 0.5f);
    GLPoint point3 = GLPoint(1.0f, 1.0f);

    defaultCurve.push_back(point1);
    defaultCurve.push_back(point2);
    defaultCurve.push_back(point3);

    setRgbCompositeControlPoints(defaultCurve);
    setRedControlPoints(defaultCurve);
    setGreenControlPoints(defaultCurve);
    setBlueControlPoints(defaultCurve);
}

void GPUImageToneCurveFilter::initACVCurve(uint8_t* data, uint32_t length)
{
    if(!m_pACVFile){
        m_pACVFile = new GPUImageACVFile();
    }

    m_pACVFile->clear();
    m_pACVFile->initWithACVFileData(data, length);

    setRgbCompositeControlPoints(m_pACVFile->getRGBCompositeControlPoints());
    setRedControlPoints(m_pACVFile->getRedControlPoints());
    setGreenControlPoints(m_pACVFile->getGreenControlPoints());
    setBlueControlPoints(m_pACVFile->getBlueControlPoints());
}


bool GPUImageToneCurveFilter::release()
{
    if(0 != m_uToneCurveTextureId){
        glDeleteTextures(1, &m_uToneCurveTextureId);
        m_uToneCurveTextureId = 0;
    }

    if(m_pToneCurveByteArray){
        free(m_pToneCurveByteArray);
        m_pToneCurveByteArray = NULL;
    }

    if(m_pACVFile){
        delete m_pACVFile;
        m_pACVFile = NULL;
    }

    return true;
}

bool GPUImageToneCurveFilter::createProgramExtra()
{
    m_iToneCurveTextureUnifomLocation = glGetUniformLocation(m_uProgram, "toneCurveTexture");

    if(0 == m_uToneCurveTextureId){
        glActiveTexture(GL_TEXTURE2);
        glGenTextures(1, &m_uToneCurveTextureId);
        glBindTexture(GL_TEXTURE_2D, m_uToneCurveTextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageToneCurveFilter::beforeDrawExtra()
{
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_uToneCurveTextureId);
    glUniform1i(m_iToneCurveTextureUnifomLocation, 2);

    if(m_bToneTextureUpdated){
        m_bToneTextureUpdated = false;

        if(    (m_v_redCurve.size() >= 256)
            && (m_v_greenCurve.size() >= 256)
            && (m_v_blueCurve.size() >= 256)
            && (m_v_rgbCompositeCurve.size() >= 256)
          )
        {
            for (unsigned int currentCurveIndex = 0; currentCurveIndex < 256; currentCurveIndex++)
            {
                // RGBA for upload to texture
                GLubyte r = fmin(fmax( currentCurveIndex + m_v_redCurve[currentCurveIndex], 0), 255);
                m_pToneCurveByteArray[currentCurveIndex * 4 ] = fmin(fmax(r + m_v_rgbCompositeCurve[r], 0), 255);

                GLubyte g = fmin(fmax( currentCurveIndex + m_v_greenCurve[currentCurveIndex], 0), 255);
                m_pToneCurveByteArray[currentCurveIndex * 4 + 1] = fmin(fmax(g + m_v_rgbCompositeCurve[g], 0), 255);

                GLubyte b = fmin(fmax( currentCurveIndex + m_v_blueCurve[currentCurveIndex], 0), 255);
                m_pToneCurveByteArray[currentCurveIndex * 4 + 2] = fmin(fmax(b + m_v_rgbCompositeCurve[b], 0), 255);

                m_pToneCurveByteArray[currentCurveIndex * 4 + 3] = 255;
            }

            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 1, GL_RGBA, GL_UNSIGNED_BYTE, m_pToneCurveByteArray);
        }
    }

    return GPUImageFilter::beforeDrawExtra();
}


void GPUImageToneCurveFilter::setPointsWithACVFileName(const char *acvfilenmae)
{
    uint32_t fileSize = FileUtil::getFileSize(acvfilenmae);
    uint8_t *data = (uint8_t *) malloc(fileSize * sizeof(uint8_t));
    if(!data){
        return ;
    }

    FileUtil::loadABSFile(acvfilenmae, data, fileSize);

    setPointsWithACVData(data, fileSize);

    free(data);
}

void GPUImageToneCurveFilter::setPointsWithACVData(uint8_t *data, uint32_t length)
{
    initACVCurve(data, length);
}


void GPUImageToneCurveFilter::setRGBControPoints(CurvePointArray points)
{
    setRedControlPoints(points);
    setGreenControlPoints(points);
    setBlueControlPoints(points);
}

void GPUImageToneCurveFilter::setRgbCompositeControlPoints(CurvePointArray points)
{
    m_vRGBCompositeControlPoints = points;
    m_v_rgbCompositeCurve = getPreparedSplineCurve(m_vRGBCompositeControlPoints);
    m_bToneTextureUpdated = true;

}

void GPUImageToneCurveFilter::setRedControlPoints(CurvePointArray points)
{
    m_vRedControlPoints = points;
    m_v_redCurve = getPreparedSplineCurve(m_vRedControlPoints);
    m_bToneTextureUpdated = true;
}

void GPUImageToneCurveFilter::setGreenControlPoints(CurvePointArray points)
{
    m_vGreenControlPoints = points;
    m_v_greenCurve = getPreparedSplineCurve(m_vGreenControlPoints);
    m_bToneTextureUpdated = true;
}

void GPUImageToneCurveFilter::setBlueControlPoints(CurvePointArray points)
{
    m_vBlueControlPoints = points;
    m_v_blueCurve = getPreparedSplineCurve(m_vBlueControlPoints);
    m_bToneTextureUpdated = true;
}

bool compare(GLPoint& a, GLPoint& b)
{
    return a.x < b.x;
}

CurveArray GPUImageToneCurveFilter::getPreparedSplineCurve(CurvePointArray points)
{
    CurveArray retVec;

    if(!points.empty()){

        // Sort the array.
        std::sort(points.begin(), points.end(), compare);

        // Convert from (0, 1) to (0, 255).

        CurvePointArray convertedPoints(points.size());

        for (int i = 0; i < points.size(); ++i) {
            GLPoint point = points[i];
            point.x = point.x * 255;
            point.y = point.y * 255;
            convertedPoints[i] = point;
        }

        CurvePointList splinePoints = splineCurve(convertedPoints);

        // If we have a first point like (0.3, 0) we'll be missing some points at the beginning
        // that should be 0.
        GLPoint firstSplinePoint = splinePoints.front();

        if (firstSplinePoint.x > 0) {
            for (int i = firstSplinePoint.x; i >= 0; i--) {
                GLPoint point = GLPoint(i, 0);
                splinePoints.insert(splinePoints.begin(), point);
            }
        }

        // Insert points similarly at the end, if necessary.

        GLPoint lastSplinePoint = splinePoints.back();
        if (lastSplinePoint.x < 255) {
            for (int i = lastSplinePoint.x + 1; i <= 255; i++) {
                GLPoint point = GLPoint(i, 255);
                splinePoints.push_back(point);
            }
        }


        // Prepare the spline points.
        CurveArray preparedSplinePoints(splinePoints.size());
        int idx = 0;
        for(CurvePointList::iterator iterator = splinePoints.begin(); iterator != splinePoints.end(); ++iterator)
        {
            GLPoint newPoint = *iterator;
            GLPoint origPoint =  GLPoint(newPoint.x, newPoint.x);

            float distance = sqrt(pow((origPoint.x - newPoint.x), 2.0) + pow((origPoint.y - newPoint.y), 2.0));

            if (origPoint.y > newPoint.y)
            {
                distance = -distance;
            }

            preparedSplinePoints[idx++] = distance;
        }

        return preparedSplinePoints;
    }

    return retVec;
}

CurvePointList GPUImageToneCurveFilter::splineCurve(CurvePointArray& points)
{
    CurvePointList retVec;

    CurveArray sdA = secondDerivative(points);

    // [points count] is equal to [sdA count]
    if(sdA.empty()){
        return retVec;
    }

    int n = sdA.size();
    double *sd = new double[n];

    // From NSMutableArray to sd[n];
    for (int i = 0; i < n; i++)
    {
        sd[i] = sdA[i];
    }

    CurvePointList output;

    for(int i=0; i<n-1 ; i++)
    {
        GLPoint cur = points[i];
        GLPoint next = points[i + 1];

        for(int x =cur.x; x < (int)next.x; x++)
        {
            double t = (double)(x-cur.x)/(next.x-cur.x);

            double a = 1-t;
            double b = t;
            double h = next.x-cur.x;

            double y= a*cur.y + b*next.y + (h*h/6)*( (a*a*a-a)*sd[i]+ (b*b*b-b)*sd[i+1] );

            if (y > 255.0)
            {
                y = 255.0;
            }
            else if (y < 0.0)
            {
                y = 0.0;
            }

            output.push_back(Point(x, y));
        }
    }

    // The above always misses the last point because the last point is the last next, so we approach but don't equal it.
    output.push_back(points.back());

    delete[] sd;
    return output;
}

CurveArray GPUImageToneCurveFilter::secondDerivative(CurvePointArray& points)
{
    CurveArray retVec;

    const int n = points.size();
    if(n <= 1){
        return retVec;
    }

    double **matrix = new double*[n];
    for(int i=0; i< n; ++i){
        matrix[i] = new double[3];
    }

    double *result = new double[n];

    matrix[0][1]=1;
    // What about matrix[0][1] and matrix[0][0]? Assuming 0 for now (Brad L.)
    matrix[0][0]=0;
    matrix[0][2]=0;

    for(int i = 1; i < n-1; i++)
    {
        GLPoint P1 = points[ i - 1 ];
        GLPoint P2 = points[ i ];
        GLPoint P3 = points[ i + 1 ];

        matrix[i][0]=(double)(P2.x-P1.x)/6;
        matrix[i][1]=(double)(P3.x-P1.x)/3;
        matrix[i][2]=(double)(P3.x-P2.x)/6;
        result[i]=(double)(P3.y-P2.y)/(P3.x-P2.x) - (double)(P2.y-P1.y)/(P2.x-P1.x);
    }

    // What about result[0] and result[n-1]? Assuming 0 for now (Brad L.)
    result[0] = 0;
    result[n-1] = 0;

    matrix[n-1][1]=1;
    // What about matrix[n-1][0] and matrix[n-1][2]? For now, assuming they are 0 (Brad L.)
    matrix[n-1][0]=0;
    matrix[n-1][2]=0;

    // solving pass1 (up->down)
    for(int i = 1; i < n; i++)
    {
        double k = matrix[i][0]/matrix[i-1][1];
        matrix[i][1] -= k*matrix[i-1][2];
        matrix[i][0] = 0;
        result[i] -= k*result[i-1];
    }

    // solving pass2 (down->up)
    for(int i = n-2; i >= 0; i--)
    {
        double k = matrix[i][2]/matrix[i+1][1];
        matrix[i][1] -= k*matrix[i+1][0];
        matrix[i][2] = 0;
        result[i] -= k*result[i+1];
    }

    double *y2 = new double[n];
    for(int i = 0; i < n; i++)
    {
        y2[i] = result[i] / matrix[i][1];
    }

    CurveArray output(n);
    for (int i = 0; i < n; i++)
    {
        output[i] = y2[i];
    }

    delete[] y2;

    delete[] result;

    for(int i=0; i< n; ++i){
        delete[] matrix[i];
    }
    delete[] matrix;

    return output;
}

