package com.lvhiei.cgpuimage;

import android.app.Activity;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.TextureView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends Activity implements View.OnClickListener{

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("cgpuimage");
    }

    private Logger logger = new Logger(this.getClass().getName());

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

    private int mCameraId = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.activity_main);

        Button btn = (Button) findViewById(R.id.cgpuimage_test_button);
        btn.setOnClickListener(this);
        btn.setVisibility(View.GONE);

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

    @Override
    protected void onPause() {
        super.onPause();

        closeCamera();
    }

    private boolean openCamera(int id){
        try {
            mCamera = Camera.open(id);
            if(null == mCamera){
                logger.e("opencamera failed id " + id);
                return false;
            }

            Camera.Parameters parameters = mCamera.getParameters();
            parameters.setPreviewSize(getCameraPreviewSize().width, getCameraPreviewSize().height);
            int[] fpsrange = getCameraFpsRange();
            parameters.setPreviewFpsRange(fpsrange[0], fpsrange[1]);
            mCamera.setParameters(parameters);
        }catch (Exception e){
            logger.e("opencamera get some error");
            e.printStackTrace();
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

    private void closeCamera(){
        if(mCamera != null){
            mCamera.stopPreview();
            mCamera.release();
            mCamera = null;
        }
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

        if(mCamera == null){
            return;
        }

        if(OpenGLUtils.NO_TEXTURE == mTextureId){
            mTextureId = OpenGLUtils.getExternalOESTextureID();
        }

        if(null == mSurfaceTexture){
            mSurfaceTexture = new SurfaceTexture(mTextureId);
            mSurfaceTexture.setOnFrameAvailableListener(mOnFrameAvailableListener);
        }

        mRender.setFrameSize(mCamera.getParameters().getPreviewSize().width, mCamera.getParameters().getPreviewSize().height);
        mRender.setSurfaceTexture(mSurfaceTexture);
        mRender.setTextureId(mTextureId);

        try{
            mCamera.setPreviewTexture(mSurfaceTexture);
            mCamera.startPreview();
        }catch (Throwable t){

        }
    }


    private native void nativeSetFrontCamera(boolean isfront);

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.cgpuimage_test_button:
                openCamera(mCameraId);
                startPreview();
                break;
            default:
                break;
        }
    }
}
