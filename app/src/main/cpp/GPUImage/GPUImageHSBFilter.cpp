/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include <math.h>

#include "GPUImageHSBFilter.h"

/* Matrix algorithms adapted from http://www.graficaobscura.com/matrix/index.html

 Note about luminance vector values below from that page:
 Where rwgt is 0.3086, gwgt is 0.6094, and bwgt is 0.0820. This is the luminance vector. Notice here that we do not use the standard NTSC weights of 0.299, 0.587, and 0.114. The NTSC weights are only applicable to RGB colors in a gamma 2.2 color space. For linear RGB colors the values above are better.
 */
//#define RLUM (0.3086f)
//#define GLUM (0.6094f)
//#define BLUM (0.0820f)

/* This is the vector value from the PDF specification, and may be closer to what Photoshop uses */
#define RLUM (0.3f)
#define GLUM (0.59f)
#define BLUM (0.11f)


GPUImageHSBFilter::GPUImageHSBFilter()
    : GPUImageColorMatrixFilter()
{
    reset();
}

GPUImageHSBFilter::~GPUImageHSBFilter()
{

}

void GPUImageHSBFilter::reset()
{
    identmat(m_pMatrix);
    updateColorMatrix();
}

void GPUImageHSBFilter::rotateHue(float h)
{
    huerotatemat(m_pMatrix, h);
    updateColorMatrix();
}

void GPUImageHSBFilter::adjustSaturation(float s)
{
    saturatemat(m_pMatrix, s);
    updateColorMatrix();
}

void GPUImageHSBFilter::adjustBrightness(float b)
{
    cscalemat(m_pMatrix, b, b, b);
    updateColorMatrix();
}

void GPUImageHSBFilter::updateColorMatrix()
{
    int colorIdx = 0;
    int idx = 0;
    for(int i = 0; i < 4; i++){
        idx = i;
        for(int j = 0; j < 4; j++){
            m_pColorMatrix[colorIdx++] = m_pMatrix[idx];
            idx += 4;
        }
    }
}

/*
 *	matrixmult -
 *		multiply two matricies
 */
void GPUImageHSBFilter::matrixmult(float *a, float *b, float *c)
{
    int x, y;
    float temp[16];
//    for(y=0; y<4 ; y++)
//        for(x=0 ; x<4 ; x++) {
//            temp[y][x] = b[y][0] * a[0][x]
//                         + b[y][1] * a[1][x]
//                         + b[y][2] * a[2][x]
//                         + b[y][3] * a[3][x];
//        }
//    for(y=0; y<4; y++)
//        for(x=0; x<4; x++)
//            c[y][x] = temp[y][x];


    for(y=0; y<4 ; y++)
    {
        for(x=0 ; x<4 ; x++)
        {
            temp[4 * y + x] = b[4 * y] * a[x]
                         + b[4 * y + 1] * a[4 + x]
                         + b[4 * y + 2] * a[8 + x]
                         + b[4 * y + 3] * a[12 + x];
        }
    }

    memcpy(c, temp, 16* sizeof(float));
}

/*
 *	identmat -
 *		make an identity matrix
 */
void GPUImageHSBFilter::identmat(float *matrix)
{
    memset(matrix, 0, 16*sizeof(float));
    matrix[0] = 1.0f;
    matrix[1 * 4 + 1] = 1.0f;
    matrix[2 * 4 + 2] = 1.0f;
    matrix[3 * 4 + 3] = 1.0f;
}

/*
 *	xformpnt -
 *		transform a 3D point using a matrix
 */
void GPUImageHSBFilter::xformpnt(float *matrix, float x, float y, float z, float *tx, float *ty,
                                 float *tz)
{
    *tx = x*matrix[0] + y*matrix[4] + z*matrix[8] + matrix[12];
    *ty = x*matrix[1] + y*matrix[4 + 1] + z*matrix[8 + 1] + matrix[12 + 1];
    *tz = x*matrix[2] + y*matrix[4 + 2] + z*matrix[8 + 2] + matrix[12 + 2];
}

/*
 *	cscalemat -
 *		make a color scale marix
 */
void GPUImageHSBFilter::cscalemat(float *mat, float rscale, float gscale, float bscale)
{
    float mmat[16];

    int idx = 0;
    mmat[idx++] = rscale;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = gscale;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;


    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = bscale;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;
    matrixmult(mmat,mat,mat);
}

/*
 *	saturatemat -
 *		make a saturation marix
 */
