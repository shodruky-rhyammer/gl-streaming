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
#include <string.h>
#include <sys/time.h>

#include "glclient.h"
#include "rpi/GLES2/gl2.h"


#define GLS_TMP_BUFFER_SIZE 2097152
#define GLS_OUT_BUFFER_SIZE 2048
#define TRUE 1
#define FALSE 0
#define BATCH_AUTO_FLUSH_SIZE 8128
#define GLS_TIMEOUT_SEC 3.0f


gls_context_t glsc_global;


int gls_cmd_flush();


static inline float get_diff_time(struct timeval start, struct timeval end)
{
  float dt = (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec) * 0.000001f;
  return dt;
}


static inline void push_batch_command(size_t size)
{
  glsc_global.tmp_buf.ptr = next_ptr(glsc_global.tmp_buf.ptr, size, GLS_ALIGNMENT_BITS);
  if (glsc_global.tmp_buf.ptr > BATCH_AUTO_FLUSH_SIZE)
  {
    gls_cmd_flush();
  }
}


int gls_init(server_thread_args_t *arg)
{
  memset(&glsc_global, 0, sizeof(glsc_global));
  glsc_global.sta = arg;
  glsc_global.out_buf.buf = (char *)malloc(GLS_OUT_BUFFER_SIZE);
  if (glsc_global.out_buf.buf == NULL)
  {
    return FALSE;
  }
  glsc_global.tmp_buf.buf = (char *)malloc(GLS_TMP_BUFFER_SIZE);
  if (glsc_global.tmp_buf.buf == NULL)
  {
    free(glsc_global.out_buf.buf);
    return FALSE;
  }
  glsc_global.out_buf.size = GLS_OUT_BUFFER_SIZE;
  glsc_global.tmp_buf.size = GLS_TMP_BUFFER_SIZE;
  glsc_global.out_buf.ptr = 0;
  glsc_global.tmp_buf.ptr = 0;
  return TRUE;
}


int gls_free()
{
  free(glsc_global.out_buf.buf);
  free(glsc_global.tmp_buf.buf);
  return TRUE;
}


int send_packet(size_t size)
{
  server_thread_args_t *a = glsc_global.sta;
  if (sendto(a->sock_fd, glsc_global.out_buf.buf, size, 0, (struct sockaddr *)&a->sai, sizeof(struct sockaddr_in)) == -1)
  {
    return FALSE;
  }
  gls_sleep(a->max_mbps, size);
  return TRUE;
}


int gls_cmd_recv_data()
{
  gls_cmd_send_data_t *c = (gls_cmd_send_data_t *)glsc_global.cmd_data;
  if ((c->offset + c->size > glsc_global.tmp_buf.size) || (glsc_global.tmp_buf.size == 0))
  {
    return c->isLast;
  }
  memcpy(&glsc_global.tmp_buf.buf[c->offset], c->data.data_char, c->size);
  return c->isLast;
}


int wait_for_data(char *str)
{
  server_thread_args_t *a = glsc_global.sta;
  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  int quit = FALSE;
  while (quit == FALSE)
  {
    void *popptr = (void *)fifo_pop_ptr_get(a->fifo);
    if (popptr == NULL)
    {
      gettimeofday(&end_time, NULL);
      float diff_time = get_diff_time(start_time, end_time);
      if (diff_time > GLS_TIMEOUT_SEC)
      {
        printf("\n%s\n", str);
        return FALSE;
      }
      usleep(a->sleep_usec);
    }
    else
    {
      gls_command_t *c = (gls_command_t *)popptr;
      glsc_global.cmd_data = popptr;
      switch (c->cmd)
      {
        case GLSC_SEND_DATA:
          if (gls_cmd_recv_data() == TRUE)
          {
            quit = TRUE;
          }
          break;
        default:
          break;
      }
      fifo_pop_ptr_next(a->fifo);
    }
  }
  return TRUE;
}


