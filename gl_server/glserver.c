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
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>

#include "fastlog.h"
#include "glserver.h"


glse_context_t glsec_global;


void pop_batch_command(size_t size)
{
  glsec_global.tmp_buf.ptr = next_ptr(glsec_global.tmp_buf.ptr, size, GLS_ALIGNMENT_BITS);
}


int send_packet(size_t size)
{
  server_thread_args_t *a = glsec_global.sta;
  if (sendto(a->sock_fd, glsec_global.out_buf.buf, size, 0, (struct sockaddr *)&a->sai, sizeof(struct sockaddr_in)) == -1)
  {
    return FALSE;
  }
  gls_sleep(a->max_mbps, size);
  return TRUE;
}


int glse_cmd_send_data(uint32_t offset, uint32_t size, void *data)
{
  gls_cmd_send_data_t *c = (gls_cmd_send_data_t *)glsec_global.out_buf.buf;
  c->cmd = GLSC_SEND_DATA;

  int success = TRUE;
  uint32_t glssize = GLS_DATA_SIZE * 4;
  char *data1 = (char *)data;
  uint32_t offset1;
  for (offset1 = 0; offset1 < size; offset1 += glssize)
  {
    unsigned int size1 = size - offset1;
    c->isLast = (size1 > glssize) ? FALSE : TRUE;
    size1 = (size1 > glssize) ? glssize : size1;
    memcpy(c->data.data_char, data1, size1);
    size_t sendbytes = (size_t)(&c->data.data_char[size1] - (char *)c);
    c->offset = offset + offset1;
    c->size = size1;
    if (send_packet(sendbytes) == FALSE)
    {
      success = FALSE;
    }
    data1 += glssize;
  }
  return success;
}


void glse_cmd_get_context()
{
  gls_cmd_get_context_t *c = (gls_cmd_get_context_t *)glsec_global.cmd_data;
  graphics_context_t *gc = glsec_global.gc;

  gls_ret_get_context_t *ret = (gls_ret_get_context_t *)glsec_global.tmp_buf.buf;
  ret->cmd = c->cmd;
  ret->screen_width = gc->screen_width = glsurfaceview_width;
  ret->screen_height = gc->screen_height = glsurfaceview_height;
  ret->server_version = GLS_VERSION;
  size_t size = sizeof(gls_ret_get_context_t);
  glse_cmd_send_data(0, size, glsec_global.tmp_buf.buf);
}


void glse_cmd_flip()
{
  gls_cmd_flip_t *c = (gls_cmd_flip_t *)glsec_global.cmd_data;
  graphics_context_t *gc = glsec_global.gc;
  eglSwapBuffers(gc->display, gc->surface);
  check_gl_err();
  gls_ret_flip_t *ret = (gls_ret_flip_t *)glsec_global.tmp_buf.buf;
  ret->cmd = c->cmd;
  ret->frame = c->frame;
  size_t size = sizeof(gls_ret_flip_t);
  glse_cmd_send_data(0, size, glsec_global.tmp_buf.buf);
}


int glse_cmd_recv_data()
{
  gls_cmd_send_data_t *c = (gls_cmd_send_data_t *)glsec_global.cmd_data;
  if ((c->offset + c->size > glsec_global.tmp_buf.size) || (glsec_global.tmp_buf.size == 0))
  {
    return FALSE;
  }
  memcpy(&glsec_global.tmp_buf.buf[c->offset], c->data.data_char, c->size);
  return TRUE;
}


void glse_cmd_flush()
{
  glsec_global.tmp_buf.ptr = 0;
  int quit = FALSE;
  while (quit == FALSE)
  {
    gls_command_t *c = (gls_command_t *)(glsec_global.tmp_buf.buf + glsec_global.tmp_buf.ptr);
    glsec_global.cmd_data = c;
    switch (c->cmd)
    {
      case GLSC_BREAK:
        quit = TRUE;
        break;
	  default: {
	    int result = FALSE;
	  	if (c->cmd >= GLSC_eglGetError && c->cmd <= GLSC_eglQueryString) {
			result = egl_flushCommand(c);
		} else if (c->cmd >= GLSC_glActiveTexture) {
			result = gles_flushCommand(c);
		}
		
        if (result == FALSE) {
			LOGE("Error: Command Flush %i", c->cmd);
			quit = TRUE;
		}
		break;
	  }
    }
  }
}

void * glserver_thread(void * arg)
{
  FILE *fl;
#ifdef GL_DEBUG
  fl = fopen("/sdcard/mthr_log.txt", "w");
#endif
  int quit = FALSE;
  server_thread_args_t * a = (server_thread_args_t *)arg;
  static graphics_context_t gc;
  memset(&glsec_global, 0, sizeof(glsec_global));
  memset(&gc, 0, sizeof(gc));
  assert (glsurfaceview_window != NULL);
  gc.d_window = glsurfaceview_window;
  init_egl(&gc);

  glsec_global.sta = a;
  glsec_global.gc = &gc;
  glsec_global.tmp_buf.buf = (char *)malloc(GLSE_TMP_BUFFER_SIZE);
  glsec_global.tmp_buf.size = GLSE_TMP_BUFFER_SIZE;
  glsec_global.out_buf.buf = (char *)malloc(GLSE_OUT_BUFFER_SIZE);
  glsec_global.out_buf.size = GLSE_OUT_BUFFER_SIZE;
  

  while (quit == FALSE)
  {
    void *popptr = (void *)fifo_pop_ptr_get(a->fifo);
    if (popptr == NULL)
    {
      usleep(a->sleep_usec);
    }
    else
    {
      gls_command_t *c = (gls_command_t *)popptr;
      glsec_global.cmd_data = c;
#ifdef GL_DEBUG
      fprintf(fl,"@MainLoop: Attempting to execute command %i \n",c->cmd);
#endif

      switch (c->cmd)
      {
        case GLSC_FLIP:
          glse_cmd_flip();
          break;
        case GLSC_SEND_DATA:
          glse_cmd_recv_data();
          break;
        case GLSC_FLUSH:
#ifdef GL_DEBUG
          fprintf(fl,"@Exec: Flushing command buffer...\n");
#endif
          glse_cmd_flush();
          break;
        case GLSC_get_context:
#ifdef GL_DEBUG
          fprintf(fl,"@Exec: Feeding context to client...\n");
#endif
          glse_cmd_get_context();
          break;
		  
		default: {
		  int result = FALSE;
		  if (c->cmd >= GLSC_eglGetError && c->cmd <= GLSC_eglQueryString) {
			  result = egl_executeCommand(c);
		  } else if (c->cmd >= GLSC_glActiveTexture) {
			  result = gles_executeCommand(c);
		  }
		  
		  if (result == FALSE) {
#ifdef GL_DEBUG
          	fprintf(fl,"@Exec: %i : Undefined command\n",c->cmd);
#endif
		  	LOGE("Error: Undefined command %i", c->cmd);
		  }
          break;
		}
      }
      fifo_pop_ptr_next(a->fifo);
    }
  }

  release_egl(&gc);

  free(glsec_global.tmp_buf.buf);
  free(glsec_global.out_buf.buf);
  fclose(fl);
  pthread_exit(NULL);
}


