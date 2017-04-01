package com.lvhiei.cgpuimage;

import android.graphics.SurfaceTexture;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by mj on 17-3-31.
 */

public class CGPUImageRender implements GLSurfaceView.Renderer {

    private int mViewWidth;
    private int mViewHeight;

    private SurfaceTexture mSurfaceTexture;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mViewWidth = width;
        mViewHeight = height;

        nativeCreateFilter(0);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeDraw(mViewWidth, mViewHeight);

        if(null != mSurfaceTexture){
            mSurfaceTexture.updateTexImage();
        }
    }


    public void setSurfaceTexture(SurfaceTexture surfaceTexture){
        mSurfaceTexture = surfaceTexture;
    }


    private native void nativeCreateFilter(int filtertype);
    private native void nativeDraw(int viewWidth, int viewHeight);
}
