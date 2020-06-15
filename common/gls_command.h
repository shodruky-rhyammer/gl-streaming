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


#include <unistd.h>
#include <stdint.h>


#define GLS_TMP_BUFFER_SIZE 2097152
#define GLS_DATA_SIZE 356
#define GLS_STRING_SIZE_PLUS 10240 // 256
#define GLS_STRING_SIZE 10160 // 254
#define GLS_ALIGNMENT_BITS 3


// To prevent incompatible version, change every
#define GLS_VERSION 8
// #define GL_MAJOR_VERSION 1
// #define GL_MINOR_VERSION 2


enum GL_Server_Command
{
  GLSC_BREAK,
  GLSC_FLIP,
  GLSC_SEND_DATA,
  GLSC_FLUSH,
  GLSC_get_context,
  
  // EGL commands
  GLSC_eglChooseConfig,
  GLSC_eglCopyBuffers,
  GLSC_eglCreateContext,
  GLSC_eglCreatePbufferSurface,
  GLSC_eglCreatePixmapSurface,
  GLSC_eglCreateWindowSurface,
  GLSC_eglDestroyContext,
  GLSC_eglDestroySurface,
  GLSC_eglGetConfigAttrib,
  GLSC_eglGetConfigs,
  GLSC_eglGetCurrentDisplay,
  GLSC_eglGetCurrentSurface,
  GLSC_eglGetDisplay,
  GLSC_eglGetError,
// This will never get streamed. Proc address is different.
  // GLSC_eglGetProcAddress,
  GLSC_eglInitialize,
  GLSC_eglMakeCurrent,
  GLSC_eglQueryContext,
  GLSC_eglQueryString,
  GLSC_eglQuerySurface,
  GLSC_eglSwapBuffers,
  GLSC_eglTerminate,
  GLSC_eglWaitGL,
  GLSC_eglWaitNative,
  
  // GLES 2 commands
  GLSC_glActiveTexture,
  GLSC_glAttachShader,
  GLSC_glBindAttribLocation,
  GLSC_glBindBuffer,
  GLSC_glBindFramebuffer,
  GLSC_glBindTexture,
  GLSC_glBlendEquationSeparate,
  GLSC_glBlendFuncSeparate,
  GLSC_glBlendFunc,
  GLSC_glBufferData,
  GLSC_glBufferSubData,
  GLSC_glClear,
  GLSC_glClearColor,
  GLSC_glClearDepthf,
  GLSC_glClearStencil,
  GLSC_glCompileShader,
  GLSC_glCreateProgram,
  GLSC_glCreateShader,
  GLSC_glCullFace,
  GLSC_glDeleteBuffers,
  GLSC_glDeleteProgram,
  GLSC_glDeleteShader,
  GLSC_glDeleteTextures,
  GLSC_glDepthFunc,
  GLSC_glDepthMask,
  GLSC_glDepthRangef,
  GLSC_glDisable,
  GLSC_glDisableVertexAttribArray,
  GLSC_glDrawArrays,
  GLSC_glDrawElements,
  GLSC_glEnable,
  GLSC_glEnableVertexAttribArray,
  GLSC_glFinish,
  GLSC_glFlush,
  GLSC_glGenBuffers,
  GLSC_glGenTextures,
  GLSC_glGetActiveUniform,
  GLSC_glGetAttribLocation,
  GLSC_glGetError,
  GLSC_glGetFloatv,
  GLSC_glGetProgramiv,
  GLSC_glGetIntegerv,
  GLSC_glGetProgramInfoLog,
  GLSC_glGetShaderInfoLog,
  GLSC_glGetShaderiv,
  GLSC_glGetString,
  GLSC_glGetUniformLocation,
  GLSC_glHint,
  GLSC_glLineWidth,
  GLSC_glLinkProgram,
  GLSC_glPixelStorei,
  GLSC_glPolygonOffset,
  GLSC_glReadPixels,
  GLSC_glShaderSource,
  GLSC_glStencilFunc,
  GLSC_glStencilMask,
  GLSC_glStencilOp,
  GLSC_glTexImage2D,
  GLSC_glTexParameteri,
  GLSC_glTexSubImage2D,
  GLSC_glUniform1f,
  GLSC_glUniform4fv,
  GLSC_glUniformMatrix4fv,
  GLSC_glUseProgram,
  GLSC_glVertexAttribPointer,
  GLSC_glViewport
};


typedef struct
{
  char *buf;
  size_t size;
  uint32_t ptr;
} gls_buffer_t;


typedef struct
{
  uint32_t cmd;
} gls_command_t;


typedef struct
{
  uint32_t cmd;
  uint32_t frame;
} gls_cmd_flip_t;


