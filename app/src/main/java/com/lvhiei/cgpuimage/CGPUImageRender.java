package com.lvhiei.cgpuimage;

import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by mj on 17-3-31.
 */

public class CGPUImageRender implements GLSurfaceView.Renderer {

    public static class FilterType{
        public static int FILTER_3X3_CONVOLUTION = 0;

        public static int FILTER_ADAPTIVE_THRESHOLD = 0;
        public static int FILTER_ADD_BLEND = 0;
        public static int FILTER_ALPHA_BLEND = 0;
        public static int FILTER_AMATORKA = 0;

        public static int FILTER_BILATERAL = 0;
        public static int FILTER_BOXBLUR = 0;
        public static int FILTER_BRIGHTNESS = 0;
        public static int FILTER_BULGE_DISTORTION = 0;

        public static int FILTER_CANNY_EDGE_DETECTION = 0;
        public static int FILTER_CGA_COLORSPACE = 0;
        public static int FILTER_CHROMAKEY_BLEND = 0;
        public static int FILTER_CHROMAKEY = 0;
        public static int FILTER_CLOSING = 0;
        public static int FILTER_COLOR_BLEND = 0;
        public static int FILTER_COLOR_BURN_BLEND = 0;
        public static int FILTER_COLOR_DODGE_BLEND = 0;
        public static int FILTER_COLOR_INVERT = 0;
        public static int FILTER_COLOR_LOCAL_BINARY_PATTERN = 0;
        public static int FILTER_COLOR_MATRIX = 0;
        public static int FILTER_COLOR_PACKING = 0;
        public static int FILTER_COLOUR_FAST_FEATURE_DETECTOR = 0;
        public static int FILTER_COLOUR_FAST_SAMPLING_OPERATION = 0;
        public static int FILTER_CONTRAST = 0;
        public static int FILTER_CROP = 0;
        public static int FILTER_CROSSHATCH = 0;

        public static int FILTER_DARKEN_BLEND = 0;
        public static int FILTER_DIFFERENCE_BLEND = 0;
        public static int FILTER_DILATION = 0;
        public static int FILTER_DIRECTIONAL_NON_MAXIMUM_SUPPRESSION = 0;
        public static int FILTER_DIRECTIONAL_SOBEL_EDGE_DETECTION = 0;
        public static int FILTER_DISSOLVE_BLEND = 0;
        public static int FILTER_DIVIDE_BLEND = 0;

        public static int FILTER_EMBOSS = 0;
        public static int FILTER_EROSION = 0;
        public static int FILTER_EXCLUSION_BLEND = 0;
        public static int FILTER_EXPOSURE = 0;

        public static int FILTER_FALSE_COLOR = 0;

        public static int FILTER_GAMMA = 0;
        public static int FILTER_GAUSSIAN_BLUR = 0;
        public static int FILTER_GAUSSIAN_BLUR_POSITION = 0;
        public static int FILTER_GAUSSIAN_SELECTIVE_BLUR = 0;
        public static int FILTER_GLASS_SPHERE = 0;
        public static int FILTER_GREYSCALE = 0;

        public static int FILTER_HALFTONE = 0;
        public static int FILTER_HARD_LIGHT_BLEND = 0;
        public static int FILTER_HAZE = 0;
        public static int FILTER_HIGHLIGHT_SHADOW = 0;
        public static int FILTER_HIGHLIGHT_SHADOW_TINT = 0;
        public static int FILTER_HSB = 0;
        public static int FILTER_HUE_BLEND = 0;
        public static int FILTER_HUE = 0;

        public static int FILTER_IOS_BLURE = 0;

        public static int FILTER_JFA_VORONOI = 0;

        public static int FILTER_KUWAHARA = 0;
        public static int FILTER_KUWAHARA_RADIUS3 = 0;

        public static int FILTER_LANCZOS_RESAMPLING = 0;
        public static int FILTER_LAPLACIAN = 0;
        public static int FILTER_LEVELS = 0;
        public static int FILTER_LIGHTEN_BLEND = 0;
        public static int FILTER_LINEAR_BURN_BLEND = 0;
        public static int FILTER_LOCAL_BINARY_PATTERN = 0;
        public static int FILTER_LUMINANCE_RANGE = 0;
        public static int FILTER_LUMINANCE_THRESHOLD = 0;
        public static int FILTER_LUMINOSITY_BLEND = 0;

        public static int FILTER_MASK = 0;
        public static int FILTER_MEDIAN = 0;
        public static int FILTER_MISS_ETIKATE = 0;
        public static int FILTER_MONOCHROME = 0;
        public static int FILTER_MOSAIC = 0;
        public static int FILTER_MOTION_BLUR = 0;
        public static int FILTER_MULTIPLY_BLEND = 0;

