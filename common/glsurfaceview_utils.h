#ifdef __ANDROID__

#include <android/native_window.h>
#include <android/native_window_jni.h>

#endif // __ANDROID__

int glsurfaceview_width;
int glsurfaceview_height;


int   var_server_port;
int   var_client_port;
const char* var_client_addr;
/*
const char* var_path_shadercache;
const char* var_file_fragment_shader;
const char* var_file_vertex_shader;
*/
// JNIEnv* glmain_jnienv;

#ifdef __ANDROID__

jstring jstrclient_addr;

ANativeWindow* glsurfaceview_window;
#endif // __ANDROID__

