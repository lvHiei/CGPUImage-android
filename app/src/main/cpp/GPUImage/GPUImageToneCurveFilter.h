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

class GPUImageToneCurveFilter : public GPUImageFilter{
public:
    GPUImageToneCurveFilter();
    virtual ~GPUImageToneCurveFilter();

    virtual bool release();

public:
    void setRGBControPoints(CurvePointArray points);
    void setRgbCompositeControlPoints(CurvePointArray points);
    void setRedControlPoints(CurvePointArray points);
    void setGreenControlPoints(CurvePointArray points);
    void setBlueControlPoints(CurvePointArray points);

protected:
    void initDefalutCurve();

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
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGETONECURVEFILTER_H
