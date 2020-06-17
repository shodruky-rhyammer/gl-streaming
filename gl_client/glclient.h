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

#include <X11/X.h>
#include <X11/Xlib.h>

#include "GLES2/gl2.h"
#include "gls_command.h"
#include "server.h"

typedef struct
{
  gls_buffer_t tmp_buf;
  gls_buffer_t out_buf;
  server_context_t *sta;
  void *cmd_data;
  uint32_t screen_width;
  uint32_t screen_height;
  int32_t pack_alignment;
  int32_t unpack_alignment;
} gls_context_t;


#ifdef __cplusplus
extern "C" {
#endif

#define GLS_OUT_BUFFER_SIZE 2048
#define BATCH_AUTO_FLUSH_SIZE 8128
#define GLS_TIMEOUT_SEC 3.0f

// gls_glFunctionName_t *c = (gls_glFunctionName_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr);
// c->cmd = GLSC_glFunctionName;
#define GLS_SET_COMMAND_PTR_BATCH(PTR, FUNCNAME) gls_##FUNCNAME##_t *PTR = (gls_##FUNCNAME##_t *)(glsc_global.tmp_buf.buf + glsc_global.tmp_buf.ptr); PTR->cmd = GLSC_##FUNCNAME

// push_batch_command(sizeof(gls_glFunctionName_t));
#define GLS_PUSH_BATCH(FUNCNAME) push_batch_command(sizeof(gls_##FUNCNAME##_t))

// gls_glFunctionName_t *c = (gls_glFunctionName_t *)glsc_global.out_buf.buf;
// c->cmd = GLSC_glFunctionName;
#define GLS_SET_COMMAND_PTR(PTR, FUNCNAME) gls_##FUNCNAME##_t *PTR = (gls_##FUNCNAME##_t *)glsc_global.out_buf.buf; PTR->cmd = GLSC_##FUNCNAME

// send_packet(sizeof(gls_glFunctionName_t));
#define GLS_SEND_PACKET(FUNCNAME) send_packet(sizeof(gls_##FUNCNAME##_t))

#define TRUE 1
#define FALSE 0

Display *xDisplay;
int xScreenId;

gls_context_t glsc_global;
static struct vbo_state
{
    GLuint vbo, ibo, ibo_emu;
} vbo;

struct attrib_ptr_s {
    GLboolean   isenabled;
    GLint       size;
    GLenum      type;
    GLsizei     stride;
    GLboolean   normalized;
    const GLvoid *ptr;
    GLuint vbo_id;
    GLuint webgl_vbo_id;
} vt_attrib_pointer[16];

float get_diff_time(struct timeval start, struct timeval end);
int check_batch_overflow(size_t size, const char *msg);
void push_batch_command(size_t size);
int gls_cmd_flush();

void gls_init_library();

extern gls_context_t glsc_global;
int gls_init(server_context_t *arg);
int gls_free();
int send_packet(size_t size);
int gls_cmd_flip(unsigned int frame);
int gls_cmd_send_data(uint32_t offset, uint32_t size, void *data);
int gls_cmd_get_context();
int gls_cmd_flush();

#ifdef __cplusplus
}
#endif
