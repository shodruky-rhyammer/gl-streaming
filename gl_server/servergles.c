// This file declare OpenGL ES methods on server side

#include "glserver.h"

int gles_flushCommand(gls_command_t *c) {
	switch (c->cmd) {
		
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
      case GLSC_glDepthFunc:
        glse_glDepthFunc();
        pop_batch_command(sizeof(gls_glDepthFunc_t));
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
		
      case GLSC_glBlendFunc:
        glse_glBlendFunc();
        pop_batch_command(sizeof(gls_glBlendFunc_t));
        break;
      case GLSC_glCullFace:
        glse_glCullFace();
        pop_batch_command(sizeof(gls_glCullFace_t));
        break;
      case GLSC_glDepthMask:
        glse_glDepthMask();
        pop_batch_command(sizeof(gls_glDepthMask_t));
        break;
      case GLSC_glDepthRangef:
        glse_glDepthRangef();
        pop_batch_command(sizeof(gls_glDepthRangef_t));
        break;
      case GLSC_glHint:
        glse_glHint();
        pop_batch_command(sizeof(gls_glHint_t));
        break;
      case GLSC_glLineWidth:
        glse_glLineWidth();
        pop_batch_command(sizeof(gls_glLineWidth_t));
        break;
      case GLSC_glPolygonOffset:
        glse_glPolygonOffset();
        pop_batch_command(sizeof(gls_glPolygonOffset_t));
        break;
      case GLSC_glStencilFunc:
        glse_glStencilFunc();
        pop_batch_command(sizeof(gls_glStencilFunc_t));
        break;
      case GLSC_glStencilMask:
        glse_glStencilMask();
        pop_batch_command(sizeof(gls_glStencilMask_t));
        break;
      case GLSC_glStencilOp:
        glse_glStencilOp();
        pop_batch_command(sizeof(gls_glStencilOp_t));
        break;
      case GLSC_glClearDepthf:
        glse_glClearDepthf();
        pop_batch_command(sizeof(gls_glClearDepthf_t));
        break;
		
/*
      case GLSC_glXXX:
        glse_glXXX();
        pop_batch_command(sizeof(gls_glXXX_t));
        break;
*/
	
	  default:
	  	return FALSE;
	}
	return TRUE;
}

