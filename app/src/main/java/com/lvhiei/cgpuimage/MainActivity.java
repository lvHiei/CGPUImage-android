package com.lvhiei.cgpuimage;

import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.TextureView;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private Camera mCamera;

    private GLSurfaceView mSurfaceView;
    private CGPUImageRender mRender;
    private SurfaceTexture mSurfaceTexture;
    private SurfaceTexture.OnFrameAvailableListener mOnFrameAvailableListener = new SurfaceTexture.OnFrameAvailableListener() {
        @Override
        public void onFrameAvailable(SurfaceTexture surfaceTexture) {
            if(null != mSurfaceView){
                mSurfaceView.requestRender();
            }
        }
    };

    private int mTextureId = OpenGLUtils.NO_TEXTURE;

    private int mCameraId = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mRender = new CGPUImageRender();

        mSurfaceView = (GLSurfaceView) findViewById(R.id.cgpuimage_surface_id);
        mSurfaceView.setEGLContextClientVersion(2);
        mSurfaceView.setRenderer(mRender);
        mSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }


    @Override
    protected void onResume() {
        super.onResume();

        openCamera(mCameraId);
        startPreview();
    }

    private boolean openCamera(int id){
        try {
            mCamera = Camera.open(id);
            if(null == mCamera){
                return false;
            }

            Camera.Parameters parameters = mCamera.getParameters();
            parameters.setPreviewSize(getCameraPreviewSize().width, getCameraPreviewSize().height);
            int[] fpsrange = getCameraFpsRange();
            parameters.setPreviewFpsRange(fpsrange[0], fpsrange[1]);
            mCamera.setParameters(parameters);
        }catch (Throwable t){
            try {
                if(null != mCamera){
                    mCamera.release();
                }
                return false;
            }catch (Throwable throwable){
                return false;
            }
        }

        return true;
    }

    private Camera.Size getCameraPreviewSize(){
        if(null == mCamera){
            throw new RuntimeException("camera is null!");
        }

        List<Camera.Size> supportedsize = mCamera.getParameters().getSupportedPreviewSizes();

        for(Camera.Size size : supportedsize){
            if(size.width == 1280 && size.height == 720){
                return size;
            }
        }

        for(Camera.Size size : supportedsize){
            if(size.width == 640 && size.height == 480){
                return size;
            }
        }

        throw new RuntimeException("camerasize not support!");
    }

    private int[] getCameraFpsRange(){
        if(null == mCamera){
            throw new RuntimeException("camera is null!");
        }

        List<int []> supportFpsRange = mCamera.getParameters().getSupportedPreviewFpsRange();

        for(int [] ragne : supportFpsRange){
            if(ragne[1] >= 25){
                return ragne;
            }
        }

        return supportFpsRange.get(0);
    }

    private void startPreview(){

        if(OpenGLUtils.NO_TEXTURE == mTextureId){
            mTextureId = OpenGLUtils.getExternalOESTextureID();
        }

        if(null == mSurfaceTexture){
            mSurfaceTexture = new SurfaceTexture(mTextureId);
            mSurfaceTexture.setOnFrameAvailableListener(mOnFrameAvailableListener);
        }

        mRender.setSurfaceTexture(mSurfaceTexture);

        try{
            mCamera.setPreviewTexture(mSurfaceTexture);
            mCamera.startPreview();
        }catch (Throwable t){

        }
    }

}
