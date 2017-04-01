package com.lvhiei.cgpuimage;

import android.graphics.Bitmap;
import android.opengl.GLES11Ext;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.os.Environment;
import android.util.Log;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.Calendar;
import java.util.LinkedList;

public class TexturePreProcessRender {

	private static final String CAMERA_INPUT_VERTEX_SHADER = ""+
			"attribute vec4 position;\n" +
            "attribute vec4 inputTextureCoordinate;\n" +
            "\n" +
            "uniform mat4 textureTransform;\n" +
            "varying vec2 textureCoordinate;\n" +
            "\n" +
            "void main()\n" +
            "{\n" +
            "	textureCoordinate = (textureTransform * inputTextureCoordinate).xy;\n" +
            "	gl_Position = position;\n" +
            "}";

	private static final String CAMERA_INPUT_FRAGMENT_SHADER = ""+
			"#extension GL_OES_EGL_image_external : require\n" +
			"//varying highp vec2 textureCoordinate;\n" +
			"\n" +
	         "precision mediump float;\n" +
	         "varying vec2 textureCoordinate;\n" +
			"uniform samplerExternalOES inputImageTexture;\n" +
			"\n" +
			"void main()\n" +
			"{\n" +
			"	gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n" +
			"}";

	private float[] mTextureTransformMatrix = new float[16];
    private int mTextureTransformMatrixLocation;

    private final LinkedList<Runnable> mRunOnDraw;
    private final String mVertexShader;
    private final String mFragmentShader;
    protected int mGLProgId;
    protected int mGLAttribPosition;
    protected int mGLUniformTexture;
    protected int mGLAttribTextureCoordinate;
    protected int mGLStrengthLocation;
    protected int mOutputWidth;
    protected int mOutputHeight;
    protected boolean mIsInitialized;
    protected FloatBuffer mGLCubeBuffer;
    protected FloatBuffer mGLTextureBuffer;
    protected int mDisplayWidth, mDisplayHeight;

    protected  int[] mFrameBuffers = null;
    protected  int[] mFrameBufferTextures = null;
    private int mFrameWidth = -1;
    private int mFrameHeight = -1;

    private final float vertexPoint[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            -1.0f, 1.0f,
            1.0f, 1.0f,
    };

    private final float texturePoint[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
    };

	public TexturePreProcessRender(){
	    mRunOnDraw = new LinkedList<Runnable>();
	    mVertexShader = CAMERA_INPUT_VERTEX_SHADER;
	    mFragmentShader = CAMERA_INPUT_FRAGMENT_SHADER;

	    mGLCubeBuffer = ByteBuffer.allocateDirect(vertexPoint.length * 4)
	                .order(ByteOrder.nativeOrder())
	                .asFloatBuffer();
	    mGLCubeBuffer.put(vertexPoint).position(0);

	    mGLTextureBuffer = ByteBuffer.allocateDirect(texturePoint.length * 4)
	                .order(ByteOrder.nativeOrder())
	                .asFloatBuffer();
	    mGLTextureBuffer.put(texturePoint).position(0);
        Matrix.setIdentityM(mTextureTransformMatrix, 0);
	}

    public void init() {
        onInit();
        mIsInitialized = true;
    }

    protected void onInit() {
        mGLProgId = OpenGLUtils.loadProgram(mVertexShader, mFragmentShader);
        mGLAttribPosition = GLES20.glGetAttribLocation(mGLProgId, "position");
        mGLUniformTexture = GLES20.glGetUniformLocation(mGLProgId, "inputImageTexture");
        mGLAttribTextureCoordinate = GLES20.glGetAttribLocation(mGLProgId,
                "inputTextureCoordinate");
        mIsInitialized = true;
        mTextureTransformMatrixLocation = GLES20.glGetUniformLocation(mGLProgId, "textureTransform");
    }

	public void setTextureTransformMatrix(float[] mtx){
		mTextureTransformMatrix = mtx;
    }

    protected void runOnDraw(final Runnable runnable) {
        synchronized (mRunOnDraw) {
            mRunOnDraw.addLast(runnable);
        }
    }

    public void onDisplaySizeChanged(final int width, final int height) {
    	mDisplayWidth = width;
    	mDisplayHeight = height;
    }

    public void onOutputSizeChanged(final int width, final int height) {
        mOutputWidth = width;
        mOutputHeight = height;
    }

