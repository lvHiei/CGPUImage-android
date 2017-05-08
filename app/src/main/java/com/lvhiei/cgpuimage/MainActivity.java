package com.lvhiei.cgpuimage;

import android.app.Activity;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
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
            if(mbCameraSwithed){
                mbCameraSwithed = false;
                nativeSetFrontCamera(mCameraId == 1);
            }

            if(null != mSurfaceView){
                mSurfaceView.requestRender();
            }
        }
    };

    private SeekBar mSeekBar;

    private SeekBar.OnSeekBarChangeListener mSeekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if(null != mRender){
                mRender.setFilterPercent(progress);
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {

        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {

        }
    };

    private int mTextureId = OpenGLUtils.NO_TEXTURE;

    private int mCameraId = 1;

    private boolean mbCameraSwithed = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.activity_main);

        Button btn = (Button) findViewById(R.id.cgpuimage_switchCamera);
        btn.setOnClickListener(this);

        mSeekBar = (SeekBar) findViewById(R.id.cgpuimage_seekBar);
        mSeekBar.setOnSeekBarChangeListener(mSeekBarChangeListener);

        copyAssets();

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
            closeCamera();
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



    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.cgpuimage_switchCamera:
                mCameraId = mCameraId == 0 ? 1 : 0;
                openCamera(mCameraId);
                startPreview();
                mbCameraSwithed = true;
                break;
            default:
                break;
        }
    }


    private void copyAssets(){
        String cgpuimagePath = "/sdcard/cgpuimage/";
        File filepath = new File(cgpuimagePath);
        if(!filepath.exists()){
            filepath.mkdir();
        }

        String lookup_amatoka = "lookup_amatorka.rgba";
        String lookup_miss_etikate = "lookup_miss_etikate.rgba";
        String lookup_soft_elegance_1 = "lookup_soft_elegance_1.rgba";
        String lookup_soft_elegance_2 = "lookup_soft_elegance_2.rgba";
        String blend = "blend.rgba";
        String mask = "mask.rgba";
        String squares = "squares.rgba";
        String voroni_points2 = "voroni_points2.rgba";

        copyAssetsToSD(lookup_amatoka, cgpuimagePath + lookup_amatoka);
        copyAssetsToSD(lookup_miss_etikate, cgpuimagePath + lookup_miss_etikate);
        copyAssetsToSD(lookup_soft_elegance_1, cgpuimagePath + lookup_soft_elegance_1);
        copyAssetsToSD(lookup_soft_elegance_2, cgpuimagePath + lookup_soft_elegance_2);
        copyAssetsToSD(blend, cgpuimagePath + blend);
        copyAssetsToSD(mask, cgpuimagePath + mask);
        copyAssetsToSD(squares, cgpuimagePath + squares);
        copyAssetsToSD(voroni_points2, cgpuimagePath + voroni_points2);
    }

    private void copyAssetsToSD(String assetName, String sdFile)
    {
        File file = new File(sdFile);
        if (file.exists()){
            return ;
        }

        InputStream myInput = null;
        OutputStream myOutput = null;
        try {
            myOutput = new FileOutputStream(sdFile);
            myInput = this.getAssets().open(assetName);

            byte[] buffer = new byte[1024];
            int length = myInput.read(buffer);
            while (length > 0) {
                myOutput.write(buffer, 0, length);
                length = myInput.read(buffer);
            }

            myOutput.flush();

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (null != myInput) {
                    myInput.close();
                }

                if (null != myOutput) {
                    myOutput.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    private native void nativeSetFrontCamera(boolean isfront);

}