        public static int FILTER_NON_MAXIMUM_SUPPRESSION = 0;
        public static int FILTER_NORMAL_BLEND = 0;

        public static int FILTER_OPACITY = 0;
        public static int FILTER_OPENING = 0;
        public static int FILTER_OVERLAY_BLEND = 0;

        public static int FILTER_PERLIN_NOISE = 0;
        public static int FILTER_PINCH_DISTORTION = 0;
        public static int FILTER_PIXELLATE = 0;
        public static int FILTER_PIXELLATE_POSITION = 0;
        public static int FILTER_POISSON_BLEND = 0;
        public static int FILTER_POLAR_PIXELLATE = 0;
        public static int FILTER_POLKA_DOT = 0;
        public static int FILTER_POSTERIZE = 0;
        public static int FILTER_PREWITT_EDGE_DETECTION = 0;

        public static int FILTER_RGB_CLOSING = 0;
        public static int FILTER_RGB_DILATION = 0;
        public static int FILTER_RGB_EROSION = 0;
        public static int FILTER_RGB = 0;
        public static int FILTER_RGB_OPENING = 0;

        public static int FILTER_SATURATION_BLEND = 0;
        public static int FILTER_SATURATION = 0;
        public static int FILTER_SCREEN_BLEND = 0;
        public static int FILTER_SEPIA = 0;
        public static int FILTER_SHARPEN = 0;
        public static int FILTER_SINGLE_COMPONENT_GAUSSIAN_BLUR = 0;
        public static int FILTER_SKETCH = 0;
        public static int FILTER_SKIN_TONE = 0;
        public static int FILTER_SMOOTH_TOON = 0;
        public static int FILTER_SOBEL_EDGE_DETECTION = 0;
        public static int FILTER_SOFT_ELEGANCE = 0;
        public static int FILTER_SOFT_LIGHT_BLEND = 0;
        public static int FILTER_SOURCE_OVER_BLEND = 0;
        public static int FILTER_SPHERE_REFRACTION = 0;
        public static int FILTER_STRETCH_DISTORTION = 0;
        public static int FILTER_SUBTRACT_BLEND = 0;
        public static int FILTER_SWIRL = 0;

        public static int FILTER_THRESHOLD_EDGE_DETECTION = 0;
        public static int FILTER_THRESHOLDED_NON_MAXIMUM_SUPPRESSION = 0;
        public static int FILTER_THRESHOLD_SKETCH = 0;
        public static int FILTER_TILT_SHIFT = 0;
        public static int FILTER_TONE_CURVE = 0;
        public static int FILTER_TOON = 0;
        public static int FILTER_TRANSFORM = 0;

        public static int FILTER_UNSHARP_MASK = 0;

        public static int FILTER_VIBRANCE = 0;
        public static int FILTER_VIGNETTE = 0;
        public static int FILTER_VORONOI_CONSUMER = 0;

        public static int FILTER_WEAK_PIXEL_INCLUSION = 0;
        public static int FILTER_WHITE_BALANCE = 0;

        public static int FILTER_XY_DERIVATIVE = 0;
        public static int FILTER_ZOOM = 0;

