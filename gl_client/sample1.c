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
#include <string.h>
#include <linux/joystick.h>
#include <fcntl.h>
#include <math.h>

#include "glclient.h"
#include "rpi/GLES2/gl2.h"
#include "glsutil.h"

#define g_vsize_pos 3
#define g_stride_pos (g_vsize_pos * sizeof(GLfloat))
#define g_vsize_nor 3
#define g_stride_nor (g_vsize_nor * sizeof(GLfloat))


typedef struct
{
  union
  {
    struct
    {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };
    uint32_t rgba;
  };
} color_t;

  
typedef struct
{
  float modelproj_mat[16];
  float nor_mat[16];
  uint32_t type;
  color_t color;
  float x;
  float y;
  float z;
  float dx;
  float dy;
  float dz;
  float rx;
  float ry;
  float rz;
  float drx;
  float dry;
  float drz;
} obj_3d_t;


static GLfloat light_pos[4] = {5.0, 5.0, 10.0, 1.0};
static obj_3d_t obj[1024];
static GLfloat proj_mat[16];
static float model_mat[16];
static float modelproj_mat[16];
static float nor_mat[16];
static float col[4];


static GLfloat vtx_cube[] =
{
  1.000000,1.000000,-1.000000,
  1.000000,-1.000000,-1.000000,
  -1.000000,-1.000000,-1.000000,
  1.000000,0.999999,1.000000,
  -1.000000,1.000000,1.000000,
  0.999999,-1.000001,1.000000,
  1.000000,1.000000,-1.000000,
  1.000000,0.999999,1.000000,
  1.000000,-1.000000,-1.000000,
  1.000000,-1.000000,-1.000000,
  0.999999,-1.000001,1.000000,
  -1.000000,-1.000000,-1.000000,
  -1.000000,-1.000000,-1.000000,
  -1.000000,-1.000000,1.000000,
  -1.000000,1.000000,1.000000,
  1.000000,0.999999,1.000000,
  1.000000,1.000000,-1.000000,
  -1.000000,1.000000,1.000000,
  -1.000000,1.000000,-1.000000,
  -1.000000,-1.000000,1.000000,
  1.000000,0.999999,1.000000,
  0.999999,-1.000001,1.000000,
  1.000000,-1.000000,-1.000000,
  -1.000000,-1.000000,1.000000,
  -1.000000,1.000000,-1.000000,
  -1.000000,1.000000,-1.000000,
};


static GLfloat nor_cube[] =
{
  0.000000,0.000000,-1.000000,
  0.000000,0.000000,-1.000000,
  0.000000,0.000000,-1.000000,
  -0.000000,-0.000000,1.000000,
  -0.000000,-0.000000,1.000000,
  -0.000000,-0.000000,1.000000,
  1.000000,0.000000,-0.000000,
  1.000000,0.000000,-0.000000,
  1.000000,0.000000,-0.000000,
  -0.000000,-1.000000,-0.000000,
  -0.000000,-1.000000,-0.000000,
  -0.000000,-1.000000,-0.000000,
  -1.000000,0.000000,-0.000000,
  -1.000000,0.000000,-0.000000,
  -1.000000,0.000000,-0.000000,
  0.000000,1.000000,0.000000,
  0.000000,1.000000,0.000000,
  0.000000,1.000000,0.000000,
  0.000000,0.000000,-1.000000,
  0.000000,-0.000000,1.000000,
  1.000000,-0.000001,0.000000,
  1.000000,-0.000001,0.000000,
  1.000000,-0.000001,0.000000,
  -0.000000,-1.000000,0.000000,
  -1.000000,0.000000,-0.000000,
  0.000000,1.000000,0.000000,
};


static GLushort ind_cube[] =
{
  0,1,2,
  3,4,5,
  6,7,8,
  9,10,11,
  12,13,14,
  15,16,17,
  18,0,2,
  4,19,5,
  20,21,22,
  10,23,11,
  24,12,14,
  16,25,17,
};


