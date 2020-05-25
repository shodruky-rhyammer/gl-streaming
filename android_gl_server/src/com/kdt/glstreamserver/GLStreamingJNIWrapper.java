package com.kdt.glstreamserver;
import android.view.*;

public class GLStreamingJNIWrapper
{
	public static native void initServer(int serverPort, String clientAddr, int clientPort);
	public static native void setGLSize(int width, int height, Surface surface);

	public static void step() {
		// TODO implement in native
	}
	
	static {
		System.loadLibrary("glstreamserver");
	}
}
