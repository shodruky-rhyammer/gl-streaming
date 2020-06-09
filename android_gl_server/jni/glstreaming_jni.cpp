#include <string.h>
#include <jni.h>
#include <android/native_window_jni.h>
#include <assert.h>

#include "main.h"
#include "glserver.h"

bool need_init_glstream = true;

extern "C"
{
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_initServer(JNIEnv* env, jobject thiz, jint serverPort, jstring clientAddr, jint clientPort)
	{
		var_server_port = serverPort;
		jstrclient_addr = clientAddr;
		var_client_port = clientPort;
		
		var_client_addr = env->GetStringUTFChars(jstrclient_addr, 0);
		
		var_path_shadercache = "/sdcard/games/.minecraft/shader_cache";
		var_file_fragment_shader = "/sdcard/games/.minecraft/shader_cache/fragment_shader.glsl";
		var_file_vertex_shader = "/sdcard/games/.minecraft/shader_cache/vertex_shader.glsl";
	}
	
	JNIEXPORT void JNICALL Java_com_kdt_glstreamserver_GLStreamingJNIWrapper_setGLSize(JNIEnv* env, jobject thiz, jint width, jint height, jobject surface)
	{
		// glmain_jnienv = env;
		
		glsurfaceview_width = width;
		glsurfaceview_height = height;
		
		if (need_init_glstream) {
			need_init_glstream = false;
			
			glsurfaceview_window = ANativeWindow_fromSurface(env, surface);

			init_android_main();
			env->ReleaseStringUTFChars(jstrclient_addr, var_client_addr);
		}
	}
}