int gles_executeCommand(gls_command_t *c) {
	switch (c->cmd) {
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
/*
        case GLSC_glGetActiveUniform:
          glse_glGetActiveUniform();
          break;
*/
        case GLSC_glGetAttribLocation:
          glse_glGetAttribLocation();
          break;
		case GLSC_glGetError:
		  glse_glGetError();
		  break;
        case GLSC_glGetFloatv:
          glse_glGetFloatv();
          break;
        case GLSC_glGetIntegerv:
          glse_glGetIntegerv();
          break;
        case GLSC_glGetProgramInfoLog:
          glse_glGetProgramInfoLog();
          break;
        case GLSC_glGetProgramiv:
          glse_glGetProgramiv();
          break;
        case GLSC_glGetShaderInfoLog:
          glse_glGetShaderInfoLog();
          break;
        case GLSC_glGetShaderiv:
          glse_glGetShaderiv();
          break;
        case GLSC_glGetString:
          glse_glGetString();
          break;
        case GLSC_glGetUniformLocation:
          glse_glGetUniformLocation();
          break;
        case GLSC_glReadPixels:
          glse_glReadPixels();
          break;
        case GLSC_glShaderSource:
          glse_glShaderSource();
          break;
		default:
		  return FALSE;
	}
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


void glse_glDepthFunc()
{
  GLSE_SET_COMMAND_PTR(c, glDepthFunc);
  glDepthFunc(c->func);
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


void glse_glGetError()
{
  GLuint error = glGetError();
  // Should check gl error inside glGetError() ???
  check_gl_err();
  gls_ret_glGetError_t *ret = (gls_ret_glGetError_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_glGetError;
  ret->error = error;
  glse_cmd_send_data(0, sizeof(gls_ret_glGetError_t), (char *)glsec_global.tmp_buf.buf);
}


void glse_glGetFloatv()
{
  GLSE_SET_COMMAND_PTR(c, glGetFloatv);
  gls_ret_glGetFloatv_t *ret = (gls_ret_glGetFloatv_t *)glsec_global.tmp_buf.buf;
  glGetFloatv(c->name, &ret->params);
  check_gl_err();
  ret->cmd = GLSC_glGetFloatv;
  glse_cmd_send_data(0,sizeof(gls_ret_glGetFloatv_t),(char *)glsec_global.tmp_buf.buf);
}


void glse_glGetIntegerv()
{
  GLSE_SET_COMMAND_PTR(c, glGetIntegerv);
  gls_ret_glGetIntegerv_t *ret = (gls_ret_glGetIntegerv_t *)glsec_global.tmp_buf.buf;
  glGetIntegerv(c->name, &ret->params);
  check_gl_err();
  ret->cmd = GLSC_glGetIntegerv;
  glse_cmd_send_data(0,sizeof(gls_ret_glGetIntegerv_t),(char *)glsec_global.tmp_buf.buf);
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


void glse_glGetProgramiv()
{
  GLSE_SET_COMMAND_PTR(c, glGetProgramiv);
  gls_ret_glGetProgramiv_t *ret = (gls_ret_glGetProgramiv_t *)glsec_global.tmp_buf.buf;
  glGetProgramiv(c->program,c->pname,&ret->params);
  check_gl_err();
  ret->cmd = GLSC_glGetProgramiv;
  glse_cmd_send_data(0,sizeof(gls_ret_glGetProgramiv_t),(char *)glsec_global.tmp_buf.buf);
}


void glse_glGetShaderiv()
{
  GLSE_SET_COMMAND_PTR(c, glGetShaderiv);
  gls_ret_glGetShaderiv_t *ret = (gls_ret_glGetShaderiv_t *)glsec_global.tmp_buf.buf;
  glGetShaderiv(c->shader,c->pname,&ret->params);
  check_gl_err();
  // LOGD("GLGetShaderiv from %p return %p or with address it become %p", c->pname, ret->params, &ret->params);
  ret->cmd = GLSC_glGetShaderiv;
  glse_cmd_send_data(0,sizeof(gls_ret_glGetShaderiv_t),(char *)glsec_global.tmp_buf.buf);
}


void glse_glGetString()
{
  GLSE_SET_COMMAND_PTR(c, glGetString);
  gls_ret_glGetString_t *ret = (gls_ret_glGetString_t *)glsec_global.tmp_buf.buf;
  const char *params = glGetString(c->name);
  check_gl_err();
  ret->cmd = GLSC_glGetString;
  // LOGD("Client asking for %i, return %s", c->name, params);
  ret->params[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(ret->params, params, GLS_STRING_SIZE);
  glse_cmd_send_data(0,sizeof(gls_ret_glGetString_t),(char *)glsec_global.tmp_buf.buf);
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


// Based from glTexImage2D
void glse_glTexSubImage2D()
{
  GLSE_SET_COMMAND_PTR(c, glTexSubImage2D);
  glTexSubImage2D(c->target, c->level, c->xoffset, c->yoffset, c->width, c->height, c->format, c->type, c->pixels);
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


void glse_glBlendFunc()
{
  GLSE_SET_COMMAND_PTR(c, glBlendFunc);
  glBlendFunc(c->sfactor, c->dfactor);
  check_gl_err();
}


void glse_glCullFace()
{
  GLSE_SET_COMMAND_PTR(c, glCullFace);
  glActiveTexture(c->mode);
  check_gl_err();
}


void glse_glDepthMask()
{
  GLSE_SET_COMMAND_PTR(c, glDepthMask);
  glDepthMask(c->flag);
  check_gl_err();
}


void glse_glDepthRangef()
{
  GLSE_SET_COMMAND_PTR(c, glDepthRangef);
  glDepthRangef(c->zNear, c->zFar);
  check_gl_err();
}


void glse_glStencilFunc()
{
  GLSE_SET_COMMAND_PTR(c, glStencilFunc);
  glStencilFunc(c->func, c->r, c->m);
  check_gl_err();
}


void glse_glStencilOp()
{
  GLSE_SET_COMMAND_PTR(c, glStencilOp);
  glStencilOp(c->fail, c->zfail, c->zpass);
  check_gl_err();
}


void glse_glPolygonOffset()
{
  GLSE_SET_COMMAND_PTR(c, glPolygonOffset);
  glPolygonOffset(c->factor, c->units);
  check_gl_err();
}


void glse_glStencilMask()
{
  GLSE_SET_COMMAND_PTR(c, glStencilMask);
  glStencilMask(c->mask);
  check_gl_err();
}


void glse_glLineWidth()
{
  GLSE_SET_COMMAND_PTR(c, glLineWidth);
  glLineWidth(c->width);
  check_gl_err();
}


void glse_glHint()
{
  GLSE_SET_COMMAND_PTR(c, glHint);
  glHint(c->target, c->mode);
  check_gl_err();
}


void glse_glClearDepthf()
{
  GLSE_SET_COMMAND_PTR(c, glClearDepthf);
  glClearDepthf(c->depth);
  check_gl_err();
}


void glse_glReadPixels()
{
  GLSE_SET_COMMAND_PTR(c, glReadPixels);
  gls_ret_glReadPixels_t *ret = (gls_ret_glReadPixels_t *)glsec_global.tmp_buf.buf;
  glReadPixels(c->x, c->y, c->width, c->height, c->format, c->type, &ret->pixels);
  check_gl_err();
  ret->cmd = glReadPixels;
  glse_cmd_send_data(0, sizeof(gls_ret_glReadPixels_t), (char *)glsec_global.tmp_buf.buf);
  
  // gls_cmd_send_data(0, (uint32_t) (c->width * c->height) /* correct??? */ , (void *)ret->pixels);
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