    public final void destroy() {
        mIsInitialized = false;
        GLES20.glDeleteProgram(mGLProgId);
    }

	public int onDrawFrame(int textureId, FloatBuffer vertexBuffer, FloatBuffer textureBuffer) {
        GLES20.glUseProgram(mGLProgId);
        if(!mIsInitialized) {
            return OpenGLUtils.NOT_INIT;
        }
        vertexBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, vertexBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        textureBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, textureBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glUniformMatrix4fv(mTextureTransformMatrixLocation, 1, false, mTextureTransformMatrix, 0);

        if(textureId != OpenGLUtils.NO_TEXTURE){
	        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
	        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureId);
	        GLES20.glUniform1i(mGLUniformTexture, 0);
        }

        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
        GLES20.glDisableVertexAttribArray(mGLAttribPosition);
        GLES20.glDisableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);
        return OpenGLUtils.ON_DRAWN;
	}

	public int onDrawFrame(int textureId) {
        GLES20.glUseProgram(mGLProgId);
        if(!mIsInitialized) {
            return OpenGLUtils.NOT_INIT;
        }
        mGLCubeBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, mGLCubeBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        mGLTextureBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, mGLTextureBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glUniformMatrix4fv(mTextureTransformMatrixLocation, 1, false, mTextureTransformMatrix, 0);

        if(textureId != OpenGLUtils.NO_TEXTURE){
	        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
	        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureId);
	        GLES20.glUniform1i(mGLUniformTexture, 0);
        }

        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
        GLES20.glDisableVertexAttribArray(mGLAttribPosition);
        GLES20.glDisableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);
        return OpenGLUtils.ON_DRAWN;
    }

	public int onDrawToTexture(int textureId) {
		if(mFrameBuffers == null)
			return OpenGLUtils.NO_TEXTURE;

        GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBuffers[0]);

        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mFrameBufferTextures[0]);

		GLES20.glViewport(0, 0,mOutputWidth, mOutputHeight);
    	GLES20.glUseProgram(mGLProgId);
        if(!mIsInitialized) {
            return OpenGLUtils.NOT_INIT;
        }

        mGLCubeBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, mGLCubeBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        mGLTextureBuffer.position(0);
        GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, mGLTextureBuffer);
        GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);

        GLES20.glUniformMatrix4fv(mTextureTransformMatrixLocation, 1, false, mTextureTransformMatrix, 0);

        if(textureId != OpenGLUtils.NO_TEXTURE){
	        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
	        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureId);
	        GLES20.glUniform1i(mGLUniformTexture, 0);
        }

        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
        GLES20.glDisableVertexAttribArray(mGLAttribPosition);
        GLES20.glDisableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);

        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

		GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);

		return mFrameBufferTextures[0];
	}

    public int onDrawToTexture(int textureId, FloatBuffer vertexBuffer, FloatBuffer textureBuffer) {
        if(mFrameBuffers == null)
            return -2;

        GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBuffers[0]);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mFrameBufferTextures[0]);
        GLES20.glViewport(0, 0,mOutputWidth, mOutputHeight);
        GLES20.glUseProgram(mGLProgId);
        if(!mIsInitialized) {
            return -2;
        }

        if(vertexBuffer == null) {
            mGLCubeBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, mGLCubeBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        }else{
            vertexBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, vertexBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        }

        if(textureBuffer == null){
            mGLTextureBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, mGLTextureBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        }else {
            textureBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, textureBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        }

        GLES20.glUniformMatrix4fv(mTextureTransformMatrixLocation, 1, false, mTextureTransformMatrix, 0);

        if(textureId != -1){
            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureId);
            GLES20.glUniform1i(mGLUniformTexture, 0);
        }

        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);

        GLES20.glDisableVertexAttribArray(mGLAttribPosition);
        GLES20.glDisableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);

        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

        GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
        return mFrameBufferTextures[0];
    }

    //===============================================
    public int onDrawToTexture(int textureId, FloatBuffer vertexBuffer, FloatBuffer textureBuffer, ByteBuffer buffer) {
        if(mFrameBuffers == null)
            return -2;

        GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBuffers[0]);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mFrameBufferTextures[0]);
        GLES20.glViewport(0, 0,mOutputWidth, mOutputHeight);
        GLES20.glUseProgram(mGLProgId);
        if(!mIsInitialized) {
            return -2;
        }

        if(vertexBuffer == null) {
            mGLCubeBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, mGLCubeBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        }else{
            vertexBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, vertexBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribPosition);
        }

        if(textureBuffer == null){
            mGLTextureBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, mGLTextureBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        }else {
            textureBuffer.position(0);
            GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, textureBuffer);
            GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);
        }