static const GLchar *VShader1 = 
  "attribute vec3 pos;\n"
  "attribute vec3 nor;\n"
  "uniform mat4 model_mat;\n"
  "uniform mat4 nor_mat;\n"
  "uniform vec4 light_pos;\n"
  "uniform vec4 col;\n"
  "varying vec4 fcol;\n"
  "void main(void)\n"
  "{\n"
  " vec3 eyenor = normalize(vec3(nor_mat * vec4(nor, 1.0)));\n"
  " vec3 lnor = normalize(light_pos.xyz);\n"
  " float diffuse = max(dot(eyenor, lnor), 0.0);\n"
  " fcol = vec4(vec3(diffuse * col), 1.0) ;\n"
  " gl_Position = model_mat * vec4(pos, 1.0);\n"
  "}\n";


static const GLchar *FShader1 = 
  "precision mediump float;\n"
  "varying vec4 fcol;\n"
  "void main(void)\n"
  "{\n"
  " gl_FragColor = fcol;\n"
  "}\n";


typedef struct
{
  uint32_t screen_width;
  uint32_t screen_height;
  GLuint vshader;
  GLuint fshader;
  GLuint program;
  GLuint vbo_pos;
  GLuint vbo_nor;
  GLuint vbo_ind;
  GLint vloc_pos;
  GLint vloc_nor;
  GLuint uloc_model;
  GLuint uloc_nor;
  GLuint uloc_light;
  GLuint uloc_col;
  GLfloat* vtx_pos;
  GLfloat* vtx_nor;
} graphics_context_t;


typedef struct
{
  char joy_dev[GLS_STRING_SIZE_PLUS];
} glclient_context_t;


static inline float randf(void)
{
  return (float)rand() / (float)RAND_MAX;
}


static inline float get_diff_time(struct timeval start, struct timeval end)
{
  float dt = (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec) * 0.000001f;
  return dt;
}


GLuint create_vbo(GLenum target, void *vtx, size_t size)
{
  static GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(target, vbo);
  glBufferData(target, size, vtx, GL_STATIC_DRAW);
  glBindBuffer(target, 0);
  return vbo;
}


void release_vbo(GLenum target, GLuint vbo)
{
  glBindBuffer(target, 0);
  glDeleteBuffers(1, &vbo);
}


void init_shader(graphics_context_t *gc, const GLchar *vs, const GLchar *fs)
{
  gc->vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(gc->vshader, 1, &vs, 0);
  glCompileShader(gc->vshader);
  gc->fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(gc->fshader, 1, &fs, 0);
  glCompileShader(gc->fshader);

  gc->program = glCreateProgram();
  glAttachShader(gc->program, gc->vshader);
  glAttachShader(gc->program, gc->fshader);
  glLinkProgram(gc->program);
}


void release_shader(graphics_context_t *gc)
{
  glDeleteProgram(gc->program);
  glDeleteShader(gc->vshader);
  glDeleteShader(gc->fshader);
}


