/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.kdt.glstreamserver;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;
import android.view.*;
import android.opengl.GLES20;
import android.graphics.*;

public class GLStreamingView extends TextureView implements TextureView.SurfaceTextureListener {
	private boolean mSurfaceInit = false;
    public GLStreamingView(Context context) {
        this(context, null);
    }

    public GLStreamingView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

	@Override
	public void onSurfaceTextureAvailable(SurfaceTexture texture, int width, int height) {
		System.out.println("Intializing GLStreamServer");
		// System.out.println("w=" + width + ",h=" + height);
		GLStreamingJNIWrapper.setSurface(new Surface(texture));
		GLStreamingJNIWrapper.setGLSize(width, height);
		mSurfaceInit = true;
	}
	
	@Override
	public void onSurfaceTextureUpdated(SurfaceTexture texture) {
		// Unused
	}

	@Override
	public void onSurfaceTextureSizeChanged(final SurfaceTexture texture, final int width, final int height) {
		onSurfaceTextureAvailable(texture, width, height);
	}

	@Override
	public boolean onSurfaceTextureDestroyed(SurfaceTexture texture) {
		// onSurfaceTextureAvailable(texture, 0, 0);
		return false;
	}
	
    public void init(/* boolean translucent, */ int serverPort, String clientAddr, int clientPort) {
		GLStreamingJNIWrapper.initServer(serverPort, clientAddr, clientPort);

		setSurfaceTextureListener(this);
		
		if (isAvailable()) {
			onSurfaceTextureAvailable(getSurfaceTexture(), getWidth(), getHeight());
		}
		
		new Thread(new Runnable(){
				@Override
				public void run() {
					// TODO move to background Service
					try {
						// Wait until Surface is initialized
						while (!mSurfaceInit) Thread.sleep(100);
					} catch (InterruptedException e) {}
					GLStreamingJNIWrapper.startServer();
				}
			}, "GLStreaming").start();
    }

}