typedef struct
{
  uint32_t cmd;
  uint32_t frame;
} gls_ret_flip_t;


typedef struct
{
  uint32_t cmd;
} gls_cmd_get_context_t;


typedef struct
{
  uint32_t cmd;
  uint32_t server_version;
  uint32_t screen_width;
  uint32_t screen_height;
} gls_ret_get_context_t;


typedef union
{
  float data_float[GLS_DATA_SIZE];
  uint32_t data_uint[GLS_DATA_SIZE];
  int32_t data_int[GLS_DATA_SIZE];
  char data_char[GLS_DATA_SIZE * 36]; // * 4
} gls_data_t;


typedef struct
{
  uint32_t cmd;
  uint32_t offset;
  uint32_t size;
  int32_t isLast;
  gls_data_t data;
} gls_cmd_send_data_t;

/* Conversation
 *
 * - boolean, enum, unsigned int
 * '-> uint32_t
 */

// EGL commands
typedef struct
{
  uint32_t cmd;
  uint32_t api;
} gls_eglBindAPI_t;


typedef struct
{
  uint32_t cmd;
  uint32_t success;
} gls_ret_eglBindAPI_t;


typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
  uint32_t config;
  uint32_t attribute;
} gls_eglGetConfigAttrib_t;


typedef struct
{
  uint32_t cmd;
  uint32_t value;
  uint32_t success;
} gls_ret_eglGetConfigAttrib_t;


/*
typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
  uint32_t config_size;
} gls_eglGetConfigs_t;


typedef struct
{
  uint32_t cmd;
// FIXME sending return data???
  uint32_t[GLS_STRING_SIZE_PLUS] configs;
  uint32_t num_config;
} gls_ret_eglGetConfigs_t;
*/


typedef struct
{
  uint32_t cmd;
  uint32_t display;
} gls_eglGetDisplay_t;


typedef struct
{
  uint32_t cmd;
  uint32_t display;
} gls_ret_eglGetDisplay_t;


typedef struct
{
  uint32_t cmd;
} gls_eglGetError_t;


typedef struct
{
  uint32_t cmd;
  uint32_t error;
} gls_ret_eglGetError_t;


typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
  uint32_t major;
  uint32_t minor;
} gls_eglInitialize_t;


typedef struct
{
  uint32_t cmd;
  uint32_t success;
} gls_ret_eglInitialize_t;


typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
  uint32_t name;
} gls_eglQueryString_t;


typedef struct
{
  uint32_t cmd;
  char params[GLS_STRING_SIZE_PLUS];
} gls_ret_eglQueryString_t;

typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
  uint32_t surface;
  uint32_t attribute;
} gls_eglQuerySurface_t;


typedef struct
{
  uint32_t cmd;
  uint32_t value;
  uint32_t success;
} gls_ret_eglQuerySurface_t;


typedef struct
{
  uint32_t cmd;
  uint32_t dpy;
} gls_eglTerminate_t;


typedef struct
{
  uint32_t cmd;
  uint32_t success;
} gls_ret_eglTerminate_t;

// OpenGL ES commands
typedef struct
{
  uint32_t cmd;
  uint32_t texture;
} gls_glActiveTexture_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  uint32_t shader;
} gls_glAttachShader_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  uint32_t index;
  char name[GLS_STRING_SIZE_PLUS];
} gls_glBindAttribLocation_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  uint32_t buffer;
} gls_glBindBuffer_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  uint32_t texture;
} gls_glBindTexture_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  uint32_t framebuffer;
} gls_glBindFramebuffer_t;


typedef struct
{
  uint32_t cmd;
  uint32_t srcRGB;
  uint32_t dstRGB;
  uint32_t srcAlpha;
  uint32_t dstAlpha;
} gls_glBlendFuncSeparate_t;


typedef struct
{
  uint32_t cmd;
  uint32_t modeRGB;
  uint32_t modeAlpha;
} gls_glBlendEquationSeparate_t;


typedef struct
{
  uint32_t cmd;
  uint32_t sfactor;
  uint32_t dfactor;
} gls_glBlendFunc_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  int32_t size;
  uint32_t usage;
} gls_glBufferData_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  int32_t offset;
  int32_t size;
} gls_glBufferSubData_t;


typedef struct
{
  uint32_t cmd;
  uint32_t mask;
} gls_glClear_t;


typedef struct
{
  uint32_t cmd;
  float red;
  float green;
  float  blue;
  float alpha;
} gls_glClearColor_t;


typedef struct
{
  uint32_t cmd;
  float depth;
} gls_glClearDepthf_t;


