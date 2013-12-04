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

#include "glserver.h"

#define TRUE 1
#define FALSE 0


#define GLSE_SET_COMMAND_PTR(PTR, FUNCNAME) gls_##FUNCNAME##_t *PTR = (gls_##FUNCNAME##_t *)glsec_global.cmd_data;


glse_context_t glsec_global;


static inline void pop_batch_command(size_t size)
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
  ret->screen_width = gc->screen_width;
  ret->screen_height = gc->screen_height;
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


void glse_glBindBuffer()
{
  GLSE_SET_COMMAND_PTR(c, glBindBuffer);
  glBindBuffer(c->target, c->buffer);
  check_gl_err();
}


void glse_glBindTexture()
{
  GLSE_SET_COMMAND_PTR(c, glBindTexture);
  glBindTexture(c->target, c->texture);
  check_gl_err();
}


void glse_glBlendEquationSeparate()
{
  GLSE_SET_COMMAND_PTR(c, glBlendEquationSeparate);
  glBlendEquationSeparate(c->modeRGB, c->modeAlpha);
  check_gl_err();
}


void glse_glBlendFuncSeparate()
{
  GLSE_SET_COMMAND_PTR(c, glBlendFuncSeparate);
  glBlendFuncSeparate(c->srcRGB, c->dstRGB, c->srcAlpha, c->dstAlpha);
  check_gl_err();
}


void glse_glBufferData()
{
  GLSE_SET_COMMAND_PTR(c,glBufferData );
  glBufferData(c->target, c->size, glsec_global.tmp_buf.buf, c->usage);
  check_gl_err();
}


void glse_glBufferSubData()
{
  GLSE_SET_COMMAND_PTR(c, glBufferSubData);
  glBufferSubData(c->target, c->offset, c->size, glsec_global.tmp_buf.buf);
  check_gl_err();
}


void glse_glClear()
{
  GLSE_SET_COMMAND_PTR(c, glClear);
  glClear(c->mask);
  check_gl_err();
}


void glse_glClearColor()
{
  GLSE_SET_COMMAND_PTR(c, glClearColor);
  glClearColor(c->red, c->green, c->blue, c->alpha);
  check_gl_err();
}


void glse_glDeleteBuffers()
{
  GLSE_SET_COMMAND_PTR(c, glDeleteBuffers);
  glDeleteBuffers (c->n, (GLuint *)glsec_global.tmp_buf.buf);
  check_gl_err();
}


void glse_glDrawArrays()
{
  GLSE_SET_COMMAND_PTR(c, glDrawArrays);
  glDrawArrays(c->mode, c->first, c->count);
  check_gl_err();
}


void glse_glEnable()
{
  GLSE_SET_COMMAND_PTR(c, glEnable);
  glEnable(c->cap);
  check_gl_err();
}


void glse_glGenBuffers()
{
  GLSE_SET_COMMAND_PTR(c, glGenBuffers);
  glGenBuffers(c->n, (GLuint*)glsec_global.tmp_buf.buf);
  check_gl_err();
  uint32_t size = c->n * sizeof(uint32_t);
  glse_cmd_send_data(0, size, (char *)glsec_global.tmp_buf.buf);
}


void glse_glGenTextures()
{
  GLSE_SET_COMMAND_PTR(c, glGenTextures);
  glGenTextures(c->n, (GLuint*)glsec_global.tmp_buf.buf);
  check_gl_err();
  uint32_t size = c->n * sizeof(uint32_t);
  glse_cmd_send_data(0, size, (char *)glsec_global.tmp_buf.buf);
}