int gls_cmd_send_data(uint32_t offset, uint32_t size, void *data)
{
  gls_cmd_send_data_t *c = (gls_cmd_send_data_t *)glsc_global.out_buf.buf;
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


int gls_cmd_get_context()
{
  gls_cmd_flush();
  gls_cmd_get_context_t *c = (gls_cmd_get_context_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_get_context;
  if (send_packet(sizeof(gls_cmd_get_context_t)) == FALSE)
  {
    return FALSE;
  }

  wait_for_data("timeout:gls_cmd_get_context");
  gls_ret_get_context_t *ret = (gls_ret_get_context_t *)glsc_global.tmp_buf.buf;
  if (ret->cmd == GLSC_get_context)
  {
    glsc_global.screen_width = ret->screen_width;
    glsc_global.screen_height = ret->screen_height;
  }
  return TRUE;
}


int gls_cmd_flip(unsigned int frame)
{
  gls_cmd_flush();
  gls_cmd_flip_t *c = (gls_cmd_flip_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_FLIP;
  c->frame = frame;
  if (send_packet(sizeof(gls_cmd_flip_t)) == FALSE)
  {
    return FALSE;
  }

  wait_for_data("timeout:gls_cmd_flip");
  return TRUE;
}


int gls_cmd_flush()
{
  if (glsc_global.tmp_buf.ptr == 0)
  {
    return FALSE;
  }
  gls_command_t *c = (gls_command_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_BREAK;
  glsc_global.tmp_buf.ptr = next_ptr(glsc_global.tmp_buf.ptr, sizeof(gls_command_t), GLS_ALIGNMENT_BITS);
  gls_cmd_send_data(0, glsc_global.tmp_buf.ptr, (void *)glsc_global.tmp_buf.buf);
  glsc_global.tmp_buf.ptr = 0;

  c = (gls_command_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_FLUSH;
  send_packet(sizeof(gls_command_t));
  return TRUE;
}


GL_APICALL void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer)
{
  gls_glBindBuffer_t *c = (gls_glBindBuffer_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glBindBuffer;
  c->target = target;
  c->buffer = buffer;
  push_batch_command(sizeof(gls_glBindBuffer_t));
}


GL_APICALL void GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  gls_glBlendFuncSeparate_t *c = (gls_glBlendFuncSeparate_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glBlendFuncSeparate;
  c->srcRGB = srcRGB;
  c->dstRGB = dstRGB;
  c->srcAlpha = srcAlpha;
  c->dstAlpha = dstAlpha;
  push_batch_command(sizeof(gls_glBlendFuncSeparate_t));
}


GL_APICALL void GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)
{
  gls_glBlendEquationSeparate_t *c = (gls_glBlendEquationSeparate_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glBlendEquationSeparate;
  c->modeRGB = modeRGB;
  c->modeAlpha = modeAlpha;
  push_batch_command(sizeof(gls_glBlendEquationSeparate_t));
}


GL_APICALL void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
  gls_cmd_flush();
  gls_cmd_send_data(0, (uint32_t)size, (void *)data);

  gls_glBufferData_t *c = (gls_glBufferData_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glBufferData;
  c->target = target;
  c->size = size;
  c->usage = usage;
  send_packet(sizeof(gls_glBufferData_t));
}


GL_APICALL void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
  gls_cmd_flush();
  gls_cmd_send_data(0, (uint32_t)size, (void *)data);

  gls_glBufferSubData_t *c = (gls_glBufferSubData_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glBufferSubData;
  c->target = target;
  c->offset = offset;
  c->size = size;
  send_packet(sizeof(gls_glBufferSubData_t));
}


GL_APICALL void GL_APIENTRY glClear (GLbitfield mask)
{
  gls_glClear_t *c = (gls_glClear_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glClear;
  c->mask = mask;
  push_batch_command(sizeof(gls_glClear_t));
}


GL_APICALL void GL_APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  gls_glClearColor_t *c = (gls_glClearColor_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glClearColor;
  c->red = red;
  c->green = green;
  c->blue = blue;
  c->alpha = alpha;
  push_batch_command(sizeof(gls_glClearColor_t));
}


GL_APICALL void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint* buffers)
{
  gls_cmd_flush();
  uint32_t size = n * sizeof(uint32_t);
  gls_cmd_send_data(0, size, (void *)buffers);

  gls_glDeleteBuffers_t *c = (gls_glDeleteBuffers_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glDeleteBuffers;
  c->n = n;
  send_packet(sizeof(gls_glDeleteBuffers_t));
}


GL_APICALL void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
  gls_glDrawArrays_t *c = (gls_glDrawArrays_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDrawArrays;
  c->mode = mode;
  c->first = first;
  c->count = count;
  push_batch_command(sizeof(gls_glDrawArrays_t));
}


GL_APICALL void GL_APIENTRY glEnable (GLenum cap)
{
  gls_glEnable_t *c = (gls_glEnable_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glEnable;
  c->cap = cap;
  push_batch_command(sizeof(gls_glEnable_t));
}


GL_APICALL void GL_APIENTRY glGenBuffers (GLsizei n, GLuint* buffers)
{
  gls_cmd_flush();
  gls_glGenBuffers_t *c = (gls_glGenBuffers_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glGenBuffers;
  c->n = n;
  send_packet(sizeof(gls_glGenBuffers_t));

  wait_for_data("timeout:glGenBuffers");
  memcpy(buffers, glsc_global.tmp_buf.buf, c->n * sizeof(uint32_t));
}


GL_APICALL int GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar* name)
{
  gls_cmd_flush();
  gls_glGetAttribLocation_t *c = (gls_glGetAttribLocation_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glGetAttribLocation;
  c->program = program;
  c->name[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(c->name, name, GLS_STRING_SIZE);
  send_packet(sizeof(gls_glGetAttribLocation_t));

  wait_for_data("timeout:glGetAttribLocation");
  gls_ret_glGetAttribLocation_t *ret = (gls_ret_glGetAttribLocation_t *)glsc_global.tmp_buf.buf;
  return ret->index;
}


GL_APICALL void GL_APIENTRY glEnableVertexAttribArray (GLuint index)
{
  gls_glEnableVertexAttribArray_t *c = (gls_glEnableVertexAttribArray_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glEnableVertexAttribArray;
  c->index = index;
  push_batch_command(sizeof(gls_glEnableVertexAttribArray_t));
}


GL_APICALL void GL_APIENTRY glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
  gls_glVertexAttribPointer_t *c = (gls_glVertexAttribPointer_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glVertexAttribPointer;
  c->indx = indx;
  c->size = size;
  c->type = type;
  c->normalized = normalized;
  c->stride = stride;
  c->ptr = (uint32_t)ptr;
  push_batch_command(sizeof(gls_glVertexAttribPointer_t));
}


GL_APICALL void GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer)
{
  gls_glBindFramebuffer_t *c = (gls_glBindFramebuffer_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glBindFramebuffer;
  c->target = target;
  c->framebuffer = framebuffer;
  push_batch_command(sizeof(gls_glBindFramebuffer_t));
}


GL_APICALL void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
  gls_glViewport_t *c = (gls_glViewport_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glViewport;
  c->x = x;
  c->y = y;
  c->width = width;
  c->height = height;
  push_batch_command(sizeof(gls_glViewport_t));
}


GL_APICALL void GL_APIENTRY glUseProgram (GLuint program)
{
  gls_glUseProgram_t *c = (gls_glUseProgram_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glUseProgram;
  c->program = program;
  push_batch_command(sizeof(gls_glUseProgram_t));
}


GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type)
{
  gls_cmd_flush();
  gls_glCreateShader_t *c = (gls_glCreateShader_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glCreateShader;
  c->type = type;
  send_packet(sizeof(gls_glCreateShader_t));

  wait_for_data("timeout:glCreateShader");
  gls_ret_glCreateShader_t *ret = (gls_ret_glCreateShader_t *)glsc_global.tmp_buf.buf;
  return ret->obj;
}


GL_APICALL void GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
  gls_cmd_flush();
  if (count > 256)
  {
    return;
  }
  gls_data_glShaderSource_t *dat = (gls_data_glShaderSource_t *)glsc_global.tmp_buf.buf;
  size_t size_all = (size_t)(dat->data - (char *)dat);
  uint32_t stroffset = 0;
  unsigned int i;
  for (i = 0; i < count; i++)
  {
    char *strptr = (char *)string[i];
    size_t strsize;
    if (length == NULL)
    {
      strsize = 0;
    }
    else
    {
      strsize = length[i];
    }
    if (strsize == 0)
    {
      strsize = strnlen(strptr, 0xA00000);
    }
    if (strsize > 0x100000)
    {
      return;
    }
    size_all += strsize + 1;
    if (size_all > GLS_TMP_BUFFER_SIZE)
    {
      return;
    }
    dat->string[i] = stroffset;
    dat->length[i] = strsize;
    memcpy(&dat->data[stroffset], strptr, strsize + 1);
    dat->data[stroffset + strsize] = '\0';
    stroffset = stroffset + strsize + 1;
  }

  gls_cmd_send_data(0, size_all, glsc_global.tmp_buf.buf);
  gls_glShaderSource_t *c = (gls_glShaderSource_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glShaderSource;
  c->shader = shader;
  c->count = count;
  send_packet(sizeof(gls_glShaderSource_t));
}


GL_APICALL void GL_APIENTRY glCompileShader (GLuint shader)
{
  gls_glCompileShader_t *c = (gls_glCompileShader_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glCompileShader;
  c->shader = shader;
  push_batch_command(sizeof(gls_glCompileShader_t));
}


GL_APICALL GLuint GL_APIENTRY glCreateProgram (void)
{
  gls_cmd_flush();
  gls_glCreateProgram_t *c = (gls_glCreateProgram_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glCreateProgram;
  send_packet(sizeof(gls_glCreateProgram_t));

  wait_for_data("timeout:glCreateProgram");
  gls_ret_glCreateProgram_t *ret = (gls_ret_glCreateProgram_t *)glsc_global.tmp_buf.buf;
  return ret->program;
}


GL_APICALL void GL_APIENTRY glAttachShader (GLuint program, GLuint shader)
{
  gls_glAttachShader_t *c = (gls_glAttachShader_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glAttachShader;
  c->program = program;
  c->shader = shader;
  push_batch_command(sizeof(gls_glAttachShader_t));
}


GL_APICALL void GL_APIENTRY glLinkProgram (GLuint program)
{
  gls_glLinkProgram_t *c = (gls_glLinkProgram_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glLinkProgram;
  c->program = program;
  push_batch_command(sizeof(gls_glLinkProgram_t));
}


GL_APICALL void GL_APIENTRY glDeleteProgram (GLuint program)
{
  gls_glDeleteProgram_t *c = (gls_glDeleteProgram_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDeleteProgram;
  c->program = program;
  push_batch_command(sizeof(gls_glDeleteProgram_t));
}


GL_APICALL void GL_APIENTRY glDeleteShader (GLuint shader)
{
  gls_glDeleteShader_t *c = (gls_glDeleteShader_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDeleteShader;
  c->shader = shader;
  push_batch_command(sizeof(gls_glDeleteShader_t));
}


GL_APICALL void GL_APIENTRY glUniform1f (GLint location, GLfloat x)
{
  gls_glUniform1f_t *c = (gls_glUniform1f_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glUniform1f;
  c->location = location;
  c->x = x;
  push_batch_command(sizeof(gls_glUniform1f_t));
}


GL_APICALL void GL_APIENTRY glDisableVertexAttribArray (GLuint index)
{
  gls_glDisableVertexAttribArray_t *c = (gls_glDisableVertexAttribArray_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDisableVertexAttribArray;
  c->index = index;
  push_batch_command(sizeof(gls_glDisableVertexAttribArray_t));
}


GL_APICALL void GL_APIENTRY glDisable (GLenum cap)
{
  gls_glDisable_t *c = (gls_glDisable_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDisable;
  c->cap = cap;
  push_batch_command(sizeof(gls_glDisable_t));
}


GL_APICALL void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
  gls_glDrawElements_t *c = (gls_glDrawElements_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glDrawElements;
  c->mode = mode;
  c->count = count;
  c->type = type;
  c->indices = (uint32_t)indices;
  push_batch_command(sizeof(gls_glDrawElements_t));
}


GL_APICALL void GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
  gls_cmd_flush();
  gls_glGetShaderInfoLog_t *c = (gls_glGetShaderInfoLog_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glGetShaderInfoLog;
  c->shader = shader;
  c->bufsize = bufsize;
  send_packet(sizeof(gls_glGetShaderInfoLog_t));

  wait_for_data("timeout:glGetShaderInfoLog");
  gls_ret_glGetShaderInfoLog_t *ret = (gls_ret_glGetShaderInfoLog_t *)glsc_global.tmp_buf.buf;
  if (length != NULL)
  {
    *length = ret->length;
  }
  strncpy(infolog, ret->infolog, (size_t)bufsize);
}


GL_APICALL void GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar* name)
{
  gls_glBindAttribLocation_t *c = (gls_glBindAttribLocation_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glBindAttribLocation;
  c->program = program;
  c->index = index;
  c->name[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(c->name, name, GLS_STRING_SIZE);
  push_batch_command(sizeof(gls_glBindAttribLocation_t));
}


GL_APICALL void GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
  gls_cmd_flush();
  gls_glGetProgramInfoLog_t *c = (gls_glGetProgramInfoLog_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glGetProgramInfoLog;
  c->program = program;
  c->bufsize = bufsize;
  send_packet(sizeof(gls_glGetProgramInfoLog_t));

  wait_for_data("timeout:glGetProgramInfoLog");
  gls_ret_glGetProgramInfoLog_t *ret = (gls_ret_glGetProgramInfoLog_t *)glsc_global.tmp_buf.buf;
  if (length != NULL)
  {
    *length = ret->length;
  }
  if (ret->length == 0)
  {
    ret->infolog[0] = '\0';
  }
  strncpy(infolog, ret->infolog, (size_t)bufsize);
}


GL_APICALL int GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar* name)
{
  gls_cmd_flush();
  gls_glGetUniformLocation_t *c = (gls_glGetUniformLocation_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glGetUniformLocation;
  c->program = program;
  c->name[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(c->name, name, GLS_STRING_SIZE);
  send_packet(sizeof(gls_glGetUniformLocation_t));

  wait_for_data("timeout:glGetUniformLocation");
  gls_ret_glGetUniformLocation_t *ret = (gls_ret_glGetUniformLocation_t *)glsc_global.tmp_buf.buf;
  return ret->location;
}


GL_APICALL void GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat* v)
{
  if (count > 1)
  {
    gls_cmd_flush();
    gls_data_glUniform4fv_2_t *dat = (gls_data_glUniform4fv_2_t *)glsc_global.tmp_buf.buf;
    int i;
    for (i = 0; i < count * 4; i++)
    {
      dat->v[i] = v[i];
    }  
    uint32_t size = (uint32_t)((char *)&dat->v[i] - (char *)dat);
    gls_cmd_send_data(0, size, glsc_global.tmp_buf.buf);

    gls_glUniform4fv_2_t *c = (gls_glUniform4fv_2_t *)glsc_global.out_buf.buf;
    c->cmd = GLSC_glUniform4fv_2;
    c->location = location;
    c->count = count;
    send_packet(sizeof(gls_glUniform4fv_2_t));
  }
  else
  {
    gls_glUniform4fv_t *c = (gls_glUniform4fv_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
    c->cmd = GLSC_glUniform4fv;
    c->location = location;
    c->count = count;
    int i;
    for (i = 0; i < 4; i++)
    {
      c->v[i] = v[i];
    }  
    push_batch_command(sizeof(gls_glUniform4fv_t));
  }
}


GL_APICALL void GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  if (count > 1)
  {
    gls_cmd_flush();
    gls_data_glUniformMatrix4fv_2_t *dat = (gls_data_glUniformMatrix4fv_2_t *)glsc_global.tmp_buf.buf;
    int i;
    for (i = 0; i < count * 16; i++)
    {
      dat->value[i] = value[i];
    }  
    uint32_t size = (uint32_t)((char *)&dat->value[i] - (char *)dat);
    gls_cmd_send_data(0, size, glsc_global.tmp_buf.buf);

    gls_glUniformMatrix4fv_2_t *c = (gls_glUniformMatrix4fv_2_t *)glsc_global.out_buf.buf;
    c->cmd = GLSC_glUniformMatrix4fv_2;
    c->location = location;
    c->count = count;
    c->transpose = transpose;
    send_packet(sizeof(gls_glUniformMatrix4fv_2_t));
  }
  else
  {
    gls_glUniformMatrix4fv_t *c = (gls_glUniformMatrix4fv_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
    c->cmd = GLSC_glUniformMatrix4fv;
    c->location = location;
    c->count = count;
    c->transpose = transpose;
    int i;
    for (i = 0; i < 16; i++)
    {
      c->value[i] = value[i];
    }  
    push_batch_command(sizeof(gls_glUniformMatrix4fv_t));
  }
}


GL_APICALL void GL_APIENTRY glFinish (void)
{
  gls_cmd_flush();
  gls_command_t *c = (gls_command_t *)glsc_global.out_buf.buf;
  c->cmd = GLSC_glFinish;
  send_packet(sizeof(gls_command_t));
  wait_for_data("timeout:glFinish");
}


GL_APICALL void GL_APIENTRY glFlush (void)
{
  gls_command_t *c = (gls_command_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_glFlush;
  push_batch_command(sizeof(gls_command_t));
}



/*
{
  gls__t *c = (gls__t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
  c->cmd = GLSC_;
  c-> = ;
  push_batch_command(sizeof(gls__t));
}
 */