void GPUImageHSBFilter::saturatemat(float *mat, float sat)
{
    float mmat[16];
    float a, b, c, d, e, f, g, h, i;
    float rwgt, gwgt, bwgt;

    rwgt = RLUM;
    gwgt = GLUM;
    bwgt = BLUM;

    a = (1.0-sat)*rwgt + sat;
    b = (1.0-sat)*rwgt;
    c = (1.0-sat)*rwgt;
    d = (1.0-sat)*gwgt;
    e = (1.0-sat)*gwgt + sat;
    f = (1.0-sat)*gwgt;
    g = (1.0-sat)*bwgt;
    h = (1.0-sat)*bwgt;
    i = (1.0-sat)*bwgt + sat;

    int idx = 0;
    mmat[idx++] = a;
    mmat[idx++] = b;
    mmat[idx++] = c;
    mmat[idx++] = 0.0;

    mmat[idx++] = d;
    mmat[idx++] = e;
    mmat[idx++] = f;
    mmat[idx++] = 0.0;


    mmat[idx++] = g;
    mmat[idx++] = h;
    mmat[idx++] = i;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;

    matrixmult(mmat,mat,mat);
}

/*
 *	xrotate -
 *		rotate about the x (red) axis
 */
void GPUImageHSBFilter::xrotatemat(float *mat, float rs, float rc)
{
    float mmat[16];

    int idx = 0;
    mmat[idx++] = 1.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = rc;
    mmat[idx++] = rs;
    mmat[idx++] = 0.0;


    mmat[idx++] = 0.0;
    mmat[idx++] = -rs;
    mmat[idx++] = rc;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;

    matrixmult(mmat,mat,mat);
}

/*
 *	yrotate -
 *		rotate about the y (green) axis
 */
void GPUImageHSBFilter::yrotatemat(float *mat, float rs, float rc)
{
    float mmat[16];

    int idx = 0;
    mmat[idx++] = rc;
    mmat[idx++] = 0.0;
    mmat[idx++] = -rs;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;


    mmat[idx++] = rs;
    mmat[idx++] = 0.0;
    mmat[idx++] = rc;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;

    matrixmult(mmat,mat,mat);
}


/*
 *	zrotate -
 *		rotate about the z (blue) axis
 */
void GPUImageHSBFilter::zrotatemat(float *mat, float rs, float rc)
{
    float mmat[16];

    int idx = 0;
    mmat[idx++] = rc;
    mmat[idx++] = rs;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;

    mmat[idx++] = -rs;
    mmat[idx++] = rc;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;


    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;

    matrixmult(mmat,mat,mat);
}

/*
 *	zshear -
 *		shear z using x and y.
 */
void GPUImageHSBFilter::zshearmat(float *mat, float dx, float dy)
{
    float mmat[16];

    int idx = 0;
    mmat[idx++] = 1.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = dx;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;
    mmat[idx++] = dy;
    mmat[idx++] = 0.0;


    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;
    mmat[idx++] = 0.0;

    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 0.0;
    mmat[idx++] = 1.0;

    matrixmult(mmat,mat,mat);
}


/*
 *	huerotatemat -
 *		rotate the hue, while maintaining luminance.
 */
void GPUImageHSBFilter::huerotatemat(float *mat, float rot)
{
    float mmat[16];
    float mag;
    float lx, ly, lz;
    float xrs, xrc;
    float yrs, yrc;
    float zrs, zrc;
    float zsx, zsy;

    identmat(mmat);

    /* rotate the grey vector into positive Z */
    mag = sqrt(2.0);
    xrs = 1.0/mag;
    xrc = 1.0/mag;
    xrotatemat(mmat,xrs,xrc);
    mag = sqrt(3.0);
    yrs = -1.0/mag;
    yrc = sqrt(2.0)/mag;
    yrotatemat(mmat,yrs,yrc);

    /* shear the space to make the luminance plane horizontal */
    xformpnt(mmat,RLUM,GLUM,BLUM,&lx,&ly,&lz);
    zsx = lx/lz;
    zsy = ly/lz;
    zshearmat(mmat,zsx,zsy);

    /* rotate the hue */
    zrs = sin(rot*M_PI/180.0);
    zrc = cos(rot*M_PI/180.0);
    zrotatemat(mmat,zrs,zrc);

    /* unshear the space to put the luminance plane back */
    zshearmat(mmat,-zsx,-zsy);

    /* rotate the grey vector back into place */
    yrotatemat(mmat,-yrs,yrc);
    xrotatemat(mmat,-xrs,xrc);

    matrixmult(mmat,mat,mat);
}

