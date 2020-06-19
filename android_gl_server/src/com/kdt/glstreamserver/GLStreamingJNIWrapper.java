package com.kdt.glstreamserver;
import android.view.*;

public class GLStreamingJNIWrapper
{
	public static native void initServer(int serverPort, String clientAddr, int clientPort);
	public static native void setGLSize(int width, int height);
	public static native void setSurface(Surface surface);
	public static native void startServer();

	public static void step() {
		// TODO implement in native
	}
	
	static {
		System.loadLibrary("glstreamserver");
	}
}