        public static void init(){
            int i = 0;

            FILTER_3X3_CONVOLUTION = i++;

            FILTER_ADAPTIVE_THRESHOLD = i++;
            FILTER_ADD_BLEND = i++;
            FILTER_ALPHA_BLEND = i++;
            FILTER_AMATORKA = i++;

            FILTER_BILATERAL = i++;
            FILTER_BOXBLUR = i++;
            FILTER_BRIGHTNESS = i++;
            FILTER_BULGE_DISTORTION = i++;

            FILTER_CANNY_EDGE_DETECTION = i++;
            FILTER_CGA_COLORSPACE = i++;
            FILTER_CHROMAKEY_BLEND = i++;
            FILTER_CHROMAKEY = i++;
            FILTER_CLOSING = i++;
            FILTER_COLOR_BLEND = i++;
            FILTER_COLOR_BURN_BLEND = i++;
            FILTER_COLOR_DODGE_BLEND = i++;
            FILTER_COLOR_INVERT = i++;
            FILTER_COLOR_LOCAL_BINARY_PATTERN = i++;
            FILTER_COLOR_MATRIX = i++;
            FILTER_COLOR_PACKING = i++;
            FILTER_COLOUR_FAST_FEATURE_DETECTOR = i++;
            FILTER_COLOUR_FAST_SAMPLING_OPERATION = i++;
            FILTER_CONTRAST = i++;
            FILTER_CROP = i++;
            FILTER_CROSSHATCH = i++;

            FILTER_DARKEN_BLEND = i++;
            FILTER_DIFFERENCE_BLEND = i++;
            FILTER_DILATION = i++;
            FILTER_DIRECTIONAL_NON_MAXIMUM_SUPPRESSION = i++;
            FILTER_DIRECTIONAL_SOBEL_EDGE_DETECTION = i++;
            FILTER_DISSOLVE_BLEND = i++;
            FILTER_DIVIDE_BLEND = i++;

            FILTER_EMBOSS = i++;
            FILTER_EROSION = i++;
            FILTER_EXCLUSION_BLEND = i++;
            FILTER_EXPOSURE = i++;

            FILTER_FALSE_COLOR = i++;

            FILTER_GAMMA = i++;
            FILTER_GAUSSIAN_BLUR = i++;
            FILTER_GAUSSIAN_BLUR_POSITION = i++;
            FILTER_GAUSSIAN_SELECTIVE_BLUR = i++;
            FILTER_GLASS_SPHERE = i++;
            FILTER_GREYSCALE = i++;

            FILTER_HALFTONE = i++;
            FILTER_HARD_LIGHT_BLEND = i++;
            FILTER_HAZE = i++;
            FILTER_HIGHLIGHT_SHADOW = i++;
            FILTER_HIGHLIGHT_SHADOW_TINT = i++;
            FILTER_HSB = i++;
            FILTER_HUE_BLEND = i++;
            FILTER_HUE = i++;

            FILTER_IOS_BLURE = i++;

            FILTER_JFA_VORONOI = i++;

            FILTER_KUWAHARA = i++;
            FILTER_KUWAHARA_RADIUS3 = i++;

            FILTER_LANCZOS_RESAMPLING = i++;
            FILTER_LAPLACIAN = i++;
            FILTER_LEVELS = i++;
            FILTER_LIGHTEN_BLEND = i++;
            FILTER_LINEAR_BURN_BLEND = i++;
            FILTER_LOCAL_BINARY_PATTERN = i++;
            FILTER_LUMINANCE_RANGE = i++;
            FILTER_LUMINANCE_THRESHOLD = i++;
            FILTER_LUMINOSITY_BLEND = i++;

            FILTER_MASK = i++;
            FILTER_MEDIAN = i++;
            FILTER_MISS_ETIKATE = i++;
            FILTER_MONOCHROME = i++;
            FILTER_MOSAIC = i++;
            FILTER_MOTION_BLUR = i++;
            FILTER_MULTIPLY_BLEND = i++;

            FILTER_NON_MAXIMUM_SUPPRESSION = i++;
            FILTER_NORMAL_BLEND = i++;

            FILTER_OPACITY = i++;
            FILTER_OPENING = i++;
            FILTER_OVERLAY_BLEND = i++;

            FILTER_PERLIN_NOISE = i++;
            FILTER_PINCH_DISTORTION = i++;
            FILTER_PIXELLATE = i++;
            FILTER_PIXELLATE_POSITION = i++;
            FILTER_POISSON_BLEND = i++;
            FILTER_POLAR_PIXELLATE = i++;
            FILTER_POLKA_DOT = i++;
            FILTER_POSTERIZE = i++;
            FILTER_PREWITT_EDGE_DETECTION = i++;

            FILTER_RGB_CLOSING = i++;
            FILTER_RGB_DILATION = i++;
            FILTER_RGB_EROSION = i++;
            FILTER_RGB = i++;
            FILTER_RGB_OPENING = i++;

            FILTER_SATURATION_BLEND = i++;
            FILTER_SATURATION = i++;
            FILTER_SCREEN_BLEND = i++;
            FILTER_SEPIA = i++;
            FILTER_SHARPEN = i++;
            FILTER_SINGLE_COMPONENT_GAUSSIAN_BLUR = i++;
            FILTER_SKETCH = i++;
            FILTER_SKIN_TONE = i++;
            FILTER_SMOOTH_TOON = i++;
            FILTER_SOBEL_EDGE_DETECTION = i++;
            FILTER_SOFT_ELEGANCE = i++;
            FILTER_SOFT_LIGHT_BLEND = i++;
            FILTER_SOURCE_OVER_BLEND = i++;
            FILTER_SPHERE_REFRACTION = i++;
            FILTER_STRETCH_DISTORTION = i++;
            FILTER_SUBTRACT_BLEND = i++;
            FILTER_SWIRL = i++;

            FILTER_THRESHOLD_EDGE_DETECTION = i++;
            FILTER_THRESHOLDED_NON_MAXIMUM_SUPPRESSION = i++;
            FILTER_THRESHOLD_SKETCH = i++;
            FILTER_TILT_SHIFT = i++;
            FILTER_TONE_CURVE = i++;
            FILTER_TOON = i++;
            FILTER_TRANSFORM = i++;

            FILTER_UNSHARP_MASK = i++;

            FILTER_VIBRANCE = i++;
            FILTER_VIGNETTE = i++;
            FILTER_VORONOI_CONSUMER = i++;

            FILTER_WEAK_PIXEL_INCLUSION = i++;
            FILTER_WHITE_BALANCE = i++;

            FILTER_XY_DERIVATIVE = i++;
            FILTER_ZOOM = i++;

        }
    }

