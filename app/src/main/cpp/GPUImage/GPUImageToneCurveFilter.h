/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGETONECURVEFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGETONECURVEFILTER_H

#include <vector>
#include <list>
#include<algorithm>

#include "GPUImageFilter.h"

typedef struct Point{
    Point(){x = 0.0; y =0.0;}
    Point(float a, float b){x = a; y = b;}
    float x;
    float y;
}GLPoint;


typedef std::vector<GLPoint> CurvePointArray;
typedef std::vector<float > CurveArray;
typedef std::list<GLPoint> CurvePointList;


//  GPUImageACVFile
//
//  ACV File format Parser
//  Please refer to http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/PhotoshopFileFormats.htm#50577411_pgfId-1056330
//
class GPUImageACVFile{
public:
    GPUImageACVFile();
    virtual ~GPUImageACVFile();

    void initWithACVFileData(uint8_t* data, uint32_t length);

    void clear();
protected:
    uint16_t int16WithBytes(uint8_t* bytes);
    CurvePointArray getCurvePointArrya(int idx);
    bool isHostBigendian();
    uint16_t little_byte2short(uint8_t* bytes);
    uint16_t big_byte2short(uint8_t* bytes);

public:
    const CurvePointArray &getRedControlPoints() const {
        return m_vRedControlPoints;
    }

    const CurvePointArray &getGreenControlPoints() const {
        return m_vGreenControlPoints;
    }

    const CurvePointArray &getBlueControlPoints() const {
        return m_vBlueControlPoints;
    }

    const CurvePointArray &getRGBCompositeControlPoints() const {
        return m_vRGBCompositeControlPoints;
    }

private:
    CurvePointArray m_vRedControlPoints;
    CurvePointArray m_vGreenControlPoints;
    CurvePointArray m_vBlueControlPoints;
    CurvePointArray m_vRGBCompositeControlPoints;

    uint16_t m_iVersion;
    uint16_t m_iTotalCurves;
};

class GPUImageToneCurveFilter : public GPUImageFilter{
public:
    GPUImageToneCurveFilter();
    GPUImageToneCurveFilter(const char* acvfilenmae);
    GPUImageToneCurveFilter(uint8_t* data, uint32_t length);
    virtual ~GPUImageToneCurveFilter();

    virtual bool release();

public:
    void setRGBControPoints(CurvePointArray points);
    void setRgbCompositeControlPoints(CurvePointArray points);
    void setRedControlPoints(CurvePointArray points);
    void setGreenControlPoints(CurvePointArray points);
    void setBlueControlPoints(CurvePointArray points);

    void setPointsWithACVFileName(const char* filename);
    void setPointsWithACVData(uint8_t* data, uint32_t length);

protected:
    void initValue();
    void initDefalutCurve();
    void initACVCurve(uint8_t* data, uint32_t length);

    CurveArray getPreparedSplineCurve(CurvePointArray points);

    CurvePointList splineCurve(CurvePointArray& points);
    CurveArray secondDerivative(CurvePointArray& points);

protected:
    virtual bool createProgramExtra();
    virtual bool beforeDrawExtra();

protected:
    GLuint m_uToneCurveTextureId;
    GLint m_iToneCurveTextureUnifomLocation;

protected:
    CurvePointArray m_vRedControlPoints;
    CurvePointArray m_vGreenControlPoints;
    CurvePointArray m_vBlueControlPoints;
    CurvePointArray m_vRGBCompositeControlPoints;

    GLubyte* m_pToneCurveByteArray;

    CurveArray m_v_redCurve;
    CurveArray m_v_greenCurve;
    CurveArray m_v_blueCurve;
    CurveArray m_v_rgbCompositeCurve;

    bool m_bToneTextureUpdated;

protected:
    GPUImageACVFile* m_pACVFile;
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETONECURVEFILTER_H
