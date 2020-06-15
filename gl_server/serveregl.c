// This file declare EGL methods on server side

#include "glserver.h"
#include <EGL/egl.h>


int egl_executeCommand(gls_command_t *c) {
	switch (c->cmd) {
        case GLSC_eglBindAPI:
			glse_eglBindAPI();
			break;
		case GLSC_eglCreateWindowSurface:
			glse_eglCreateWindowSurface();
			break;
		case GLSC_eglCreatePixmapSurface:
			glse_eglCreatePixmapSurface();
			break;
		case GLSC_eglCreatePbufferSurface:
			glse_eglCreatePbufferSurface();
			break;
		case GLSC_eglGetConfigAttrib:
			glse_eglGetConfigAttrib();
			break;
		case GLSC_eglGetCurrentContext:
			glse_eglGetCurrentContext();
			break;
		case GLSC_eglGetCurrentDisplay:
			glse_eglGetCurrentDisplay();
			break;
		case GLSC_eglGetCurrentSurface:
			glse_eglGetCurrentSurface();
			break;
        case GLSC_eglGetError:
			glse_eglGetError();
			break;
		case GLSC_eglInitialize:
			glse_eglInitialize();
			break;
        case GLSC_eglQueryString:
			glse_eglQueryString();
			break;
		case GLSC_eglTerminate:
			glse_eglTerminate();
			break;
/*
		case GLSC_eglXXX:
			glse_eglXXX();
			break:
*/
		default:
			return FALSE;
	}
	
	return TRUE;
}

int egl_flushCommand(gls_command_t *c) {
	switch (c->cmd) {
		// Nothing here to flush
		default:
			return FALSE;
	}
	
	return TRUE;
}


void glse_eglBindAPI()
{
  GLSE_SET_COMMAND_PTR(c, eglBindAPI);
  EGLBoolean success = eglBindAPI(c->api);
  check_gl_err();
  
  gls_ret_eglBindAPI_t *ret = (gls_ret_eglBindAPI_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglBindAPI;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglBindAPI_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglCreateWindowSurface()
{
  GLSE_SET_COMMAND_PTR(c, eglCreateWindowSurface);
  EGLSurface surface = eglGetCurrentSurface(EGL_DRAW); // Stub: current
  // eglCreateWindowSurface(c->dpy, c->config, c->window, c->attrib_list);
  check_gl_err();
  gls_ret_eglCreateWindowSurface_t *ret = (gls_ret_eglCreateWindowSurface_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglCreateWindowSurface;
  ret->surface = surface;
  glse_cmd_send_data(0, sizeof(gls_ret_eglCreateWindowSurface_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglCreatePixmapSurface()
{
  GLSE_SET_COMMAND_PTR(c, eglCreatePixmapSurface);
  EGLSurface surface = eglGetCurrentSurface(EGL_DRAW); // Stub: current
  // eglCreatePixmapSurface(c->dpy, c->config, c->pixmap, c->attrib_list);
  check_gl_err();
  gls_ret_eglCreatePixmapSurface_t *ret = (gls_ret_eglCreatePixmapSurface_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglCreatePixmapSurface;
  ret->surface = surface;
  glse_cmd_send_data(0, sizeof(gls_ret_eglCreatePixmapSurface_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglCreatePbufferSurface()
{
  GLSE_SET_COMMAND_PTR(c, eglCreatePbufferSurface);
  EGLSurface surface = eglGetCurrentSurface(EGL_DRAW); // Stub: current
  // eglCreatePbufferSurface(c->dpy, c->config, c->attrib_list);
  check_gl_err();
  gls_ret_eglCreatePbufferSurface_t *ret = (gls_ret_eglCreatePbufferSurface_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglCreatePbufferSurface;
  ret->surface = surface;
  glse_cmd_send_data(0, sizeof(gls_ret_eglCreatePbufferSurface_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetConfigAttrib()
{
  GLSE_SET_COMMAND_PTR(c, eglGetConfigAttrib);
  gls_ret_eglGetConfigAttrib_t *ret = (gls_ret_eglGetConfigAttrib_t *)glsec_global.tmp_buf.buf;
  
  EGLBoolean success = eglGetConfigAttrib(c->dpy, c->config, c->attribute, &ret->value);
  check_gl_err();
  
  ret->cmd = GLSC_eglGetConfigAttrib;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglGetConfigAttrib_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentContext()
{
  EGLContext context = eglGetCurrentContext();
  check_gl_err();
  
  gls_ret_eglGetCurrentContext_t *ret = (gls_ret_eglGetCurrentContext_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentContext;
  ret->context = context;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentContext_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentDisplay()
{
  EGLDisplay display = eglGetCurrentDisplay();
  check_gl_err();
  
  gls_ret_eglGetCurrentDisplay_t *ret = (gls_ret_eglGetCurrentDisplay_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentDisplay;
  ret->display = display;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentDisplay_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentSurface()
{
  GLSE_SET_COMMAND_PTR(c, eglGetCurrentSurface);
  EGLSurface surface = eglGetCurrentSurface(c->readdraw);
  check_gl_err();
  
  gls_ret_eglGetCurrentSurface_t *ret = (gls_ret_eglGetCurrentSurface_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentSurface;
  ret->surface = surface;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentSurface_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetError()
{
  GLuint error = eglGetError();
  // Should check gl error inside eglGetError() ???
  check_gl_err();
  
  gls_ret_eglGetError_t *ret = (gls_ret_eglGetError_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetError;
  ret->error = error;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetError_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglInitialize() {
  GLSE_SET_COMMAND_PTR(c, eglInitialize);
  EGLBoolean success = EGL_TRUE; // Current stub instead of real init
  // eglInitialize(c->dpy, c->major, c->minor);
  check_gl_err();
  
  gls_ret_eglInitialize_t *ret = (gls_ret_eglInitialize_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglInitialize;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglInitialize_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglQueryString()
{
  GLSE_SET_COMMAND_PTR(c, eglQueryString);
  gls_ret_eglQueryString_t *ret = (gls_ret_eglQueryString_t *)glsec_global.tmp_buf.buf;
  
  const char *params = eglQueryString(c->dpy, c->name);
  check_gl_err();
  
  ret->cmd = GLSC_eglQueryString;
  // LOGD("Client asking for %i, return %s", c->name, params);
  ret->params[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(ret->params, params, GLS_STRING_SIZE);
  glse_cmd_send_data(0,sizeof(gls_ret_eglQueryString_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglTerminate() {
  GLSE_SET_COMMAND_PTR(c, eglTerminate);
  gls_ret_eglTerminate_t *ret = (gls_ret_eglTerminate_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglTerminate;
  ret->success = EGL_TRUE; // Current stub instead of real init
  // eglTerminate(c->dpy);
  check_gl_err();
  
  glse_cmd_send_data(0,sizeof(gls_ret_eglTerminate_t),(char *)glsec_global.tmp_buf.buf);
}

