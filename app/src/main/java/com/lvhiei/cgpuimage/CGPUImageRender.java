package com.lvhiei.cgpuimage;

import android.graphics.SurfaceTexture;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by mj on 17-3-31.
 */

public class CGPUImageRender implements GLSurfaceView.Renderer {

    private Logger logger = new Logger(this.getClass().getName());

    private int mViewWidth;
    private int mViewHeight;

    private int mFrameWidth;
    private int mFrameHeight;

    private int mTextureID;
    private SurfaceTexture mSurfaceTexture;

    TexturePreProcessRender mCameraRender = new TexturePreProcessRender();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        logger.d("onSurfaceCreated");
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        logger.d(String.format("onSurfaceChanged w:%d,h:%d", width, height));

        mViewWidth = width;
        mViewHeight = height;

        mCameraRender.init();
        mCameraRender.initCameraFrameBuffer(mFrameWidth, mFrameHeight);
        mCameraRender.onOutputSizeChanged(mFrameWidth, mFrameHeight);
        nativeCreateFilter(0);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
//        logger.d(String.format("onDrawFrame"));

        int textureId = 0;
        textureId = mCameraRender.onDrawToTexture(mTextureID);

//        logger.d("onDrawFrame tid " + textureId + ",mid " + mTextureID);
        if(null != mSurfaceTexture){
            nativeDraw(textureId, mViewWidth, mViewHeight);
            mSurfaceTexture.updateTexImage();
        }

//        if(null != mSurfaceTexture){
//            mCameraRender.onDrawFrame(mTextureID);
//
//            mSurfaceTexture.updateTexImage();
//        }
    }


    public void setSurfaceTexture(SurfaceTexture surfaceTexture){
        mSurfaceTexture = surfaceTexture;
    }

    public void setTextureId(int textureId){
        mTextureID = textureId;
    }

    public void setFrameSize(int width, int height){
        logger.d(String.format("setFrameSize w:%d,h:%d", width, height));
        mFrameWidth = width;
        mFrameHeight = height;
    }

    public void setFilterPercent(int percent){
        nativeSetFilterPercent(percent);
    }

    private native boolean nativeCreateFilter(int filtertype);
    private native boolean nativeDraw(int textureId, int viewWidth, int viewHeight);
    private native boolean nativeSetFilterPercent(int percent);
}