    static {
        FilterType.init();
    }



    private Logger logger = new Logger(this.getClass().getName());

    private int mViewWidth;
    private int mViewHeight;

    private int mFrameWidth;
    private int mFrameHeight;

    private int mFilterId;


    private Camera mCamera = null;
    private int mTextureId = OpenGLUtils.NO_TEXTURE;

    private SurfaceTexture mSurfaceTexture;
    private int mCameraId = 1;
    private boolean mbCameraSwithed = false;
    private GLSurfaceView mSurfaceView;

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
    TexturePreProcessRender mCameraRender = new TexturePreProcessRender();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        logger.i("onSurfaceCreated");

        while (mCamera == null){
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        setUpCamera();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        logger.i(String.format("onSurfaceChanged w:%d,h:%d,filter:%d", width, height, mFilterId));


        mViewWidth = width;
        mViewHeight = height;

        mCameraRender.init();
        mCameraRender.initCameraFrameBuffer(mFrameWidth, mFrameHeight);
        mCameraRender.onOutputSizeChanged(mFrameWidth, mFrameHeight);
        nativeCreateFilter(mFilterId);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        logger.i(String.format("onDrawFrame"));

        int textureId = 0;
        textureId = mCameraRender.onDrawToTexture(mTextureId);

//        logger.d("onDrawFrame tid " + textureId + ",mid " + mTextureId);
        if(null != mSurfaceTexture){
            nativeDraw(textureId, mViewWidth, mViewHeight);
            mSurfaceTexture.updateTexImage();
        }

//        if(null != mSurfaceTexture){
//            mCameraRender.onDrawFrame(mTextureId);
//
//            mSurfaceTexture.updateTexImage();
//        }
    }

    public void onResume(){
        openCamera(mCameraId);
        mSurfaceView.onResume();
        mSurfaceView.forceLayout();
        mSurfaceView.requestRender();
    }


    public void onPause(){
        closeCamera();
        mSurfaceView.queueEvent(new Runnable() {
            @Override
            public void run() {
                nativeStopRender();
                mCameraRender.destroyFramebuffers();
                mCameraRender.destroy();
                OpenGLUtils.deleteTexture(mTextureId);
                mTextureId = OpenGLUtils.NO_TEXTURE;
                logger.i("deleteTextured.....");
            }
        });
        mSurfaceView.onPause();
        mSurfaceTexture = null;
    }

    public void onDestroy(){

        mSurfaceView = null;
    }

    public void setFrameSize(int width, int height){
        logger.d(String.format("setFrameSize w:%d,h:%d", width, height));
        mFrameWidth = width;
        mFrameHeight = height;
    }

    public void setFilterId(int id){
        mFilterId = id;
    }


    public void setFilterPercent(int percent){
        nativeSetFilterPercent(percent);
    }

    public void setSurfaceView(GLSurfaceView surfaceView){
        mSurfaceView = surfaceView;
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

    public void switchCamera(){
        mCameraId = mCameraId == 0 ? 1 : 0;
        openCamera(mCameraId);
        setUpCamera();
        mbCameraSwithed = true;
    }

    protected void setUpCamera(){

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

        this.setFrameSize(mCamera.getParameters().getPreviewSize().width, mCamera.getParameters().getPreviewSize().height);

        try{
            mCamera.setPreviewTexture(mSurfaceTexture);
            mCamera.startPreview();
        }catch (Throwable t){

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

    private native boolean nativeCreateFilter(int filtertype);
    private native boolean nativeDraw(int textureId, int viewWidth, int viewHeight);
    private native boolean nativeSetFilterPercent(int percent);
    private native boolean nativeStopRender();
    private native void nativeSetFrontCamera(boolean isfront);
}