void glse_glGetAttribLocation()
{
  GLSE_SET_COMMAND_PTR(c, glGetAttribLocation);
  int index = glGetAttribLocation (c->program, c->name);
  check_gl_err();
  gls_ret_glGetAttribLocation_t *ret = (gls_ret_glGetAttribLocation_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_glGetAttribLocation;
  ret->index = index;
  glse_cmd_send_data(0, sizeof(gls_ret_glGetAttribLocation_t), (char *)glsec_global.tmp_buf.buf);
}


void glse_glEnableVertexAttribArray()
{
  GLSE_SET_COMMAND_PTR(c,glEnableVertexAttribArray );
  glEnableVertexAttribArray(c->index);
  check_gl_err();
}



void glse_glVertexAttribPointer()
{
  GLSE_SET_COMMAND_PTR(c, glVertexAttribPointer);
  glVertexAttribPointer(c->indx, c->size, c->type, c->normalized, c->stride, (const GLvoid*)c->ptr);
  check_gl_err();
}


void glse_glBindFramebuffer()
{
  GLSE_SET_COMMAND_PTR(c, glBindFramebuffer);
  glBindFramebuffer(c->target, c->framebuffer);
  check_gl_err();
}


void glse_glViewport()
{
  GLSE_SET_COMMAND_PTR(c, glViewport);
  glViewport(c->x, c->y, c->width, c->height);
  check_gl_err();
}



void glse_glUseProgram()
{
GLSE_SET_COMMAND_PTR(c, glUseProgram);
  glUseProgram(c->program);
  check_gl_err();
}


void glse_glCreateShader()
{
  GLSE_SET_COMMAND_PTR(c, glCreateShader);
  uint32_t obj = glCreateShader(c->type);
  check_gl_err();
  gls_ret_glCreateShader_t *ret = (gls_ret_glCreateShader_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_glCreateShader;
  ret->obj = obj;
  glse_cmd_send_data(0, sizeof(gls_ret_glCreateShader_t), (char *)glsec_global.tmp_buf.buf);
}


void glse_glShaderSource()
{
  GLSE_SET_COMMAND_PTR(c, glShaderSource);
  gls_data_glShaderSource_t *dat = (gls_data_glShaderSource_t *)glsec_global.tmp_buf.buf;
  unsigned int i;
  for (i = 0; i < c->count; i++)
  {
    dat->string[i] = (uint32_t)(dat->data + dat->string[i]);
  }
  glShaderSource(c->shader, c->count, (const GLchar**)dat->string, dat->length);
  check_gl_err();
}


void glse_glCompileShader()
{
  GLSE_SET_COMMAND_PTR(c, glCompileShader);
  glCompileShader(c->shader);
  check_gl_err();
}


void glse_glCreateProgram()
{
  GLuint program = glCreateProgram();
  check_gl_err();
  gls_ret_glCreateProgram_t *ret = (gls_ret_glCreateProgram_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_glCreateProgram;
  ret->program = program;
  glse_cmd_send_data(0, sizeof(gls_ret_glCreateProgram_t), (char *)glsec_global.tmp_buf.buf);
}


void glse_glAttachShader()
{
  GLSE_SET_COMMAND_PTR(c, glAttachShader);
  glAttachShader(c->program, c->shader);
  check_gl_err();
}


void glse_glLinkProgram()
{
  GLSE_SET_COMMAND_PTR(c, glLinkProgram);
  glLinkProgram(c->program);
  check_gl_err();
}


void glse_glDeleteProgram()
{
  GLSE_SET_COMMAND_PTR(c, glDeleteProgram);
  glDeleteProgram(c->program);
  check_gl_err();
}


void glse_glDeleteShader()
{
  GLSE_SET_COMMAND_PTR(c, glDeleteShader);
  glDeleteShader(c->shader);
  check_gl_err();
}


void glse_glUniform1f()
{
  GLSE_SET_COMMAND_PTR(c, glUniform1f);
  glUniform1f(c->location, c->x);
  check_gl_err();
}


void glse_glDisableVertexAttribArray()
{
  GLSE_SET_COMMAND_PTR(c, glDisableVertexAttribArray);
  glDisableVertexAttribArray(c->index);
  check_gl_err();
}


void glse_glDisable()
{
  GLSE_SET_COMMAND_PTR(c, glDisable);
  glDisable(c->cap);
  check_gl_err();
}


void glse_glDrawElements()
{
  GLSE_SET_COMMAND_PTR(c, glDrawElements);
  glDrawElements (c->mode, c->count, c->type, (const GLvoid*)c->indices);
  check_gl_err();
}


void glse_glGetShaderInfoLog()
{
  GLSE_SET_COMMAND_PTR(c, glGetShaderInfoLog);
  gls_ret_glGetShaderInfoLog_t *ret = (gls_ret_glGetShaderInfoLog_t *)glsec_global.tmp_buf.buf;
  uint32_t maxsize = GLSE_TMP_BUFFER_SIZE - (uint32_t)((char*)ret->infolog - (char*)ret) - 256;
  if (c->bufsize > maxsize)
  {
    c->bufsize = maxsize;
  }
  glGetShaderInfoLog(c->shader, c->bufsize, (GLsizei*)&ret->length, (GLchar*)ret->infolog);
  check_gl_err();
  ret->cmd = GLSC_glGetShaderInfoLog;
  uint32_t size = (uint32_t)((char*)ret->infolog - (char*)ret) + ret->length + 1;
  glse_cmd_send_data(0, size, (char *)glsec_global.tmp_buf.buf);
}


void glse_glBindAttribLocation()
{
  GLSE_SET_COMMAND_PTR(c, glBindAttribLocation);
  glBindAttribLocation (c->program, c->index, c->name);
  check_gl_err();
}


void glse_glGetProgramInfoLog()
{
  GLSE_SET_COMMAND_PTR(c, glGetProgramInfoLog);
  gls_ret_glGetProgramInfoLog_t *ret = (gls_ret_glGetProgramInfoLog_t *)glsec_global.tmp_buf.buf;
  uint32_t maxsize = GLSE_TMP_BUFFER_SIZE - (uint32_t)((char*)ret->infolog - (char*)ret) - 256;
  if (c->bufsize > maxsize)
  {
    c->bufsize = maxsize;
  }
  glGetProgramInfoLog(c->program, c->bufsize, (GLsizei*)&ret->length, (GLchar*)ret->infolog);
  check_gl_err();
  ret->cmd = GLSC_glGetProgramInfoLog;
  uint32_t size = (uint32_t)((char*)ret->infolog - (char*)ret) + ret->length + 1;
  glse_cmd_send_data(0, size, (char *)glsec_global.tmp_buf.buf);
}


void glse_glGetUniformLocation()
{
  GLSE_SET_COMMAND_PTR(c, glGetUniformLocation);
  int location = glGetUniformLocation (c->program, (const GLchar*)c->name);
  check_gl_err();
  gls_ret_glGetUniformLocation_t *ret = (gls_ret_glGetUniformLocation_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_glGetUniformLocation;
  ret->location = (int32_t)location;
  glse_cmd_send_data(0, sizeof(gls_ret_glGetUniformLocation_t), (char *)glsec_global.tmp_buf.buf);
}


void glse_glUniform4fv()
{
  GLSE_SET_COMMAND_PTR(c, glUniform4fv);
  glUniform4fv (c->location, c->count, (const GLfloat *)c->v);
  check_gl_err();
}


void glse_glUniformMatrix4fv()
{
  GLSE_SET_COMMAND_PTR(c, glUniformMatrix4fv);
  glUniformMatrix4fv(c->location, c->count, c->transpose, (const GLfloat *)c->value);
  check_gl_err();
}


void glse_glFinish()
{
  GLSE_SET_COMMAND_PTR(c, glFinish);
  glFinish();
  check_gl_err();
  gls_command_t *ret = (gls_command_t *)glsec_global.tmp_buf.buf;
  ret->cmd = c->cmd;
  size_t size = sizeof(gls_command_t);
  glse_cmd_send_data(0, size, glsec_global.tmp_buf.buf);
}


void glse_glFlush()
{
  glFlush();
  check_gl_err();
}


void glse_glTexParameteri()
{
  GLSE_SET_COMMAND_PTR(c, glTexParameteri);
  glTexParameteri (c->target, c->pname, c->param);
  check_gl_err();
}


void glse_glTexImage2D()
{
  GLSE_SET_COMMAND_PTR(c, glTexImage2D);
  glTexImage2D(c->target, c->level, c->internalformat, c->width, c->height, c->border, c->format, c->type, c->pixels);
  check_gl_err();
}


void glse_glDeleteTextures()
{
  GLSE_SET_COMMAND_PTR(c, glDeleteTextures);
  glDeleteTextures(c->n, c->textures);
  check_gl_err();
}


void glse_glPixelStorei()
{
  GLSE_SET_COMMAND_PTR(c, glPixelStorei);
  glPixelStorei(c->pname, c->param);
  check_gl_err();
}


void glse_glActiveTexture()
{
  GLSE_SET_COMMAND_PTR(c, glActiveTexture);
  glActiveTexture(c->texture);
  check_gl_err();
}



/*
void glse_()
{
  GLSE_SET_COMMAND_PTR(c, );

  check_gl_err();
}

  gls_ret__t *ret = (gls_ret__t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_;
  ret-> = ;
  glse_cmd_send_data(0, sizeof(gls_ret__t), (char *)glsec_global.tmp_buf.buf);
*/


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
      case GLSC_glAttachShader:
        glse_glAttachShader();
        pop_batch_command(sizeof(gls_glAttachShader_t));
        break;
      case GLSC_glActiveTexture:
        glse_glActiveTexture();
        pop_batch_command(sizeof(gls_glActiveTexture_t));
        break;
      case GLSC_glBindBuffer:
        glse_glBindBuffer();
        pop_batch_command(sizeof(gls_glBindBuffer_t));
        break;
      case GLSC_glBindTexture:
        glse_glBindTexture();
        pop_batch_command(sizeof(gls_glBindTexture_t));
        break;
      case GLSC_glBindAttribLocation:
        glse_glBindAttribLocation();
        pop_batch_command(sizeof(gls_glBindAttribLocation_t));
        break;
      case GLSC_glBindFramebuffer:
        glse_glBindFramebuffer();
        pop_batch_command(sizeof(gls_glBindFramebuffer_t));
        break;
      case GLSC_glBlendFuncSeparate:
        glse_glBlendFuncSeparate();
        pop_batch_command(sizeof(gls_glBlendFuncSeparate_t));
        break;
      case GLSC_glBlendEquationSeparate:
        glse_glBlendEquationSeparate();
        pop_batch_command(sizeof(gls_glBlendEquationSeparate_t));
        break;
      case GLSC_glClear:
        glse_glClear();
        pop_batch_command(sizeof(gls_glClear_t));
        break;
      case GLSC_glClearColor:
        glse_glClearColor();
        pop_batch_command(sizeof(gls_glClearColor_t));
        break;
      case GLSC_glCompileShader:
        glse_glCompileShader();
        pop_batch_command(sizeof(gls_glCompileShader_t));
        break;
      case GLSC_glDeleteProgram:
        glse_glDeleteProgram();
        pop_batch_command(sizeof(gls_glDeleteProgram_t));
        break;
      case GLSC_glDeleteShader:
        glse_glDeleteShader();
        pop_batch_command(sizeof(gls_glDeleteShader_t));
        break;
      case GLSC_glDeleteTextures:
        glse_glDeleteTextures();
        pop_batch_command(((gls_glDeleteTextures_t *)c)->cmd_size);
        break;
      case GLSC_glDisable:
        glse_glDisable();
        pop_batch_command(sizeof(gls_glDisable_t));
        break;
      case GLSC_glDisableVertexAttribArray:
        glse_glDisableVertexAttribArray();
        pop_batch_command(sizeof(gls_glDisableVertexAttribArray_t));
        break;
      case GLSC_glDrawArrays:
        glse_glDrawArrays();
        pop_batch_command(sizeof(gls_glDrawArrays_t));
        break;
      case GLSC_glDrawElements:
        glse_glDrawElements();
        pop_batch_command(sizeof(gls_glDrawElements_t));
        break;
      case GLSC_glEnable:
        glse_glEnable();
        pop_batch_command(sizeof(gls_glEnable_t));
        break;
      case GLSC_glEnableVertexAttribArray:
        glse_glEnableVertexAttribArray();
        pop_batch_command(sizeof(gls_glEnableVertexAttribArray_t));
        break;
      case GLSC_glFlush:
        glse_glFlush();
        pop_batch_command(sizeof(gls_command_t));
        break;
      case GLSC_glLinkProgram:
        glse_glLinkProgram();
        pop_batch_command(sizeof(gls_glLinkProgram_t));
        break;
      case GLSC_glPixelStorei:
        glse_glPixelStorei();
        pop_batch_command(sizeof(gls_glPixelStorei_t));
        break;
      case GLSC_glTexImage2D:
        glse_glTexImage2D();
        pop_batch_command(((gls_glTexImage2D_t *)c)->cmd_size);
        break;
      case GLSC_glTexParameteri:
        glse_glTexParameteri();
        pop_batch_command(sizeof(gls_glTexParameteri_t));
        break;
      case GLSC_glUniform1f:
        glse_glUniform1f();
        pop_batch_command(sizeof(gls_glUniform1f_t));
        break;
      case GLSC_glUniform4fv:
        glse_glUniform4fv();
        pop_batch_command(((gls_glUniform4fv_t *)c)->cmd_size);
        break;
      case GLSC_glUniformMatrix4fv:
        glse_glUniformMatrix4fv();
        pop_batch_command(((gls_glUniformMatrix4fv_t *)c)->cmd_size);
        break;
      case GLSC_glUseProgram:
        glse_glUseProgram();
        pop_batch_command(sizeof(gls_glUseProgram_t));
        break;
      case GLSC_glVertexAttribPointer:
        glse_glVertexAttribPointer();
        pop_batch_command(sizeof(gls_glVertexAttribPointer_t));
        break;
      case GLSC_glViewport:
        glse_glViewport();
        pop_batch_command(sizeof(gls_glViewport_t));
        break;
/*
      case GLSC_:
        glse_();
        pop_batch_command(sizeof(gls__t));
        break;
*/
      default:
        printf("Error: Command Flush\n");
        quit = TRUE;
        break;
    }
  }
}


void * glserver_thread(void * arg)
{
  int quit = FALSE;
  server_thread_args_t * a = (server_thread_args_t *)arg;
  static graphics_context_t gc;
  memset(&glsec_global, 0, sizeof(glsec_global));
  memset(&gc, 0, sizeof(gc));
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
      switch (c->cmd)
      {
        case GLSC_FLIP:
          glse_cmd_flip();
          break;
        case GLSC_SEND_DATA:
          glse_cmd_recv_data();
          break;
        case GLSC_FLUSH:
          glse_cmd_flush();
          break;
        case GLSC_get_context:
          glse_cmd_get_context();
          break;
        case GLSC_glBufferData:
          glse_glBufferData();
          break;
        case GLSC_glBufferSubData:
          glse_glBufferSubData();
          break;
        case GLSC_glCreateProgram:
          glse_glCreateProgram();
          break;
        case GLSC_glCreateShader:
          glse_glCreateShader();
          break;
        case GLSC_glDeleteBuffers:
          glse_glDeleteBuffers();
          break;
        case GLSC_glFinish:
          glse_glFinish();
          break;
        case GLSC_glGenBuffers:
          glse_glGenBuffers();
          break;
        case GLSC_glGenTextures:
          glse_glGenTextures();
          break;
        case GLSC_glGetAttribLocation:
          glse_glGetAttribLocation();
          break;
        case GLSC_glGetProgramInfoLog:
          glse_glGetProgramInfoLog();
          break;
        case GLSC_glGetShaderInfoLog:
          glse_glGetShaderInfoLog();
          break;
        case GLSC_glGetUniformLocation:
          glse_glGetUniformLocation();
          break;
        case GLSC_glShaderSource:
          glse_glShaderSource();
          break;
        default:
          printf("Error: Command\n");
          break;
      }
      fifo_pop_ptr_next(a->fifo);
    }
  }

  release_egl(&gc);

  free(glsec_global.tmp_buf.buf);
  free(glsec_global.out_buf.buf);

  pthread_exit(NULL);
}


