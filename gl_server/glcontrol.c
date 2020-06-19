/*
Copyright (c) 2013, Shodruky Rhyammer
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#include "glcontrol.h"

//#define DEBUG
void check_gl_err(uint32_t cmd) {
	int glError = glGetError();
	if (glError != 0) {
		LOGD("glGetError(command:%i) return error %p", cmd, glError);
	}
#ifdef DEBUG
	assert(glError == 0)
#endif // DEBUG
}

void init_egl(graphics_context_t *gc)
{
  EGLBoolean r;
  EGLint num_config;

#ifdef RASPBERRY_PI
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;
#endif

  static const EGLint fb_attrib[] = {
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 16,
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_NONE };

  static const EGLint context_attrib[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE };

#ifdef RASPBERRY_PI
  bcm_host_init();
#endif

  gc->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(gc->display != EGL_NO_DISPLAY);
  check_gl_err(eglGetDisplay);

  r = eglInitialize(gc->display, NULL, NULL);
  assert(EGL_FALSE != r);
  check_gl_err(eglInitialize);

  r = eglChooseConfig(gc->display, fb_attrib, &config, 1, &num_config);
  assert(EGL_FALSE != r);
  check_gl_err(eglChooseConfig);

  r = eglBindAPI(EGL_OPENGL_ES_API);
  assert(EGL_FALSE != r);
  check_gl_err(eglBindAPI);

  gc->context = eglCreateContext(gc->display, config, EGL_NO_CONTEXT, context_attrib);
  assert(gc->context != EGL_NO_CONTEXT);
  check_gl_err(eglCreateContext);

#ifdef RASPBERRY_PI
  int32_t ri = graphics_get_display_size(0, &gc->screen_width, &gc->screen_height);
  assert(ri >= 0);

  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.width = gc->screen_width;
  dst_rect.height = gc->screen_height;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.width = gc->screen_width << 16;
  src_rect.height = gc->screen_height << 16;

  gc->d_display = vc_dispmanx_display_open(0);
  gc->d_update = vc_dispmanx_update_start(0);
  gc->d_element = vc_dispmanx_element_add(
    gc->d_update, gc->d_display,
    0, &dst_rect, 0,
    &src_rect, DISPMANX_PROTECTION_NONE, 0 , 0, (DISPMANX_TRANSFORM_T)0);
  gc->d_window.element = gc->d_element;
  gc->d_window.width = gc->screen_width;
  gc->d_window.height = gc->screen_height;
  vc_dispmanx_update_submit_sync(gc->d_update);
  check_gl_err();
  gc->surface = eglCreateWindowSurface(gc->display, config, &gc->d_window, NULL);
#elif defined(__ANDROID__)
  gc->screen_width = glsurfaceview_width; // (gc->d_rect.right - gc->d_rect.left);
  gc->screen_height = glsurfaceview_height; // (gc->d_rect.bottom - gc->d_rect.top);
  // gc->d_window = glsurfaceview_window;
  // assert (glsurfaceview_window != NULL);
  assert (gc->d_window != NULL);
  gc->surface = eglCreateWindowSurface(gc->display, config, gc->d_window, NULL);
#endif
  if (gc->surface == EGL_NO_SURFACE) {
	  gc->surface = eglGetCurrentSurface(EGL_DRAW);
  }
  assert(gc->surface != EGL_NO_SURFACE);
  check_gl_err(eglGetCurrentSurface);

  r = eglMakeCurrent(gc->display, gc->surface, gc->surface, gc->context);
  assert(EGL_FALSE != r);
  check_gl_err(eglMakeCurrent);
}


void release_egl(graphics_context_t *gc)
{
#ifdef RASPBERRY_PI
  vc_dispmanx_element_remove(gc->d_update, gc->d_element);
  vc_dispmanx_display_close(gc->d_display);
#endif

  eglMakeCurrent(gc->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  eglDestroySurface(gc->display, gc->surface);
  eglDestroyContext(gc->display, gc->context);
  eglTerminate(gc->display);
  eglReleaseThread();
}