void init_gl(graphics_context_t *gc)
{
  init_shader(gc, VShader1, FShader1);
  gc->vbo_pos = create_vbo(GL_ARRAY_BUFFER, vtx_cube, sizeof(vtx_cube));
  gc->vbo_nor = create_vbo(GL_ARRAY_BUFFER, nor_cube, sizeof(nor_cube));
  gc->vbo_ind = create_vbo(GL_ELEMENT_ARRAY_BUFFER, ind_cube, sizeof(ind_cube));
  gc->vloc_pos = glGetAttribLocation(gc->program, "pos");
  gc->vloc_nor = glGetAttribLocation(gc->program, "nor");
  gc->uloc_model = glGetUniformLocation(gc->program, "model_mat");
  gc->uloc_nor = glGetUniformLocation(gc->program, "nor_mat");
  gc->uloc_light = glGetUniformLocation(gc->program, "light_pos");
  gc->uloc_col = glGetUniformLocation(gc->program, "col");

  glBindBuffer(GL_ARRAY_BUFFER, gc->vbo_pos);
  glVertexAttribPointer(gc->vloc_pos, g_vsize_pos, GL_FLOAT, GL_FALSE, g_stride_pos, (GLfloat *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, gc->vbo_nor);
  glVertexAttribPointer(gc->vloc_nor, g_vsize_nor, GL_FLOAT, GL_FALSE, g_stride_nor, (GLfloat *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindFramebuffer(GL_FRAMEBUFFER,0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, gc->screen_width, gc->screen_height);
  glUseProgram(gc->program);

  glDisable(GL_BLEND);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
}


void release_gl(graphics_context_t *gc)
{
  release_shader(gc);
  release_vbo(GL_ARRAY_BUFFER, gc->vbo_pos);
  release_vbo(GL_ARRAY_BUFFER, gc->vbo_nor);
  release_vbo(GL_ELEMENT_ARRAY_BUFFER, gc->vbo_ind);
}


void * glclient_thread(void * arg)
{
  server_thread_args_t * a = (server_thread_args_t *)arg;
  static graphics_context_t gc;

  static struct js_event joy;
  int joy_fd;
  static char button[32];

  glclient_context_t *glcc = a->user_context_ptr;

  joy_fd = open(glcc->joy_dev, O_RDONLY);
  if (joy_fd == -1)
  {
    printf("Error: Joystick device open\n");
  }
  if (joy_fd != -1)
  {
    fcntl(joy_fd, F_SETFL, O_NONBLOCK);
  }

  gls_init(a);

  gls_cmd_get_context();
  gc.screen_width = glsc_global.screen_width;
  gc.screen_height = glsc_global.screen_height;
  printf("width:%d height:%d\n",glsc_global.screen_width,glsc_global.screen_height);
  init_gl(&gc);

  float aspect = (float)gc.screen_width / (float)gc.screen_height;

  mat_perspective(proj_mat, aspect, 1.0f, 1024.0f, 60.0f);
  glUniform4fv(gc.uloc_light, 1, light_pos);

  int j;
  for (j = 0; j < 1024; j++)
  {
    obj[j].x = randf() * 60.0f - 30.0f;
    obj[j].y = randf() * 60.0f - 30.0f;
    obj[j].z = randf() * 300.0f - 300.0f;
    obj[j].dx = randf() * 0.0f - 0.00f;
    obj[j].dy = randf() * 0.0f - 0.00f;
    obj[j].dz = randf() * 1.3f - 0.3f;
    if (fabs(obj[j].dz) < 0.01f)
    {
      obj[j].dz = 0.01f;
    }
    obj[j].rx = randf() * 6.28;
    obj[j].ry = randf() * 6.28;
    obj[j].rz = randf() * 6.28;
    obj[j].drx = randf() * 0.1f - 0.05f;
    obj[j].dry = randf() * 0.1f - 0.05f;
    obj[j].drz = randf() * 0.1f - 0.05f;
    obj[j].color.r = (uint8_t)(randf() * 255.5f);
    obj[j].color.g = (uint8_t)(randf() * 255.5f);
    obj[j].color.b = (uint8_t)(randf() * 255.5f);
    obj[j].color.a = (uint8_t)255;
  }

  float x = 0.0f;
  float y = 0.0f;
  float rx = 0.0f;
  float ry = 0.0f;

  int i;
  for (i = 0; i < 432000; i++)
  {
    struct timeval times, timee;
    gettimeofday(&times, NULL);

    if (joy_fd != -1)
    {
      while (read(joy_fd, &joy, sizeof(struct js_event)) == sizeof(struct js_event))
      {
        if ((joy.type & JS_EVENT_BUTTON) == JS_EVENT_BUTTON)
        {
          button[joy.number] = joy.value;
        }
      }

      if (button[4] > 0)
      {
        y += 0.01f;
      }
      if (button[6] > 0)
      {
        y += -0.01f;
      }
      if (button[5] > 0)
      {
        x += 0.01f * aspect;
      }
      if (button[7] > 0)
      {
        x += -0.01f * aspect;
      }
      if (button[12] > 0)
      {
        rx += -0.01f;
      }
      if (button[13] > 0)
      {
        ry += 0.01f;
      }
      if (button[14] > 0)
      {
        rx += 0.01f;
      }
      if (button[15] > 0)
      {
        ry += -0.01f;
      }
    }

    glUseProgram(gc.program);
    glBindBuffer(GL_ARRAY_BUFFER, gc.vbo_pos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gc.vbo_ind);
    glEnableVertexAttribArray(gc.vloc_pos);
    glEnableVertexAttribArray(gc.vloc_nor);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (j = 0; j < 240; j++)
    {
      obj[j].x += obj[j].dx;
      obj[j].y += obj[j].dy;
      obj[j].z += obj[j].dz + y;
      if (obj[j].z > 1.0f)
      {
        obj[j].x = randf() * 60.0f - 30.0f;
        obj[j].y = randf() * 60.0f - 30.0f;
        obj[j].z = -300.0f;
      }
      if (obj[j].z < -400.0f)
      {
        obj[j].x = randf() * 60.0f - 30.0f;
        obj[j].y = randf() * 60.0f - 30.0f;
        obj[j].z = 1.0f;
      }
      obj[j].rx += obj[j].drx;
      obj[j].ry += obj[j].dry;
      obj[j].rz += obj[j].drz;

      mat_identity(model_mat);
      mat_translate(model_mat, obj[j].x, obj[j].y, obj[j].z);
      mat_rotate_x(model_mat, obj[j].rx);
      mat_rotate_y(model_mat, obj[j].ry);
      mat_rotate_z(model_mat, obj[j].rz);

      mat_copy(nor_mat, model_mat);
      mat_invert(nor_mat);
      mat_transpose(nor_mat);
      glUniformMatrix4fv(gc.uloc_nor, 1, GL_FALSE, nor_mat);
      mat_copy(obj[j].nor_mat, nor_mat);

      mat_copy(modelproj_mat, proj_mat);
      mat_mul(modelproj_mat, model_mat);
      glUniformMatrix4fv(gc.uloc_model, 1, GL_FALSE, modelproj_mat);
      mat_copy(obj[j].modelproj_mat, modelproj_mat);

      col[0] = (float)obj[j].color.r * 0.00392156862745f;
      col[1] = (float)obj[j].color.g * 0.00392156862745f;
      col[2] = (float)obj[j].color.b * 0.00392156862745f;
      col[3] = (float)obj[j].color.a * 0.00392156862745f;
      glUniform4fv(gc.uloc_col, 1, col);

      glDrawElements(GL_TRIANGLES, sizeof(ind_cube) / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    }
    glDisableVertexAttribArray(gc.vloc_nor);
    glDisableVertexAttribArray(gc.vloc_pos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    gls_cmd_flip(i);
    gettimeofday(&timee, NULL);
    //printf("%d:%f ms ", i, get_diff_time(times, timee) * 1000.0f);
  }
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gls_cmd_flip(i);
  release_gl(&gc);
  gls_free();
  if (joy_fd != -1)
  {
    close(joy_fd);
  }
  pthread_exit(NULL);
}


int main(int argc, char * argv[])
{
  static server_context_t sc;
  static glclient_context_t glcc;
  int opt;
  char my_ip[GLS_STRING_SIZE_PLUS];
  char his_ip[GLS_STRING_SIZE_PLUS];
  uint16_t my_port = 12346;
  uint16_t his_port = 12345;
  strncpy(my_ip, "127.0.0.1", GLS_STRING_SIZE);
  strncpy(his_ip, "127.0.0.1", GLS_STRING_SIZE);
  strncpy(glcc.joy_dev, "/dev/input/js0", GLS_STRING_SIZE);
  while ((opt = getopt(argc, argv, "s:c:j:h")) != -1)
  {
    switch (opt)
    {
      case 's':
        strncpy(his_ip, strtok(optarg, ":"), GLS_STRING_SIZE);
        his_port = atoi(strtok(NULL, ":"));
        break;
      case 'c':
        strncpy(my_ip, strtok(optarg, ":"), GLS_STRING_SIZE);
        my_port = atoi(strtok(NULL, ":"));
        break;
      case 'j':
        strncpy(glcc.joy_dev, optarg, GLS_STRING_SIZE);
        break;
      case 'h':
      default:
        printf("Usage: %s [-c my_ip_address:port] [-s server_ip_address:port] [-j joystick_device]\n", argv[0]);
        return 0;
    }
  }
  server_init(&sc);
  set_server_address_port(&sc, my_ip, my_port);
  set_client_address_port(&sc, his_ip, his_port);
  set_client_user_context(&sc, &glcc);

  server_run(&sc, glclient_thread);

  return 0;
}
