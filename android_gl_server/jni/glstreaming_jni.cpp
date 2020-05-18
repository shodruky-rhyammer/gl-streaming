#include <string.h>
#include <jni.h>
#include <android/native_window_jni.h>
#include <assert.h>

#include "main.h"
#include "glserver.h"
#include "glsurfaceview_size.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
extern "C"
{
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_initServer(JNIEnv* env, jobject thiz)
	{
		
	}
	
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_setGLSize(JNIEnv* env, jobject thiz, jint width, jint height, jobject surface)
	{
		// glserver_thread(width, height, (void*) "-s 127.0.0.1:6272");
		// glViewport(0, 0, width, height);
		
		assert (surface != NULL);
		
		glsurfaceview_window = ANativeWindow_fromSurface(env, surface);
		assert (glsurfaceview_window != NULL);
		glsurfaceview_width = width;
		glsurfaceview_height = height;
		
		init_android_main();
	}
}