typedef struct
{
  uint32_t cmd;
  uint32_t s;
} gls_glClearStencil_t;


typedef struct
{
  uint32_t cmd;
  uint32_t shader;
} gls_glCompileShader_t;


typedef struct
{
  uint32_t cmd;
} gls_glCreateProgram_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
} gls_ret_glCreateProgram_t;


typedef struct
{
  uint32_t cmd;
  uint32_t type;
} gls_glCreateShader_t;


typedef struct
{
  uint32_t cmd;
  uint32_t obj;
} gls_ret_glCreateShader_t;


typedef struct
{
  uint32_t cmd;
  uint32_t mode;
} gls_glCullFace_t;


typedef struct
{
  uint32_t cmd;
  int32_t n;
} gls_glDeleteBuffers_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
} gls_glDeleteProgram_t;


typedef struct
{
  uint32_t cmd;
  uint32_t shader;
} gls_glDeleteShader_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cmd_size;
  int32_t n;
  uint32_t textures[1];
} gls_glDeleteTextures_t;


typedef struct
{
  uint32_t cmd;
  uint32_t func;
} gls_glDepthFunc_t;


typedef struct
{
  uint32_t cmd;
  uint32_t flag;
} gls_glDepthMask_t;


typedef struct
{
  uint32_t cmd;
  uint32_t zNear;
  uint32_t zFar;
} gls_glDepthRangef_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cap;
} gls_glDisable_t;


typedef struct
{
  uint32_t cmd;
  uint32_t index;
} gls_glDisableVertexAttribArray_t;


typedef struct
{
  uint32_t cmd;
  uint32_t mode;
  int32_t first;
  int32_t count;
} gls_glDrawArrays_t;


typedef struct
{
  uint32_t cmd;
  uint32_t mode;
  int32_t count;
  uint32_t type;
  uint32_t indices;
} gls_glDrawElements_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cap;
} gls_glEnable_t;


typedef struct
{
  uint32_t cmd;
  uint32_t index;
} gls_glEnableVertexAttribArray_t;


typedef struct
{
  uint32_t cmd;
} gls_glFinish_t;


typedef struct
{
  uint32_t cmd;
} gls_glFlush_t;


typedef struct
{
  uint32_t cmd;
  int32_t n;
  uint32_t buffers;
} gls_glGenBuffers_t;


typedef struct
{
  uint32_t cmd;
  int32_t n;
} gls_glGenTextures_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  char name[GLS_STRING_SIZE_PLUS];
} gls_glGetAttribLocation_t;


typedef struct
{
  uint32_t cmd;
  int32_t index;
} gls_ret_glGetAttribLocation_t;


typedef struct
{
  uint32_t cmd;
} gls_glGetError_t;


typedef struct
{
  uint32_t cmd;
  uint32_t error;
} gls_ret_glGetError_t;


typedef struct
{
  uint32_t cmd;
  uint32_t name;
  int32_t params;
} gls_glGetIntegerv_t;


typedef struct
{
  uint32_t cmd;
  int32_t params;
} gls_ret_glGetIntegerv_t;


typedef struct
{
  uint32_t cmd;
  uint32_t name;
  float params;
} gls_glGetFloatv_t;


typedef struct
{
  uint32_t cmd;
  float params;
} gls_ret_glGetFloatv_t;


typedef struct
{
  uint32_t cmd;
  uint32_t name;
} gls_glGetString_t;


typedef struct
{
  uint32_t cmd;
  char params[GLS_STRING_SIZE_PLUS];
} gls_ret_glGetString_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  int32_t bufsize;
} gls_glGetProgramInfoLog_t;


typedef struct
{
  uint32_t cmd;
  int32_t length;
  char infolog[GLS_STRING_SIZE_PLUS];
} gls_ret_glGetProgramInfoLog_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  uint32_t pname;
} gls_glGetProgramiv_t;


typedef struct
{
  uint32_t cmd;
  int32_t params;
} gls_ret_glGetProgramiv_t;


typedef struct
{
  uint32_t cmd;
  uint32_t shader;
  uint32_t pname;
} gls_glGetShaderiv_t;


typedef struct
{
  uint32_t cmd;
  int32_t params;
} gls_ret_glGetShaderiv_t;

typedef struct
{
  uint32_t cmd;
  uint32_t shader;
  int32_t bufsize;
} gls_glGetShaderInfoLog_t;


typedef struct
{
  uint32_t cmd;
  int32_t length;
  char infolog[GLS_STRING_SIZE_PLUS];
} gls_ret_glGetShaderInfoLog_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
  char name[GLS_STRING_SIZE_PLUS];
} gls_glGetUniformLocation_t;


