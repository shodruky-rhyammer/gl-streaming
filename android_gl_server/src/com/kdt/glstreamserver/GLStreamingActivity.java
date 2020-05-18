package com.kdt.glstreamserver;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.opengl.*;


public class GLStreamingActivity extends Activity
{
	private GLStreamingSurfaceView mGLSurface;
	@Override
    public void onCreate(Bundle savedInstanceState)
    {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		mGLSurface = (GLStreamingSurfaceView) findViewById(R.id.main_virtualgl_surfaceview);
	}
	

    @Override
	protected void onPause() {
        super.onPause();
        // mGLSurface.onPause();
    }

    @Override
	protected void onResume() {
        super.onResume();
        // mGLSurface.onResume();
    }
}