//        vertexBuffer.position(0);
//        GLES20.glVertexAttribPointer(mGLAttribPosition, 2, GLES20.GL_FLOAT, false, 0, vertexBuffer);
//        GLES20.glEnableVertexAttribArray(mGLAttribPosition);
//        textureBuffer.position(0);
//        GLES20.glVertexAttribPointer(mGLAttribTextureCoordinate, 2, GLES20.GL_FLOAT, false, 0, textureBuffer);
//        GLES20.glEnableVertexAttribArray(mGLAttribTextureCoordinate);

        GLES20.glUniformMatrix4fv(mTextureTransformMatrixLocation, 1, false, mTextureTransformMatrix, 0);

        if(textureId != -1){
            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, textureId);
            GLES20.glUniform1i(mGLUniformTexture, 0);
        }

        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);

        if (buffer != null) {
            long start = System.currentTimeMillis();
            GLES20.glReadPixels(0, 0, mOutputWidth, mOutputHeight, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, buffer);
            long end = System.currentTimeMillis();
            Log.i("vv_read_pixel", "read cost " + (end - start));

//
//            Bitmap image = Bitmap.createBitmap(mOutputWidth, mOutputHeight,
//                    Bitmap.Config.ARGB_8888);
//            buffer.position(0);
//            image.copyPixelsFromBuffer(buffer);
//            handleBitmap(image);
        }

        buffer.position(0);


        GLES20.glDisableVertexAttribArray(mGLAttribPosition);
        GLES20.glDisableVertexAttribArray(mGLAttribTextureCoordinate);
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 0);

        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

        GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
        return mFrameBufferTextures[0];
    }


    static int i = 0;
    public void handleBitmap(Bitmap bitmap) {
        try {
            Calendar now = Calendar.getInstance();
            String bitmapName = String.valueOf(i);
            File folder = new File(Environment.getExternalStorageDirectory() + "/sensetest");
            if (!folder.exists()) {
                folder.mkdir();
            }
//            File myCaptureFile = new File(Environment.getExternalStorageDirectory() + "/sensetest", bitmapName + ".jpg");
            File myCaptureFile = new File(Environment.getExternalStorageDirectory() + "/sensetest/" +  bitmapName + ".jpg");
            i+=1;
            FileOutputStream fos = new FileOutputStream(myCaptureFile);
            BufferedOutputStream bos = new BufferedOutputStream(fos);
            bitmap.compress(Bitmap.CompressFormat.JPEG, 100, bos);
            bos.flush();
            bos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        if(bitmap != null && !bitmap.isRecycled()) {
            bitmap.recycle();
        }

    }
	public void initCameraFrameBuffer(int width, int height) {
		if(mFrameBuffers != null && (mFrameWidth != width || mFrameHeight != height))
			destroyFramebuffers();
        if (mFrameBuffers == null) {
        	mFrameWidth = width;
			mFrameHeight = height;
        	mFrameBuffers = new int[1];
            mFrameBufferTextures = new int[1];

            GLES20.glGenFramebuffers(1, mFrameBuffers, 0);

            GLES20.glGenTextures(1, mFrameBufferTextures, 0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mFrameBufferTextures[0]);
            GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, width, height, 0,
                    GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, null);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                    GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                    GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                    GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
            GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D,
                    GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBuffers[0]);
            GLES20.glFramebufferTexture2D(GLES20.GL_FRAMEBUFFER, GLES20.GL_COLOR_ATTACHMENT0,
                    GLES20.GL_TEXTURE_2D, mFrameBufferTextures[0], 0);

            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);

        }
	}

	public void destroyFramebuffers() {
        if (mFrameBufferTextures != null) {
            GLES20.glDeleteTextures(1, mFrameBufferTextures, 0);
            mFrameBufferTextures = null;
        }
        if (mFrameBuffers != null) {
            GLES20.glDeleteFramebuffers(1, mFrameBuffers, 0);
            mFrameBuffers = null;
        }
        mFrameWidth = -1;
        mFrameHeight = -1;
    }
}
