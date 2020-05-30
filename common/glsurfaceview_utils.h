
#include <android/native_window.h>
#include <android/native_window_jni.h>


int glsurfaceview_width;
int glsurfaceview_height;

jstring jstrclient_addr;

int   var_server_port;
int   var_client_port;
const char* var_client_addr;

const char* var_path_shadercache = "/sdcard/games/.minecraft/shader_cache";
const char* var_file_fragment_shader = ("%s/fragment_shader.glsl", var_path_shadercache);
const char* var_file_vertex_shader = ("%s/vertex_shader.glsl", var_path_shadercache);

// JNIEnv* glmain_jnienv;

ANativeWindow* glsurfaceview_window;