typedef struct
{
  uint32_t cmd;
  int32_t location;
} gls_ret_glGetUniformLocation_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  uint32_t mode;
} gls_glHint_t;


typedef struct
{
  uint32_t cmd;
  float width;
} gls_glLineWidth_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
} gls_glLinkProgram_t;


typedef struct
{
  uint32_t cmd;
  uint32_t pname;
  int32_t param;
} gls_glPixelStorei_t;


typedef struct
{
  uint32_t cmd;
  float factor;
  float units;
} gls_glPolygonOffset_t;


typedef struct
{
  uint32_t cmd;
  int32_t x;
  int32_t y;
  uint32_t width;
  uint32_t height;
  uint32_t format;
  uint32_t type;
} gls_glReadPixels_t;


typedef struct
{
  uint32_t cmd;
  char pixels[4];
} gls_ret_glReadPixels_t;


typedef struct
{
  uint32_t cmd;
  uint32_t shader;
  int32_t count;
} gls_glShaderSource_t;


typedef struct
{
  uint32_t string[GLS_STRING_SIZE_PLUS];
  int32_t length[GLS_STRING_SIZE_PLUS];
  char data[4];
} gls_data_glShaderSource_t;


typedef struct
{
  uint32_t cmd;
  uint32_t func;
  int32_t r;
  uint32_t m;
} gls_glStencilFunc_t;


typedef struct
{
  uint32_t cmd;
  uint32_t fail;
  uint32_t zfail;
  uint32_t zpass;
} gls_glStencilOp_t;


typedef struct
{
  uint32_t cmd;
  uint32_t mask;
} gls_glStencilMask_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cmd_size;
  uint32_t target;
  int32_t level;
  int32_t internalformat;
  int32_t width;
  int32_t height;
  int32_t border;
  uint32_t format;
  uint32_t type;
  char pixels[4];
} gls_glTexImage2D_t;


typedef struct
{
  uint32_t cmd;
  uint32_t target;
  uint32_t pname;
  int32_t param;
} gls_glTexParameteri_t;


// Based from gls_glTexImage2D_t code
typedef struct
{
  uint32_t cmd;
  uint32_t cmd_size;
  uint32_t target;
  int32_t level;
  int32_t xoffset;
  int32_t yoffset;
  int32_t width;
  int32_t height;
  uint32_t format;
  uint32_t type;
  char pixels[4];
} gls_glTexSubImage2D_t;


typedef struct
{
  uint32_t cmd;
  int32_t location;
  float x;
} gls_glUniform1f_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cmd_size;
  int32_t location;
  int32_t count;
  float v[1];
} gls_glUniform4fv_t;


typedef struct
{
  uint32_t cmd;
  uint32_t cmd_size;
  int32_t location;
  int32_t count;
  uint32_t transpose;
  float value[1];
} gls_glUniformMatrix4fv_t;


typedef struct
{
  uint32_t cmd;
  uint32_t program;
} gls_glUseProgram_t;


typedef struct
{
  uint32_t cmd;
  uint32_t indx;
  int32_t size;
  uint32_t type;
  int32_t stride;
  uint32_t ptr;
  uint32_t normalized;
} gls_glVertexAttribPointer_t;


typedef struct
{
  uint32_t cmd;
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} gls_glViewport_t;





/*
typedef struct
{
  uint32_t cmd;
  uint32_t ;
} gls__t;

typedef void             GLvoid;
typedef char             GLchar;
typedef unsigned int     GLenum;
typedef unsigned char    GLboolean;
typedef unsigned int     GLbitfield;
typedef signed   char    GLbyte;
typedef short            GLshort;
typedef int              GLint;
typedef int              GLsizei;
typedef unsigned char    GLubyte;
typedef unsigned short   GLushort;
typedef unsigned int     GLuint;
typedef float            GLfloat;
typedef float            GLclampf;
typedef int32_t          GLfixed;
typedef signed long int  GLintptr;
typedef signed long int  GLsizeiptr;
 */


static inline uint32_t next_ptr(uint32_t ptr, uint32_t size, uint32_t alignment_bits)
{
  uint32_t a = (1 << alignment_bits) - 1;
  return (ptr + size + a) & ~a;
}


static inline void gls_sleep(unsigned int max_mbps, unsigned int size)
{
  //unsigned int sleeptime = (1.0f / (a->max_mbps * 1024.0f * 1024.0f / 8.0f / (float)(size)) * 1000000.0f) + 1;
  unsigned int sleeptime = (float)1500.0f * 7.62939453125f / max_mbps + 1.0f;
  usleep((useconds_t)sleeptime);
}


