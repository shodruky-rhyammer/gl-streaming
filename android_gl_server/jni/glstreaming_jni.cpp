#include <string.h>
#include <jni.h>
#include <android/native_window_jni.h>
#include <assert.h>

#include "main.h"
#include "glserver.h"
#include "glsurfaceview_size.h"

bool need_init_glstream = true;

extern "C"
{
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_initServer(JNIEnv* env, jobject thiz)
	{
		
	}
	
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_setGLSize(JNIEnv* env, jobject thiz, jint width, jint height, jobject surface)
	{
		glmain_jnienv = env;
		
		glsurfaceview_width = width;
		glsurfaceview_height = height;
		
		if (need_init_glstream) {
			need_init_glstream = false;
			
			glsurfaceview_window = ANativeWindow_fromSurface(env, surface);
			init_android_main();
		}
	}
}
