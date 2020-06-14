// This file declare EGL methods on server side

#include "glserver.h"
#include <EGL/egl.h>


int egl_executeCommand(gls_command_t *c) {
	switch (c->cmd) {
        case GLSC_eglQueryString:
			glse_eglQueryString();
			break;
        case GLSC_eglGetError:
			glse_eglGetError();
			break;
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

