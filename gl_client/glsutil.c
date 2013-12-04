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
#include <math.h>
#include "glsutil.h"


#define TRUE 1
#define FALSE 0


void mat_mul(float *a, float *b)
{
  float c[16];
  c[0]  = a[0] * b[0]  + a[4] * b[1]  + a[8]  * b[2]  + a[12] * b[3];
  c[1]  = a[1] * b[0]  + a[5] * b[1]  + a[9]  * b[2]  + a[13] * b[3];
  c[2]  = a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2]  + a[14] * b[3];
  c[3]  = a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2]  + a[15] * b[3];
  c[4]  = a[0] * b[4]  + a[4] * b[5]  + a[8]  * b[6]  + a[12] * b[7];
  c[5]  = a[1] * b[4]  + a[5] * b[5]  + a[9]  * b[6]  + a[13] * b[7];
  c[6]  = a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6]  + a[14] * b[7];
  c[7]  = a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6]  + a[15] * b[7];
  c[8]  = a[0] * b[8]  + a[4] * b[9]  + a[8]  * b[10] + a[12] * b[11];
  c[9]  = a[1] * b[8]  + a[5] * b[9]  + a[9]  * b[10] + a[13] * b[11];
  c[10] = a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10] + a[14] * b[11];
  c[11] = a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10] + a[15] * b[11];
  c[12] = a[0] * b[12] + a[4] * b[13] + a[8]  * b[14] + a[12] * b[15];
  c[13] = a[1] * b[12] + a[5] * b[13] + a[9]  * b[14] + a[13] * b[15];
  c[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
  c[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];
  a[0] =  c[0];  a[1] =  c[1];  a[2] =  c[2];   a[3] =  c[3];
  a[4] =  c[4];  a[5] =  c[5];  a[6] =  c[6];   a[7] =  c[7];
  a[8] =  c[8];  a[9] =  c[9];  a[10] = c[10];  a[11] = c[11];
  a[12] = c[12]; a[13] = c[13]; a[14] = c[14];  a[15] = c[15];
}


void mat_rotate_x(float *a, float angle)
{
  float c4, c5, c6, c7, c8, c9, c10, c11;
  float s = sin(angle);
  float c = cos(angle);
  c4  = a[4]  * c + a[8]  * s;
  c5  = a[5]  * c + a[9]  * s;
  c6  = a[6]  * c + a[10] * s;
  c7  = a[7]  * c + a[11] * s;
  c8  = a[8]  * c - a[4]  * s;
  c9  = a[9]  * c - a[5]  * s;
  c10 = a[10] * c - a[6]  * s;
  c11 = a[11] * c - a[7]  * s;
  a[4] = c4; a[5] = c5; a[6] =  c6;  a[7] =  c7;
  a[8] = c8; a[9] = c9; a[10] = c10; a[11] = c11;
}


void mat_rotate_y(float *a, float angle)
{
  float c0, c1, c2, c3, c8, c9, c10, c11;
  float s = sin(angle);
  float c = cos(angle);
  c0  = a[0] * c  - a[8]  * s;
  c1  = a[1] * c  - a[9]  * s;
  c2  = a[2] * c  - a[10] * s;
  c3  = a[3] * c  - a[11] * s;
  c8  = a[0] * s  + a[8]  * c;
  c9  = a[1] * s  + a[9]  * c;
  c10 = a[2] * s  + a[10] * c;
  c11 = a[3] * s  + a[11] * c;
  a[0] = c0; a[1] = c1; a[2] =  c2;  a[3] =  c3;
  a[8] = c8; a[9] = c9; a[10] = c10; a[11] = c11;
}


void mat_rotate_z(float *a, float angle)
{
  float c0, c1, c2, c3, c4, c5, c6, c7;
  float s = sin(angle);
  float c = cos(angle);
  c0  = a[0] * c + a[4] * s;
  c1  = a[1] * c + a[5] * s;
  c2  = a[2] * c + a[6] * s;
  c3  = a[3] * c + a[7] * s;
  c4  = a[4] * c - a[0] * s;
  c5  = a[5] * c - a[1] * s;
  c6  = a[6] * c - a[2] * s;
  c7  = a[7] * c - a[3] * s;
  a[0] = c0; a[1] = c1; a[2] = c2; a[3] = c3;
  a[4] = c4; a[5] = c5; a[6] = c6; a[7] = c7;
}


void mat_translate(float *a, float x, float y, float z)
{
  float b12, b13, b14, b15;
  b12 = a[0] * x + a[4] * y + a[8]  * z + a[12];
  b13 = a[1] * x + a[5] * y + a[9]  * z + a[13];
  b14 = a[2] * x + a[6] * y + a[10] * z + a[14];
  b15 = a[3] * x + a[7] * y + a[11] * z + a[15];
  a[12] = b12; a[13] = b13; a[14] = b14;  a[15] = b15;
}


void mat_identity(float *m)
{
  m[0]  = 1.0f; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
  m[4]  = 0.0f; m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = 0.0f;
  m[8]  = 0.0f; m[9]  = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
  m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}


void mat_transpose(float *m)
{
  float a[16];
  a[1]  = m[4];  a[2]  = m[8];  a[3]  = m[12];
  a[4]  = m[1];  a[6]  = m[9];  a[7]  = m[13];
  a[8]  = m[2];  a[9]  = m[6];  a[11] = m[14];
  a[12] = m[3];  a[13] = m[7];  a[14] = m[11];

  m[1]  = a[1];  m[2]  = a[2];  m[3]  = a[3];
  m[4]  = a[4];  m[6]  = a[6];  m[7]  = a[7];
  m[8]  = a[8];  m[9]  = a[9];  m[11] = a[11];
  m[12] = a[12]; m[13] = a[13]; m[14] = a[14];
}


void mat_invert(float *m)
{
  float a[16];
  mat_identity(a);
  a[12] = -m[12]; a[13] = -m[13]; a[14] = -m[14];
  m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f;
  mat_transpose(m);
  mat_mul(m, a);
}


void mat_perspective(float *m, float aspect, float near, float far, float fview)
{
  mat_identity(m);
  float t, dz;
  dz = far - near;
  t = 1.0f / tanf(M_PI * fview / 360.0f);
  aspect = (aspect == 0.0f) ? 0.0000001f : aspect;
  dz = (dz == 0.0f) ? 0.0000001f : dz;
  m[0] = t / aspect;
  m[5] = t;
  m[10] = - (far + near) / dz;
  m[11] = -1.0f;
  m[14] = -2.0f * near * far / dz;
  m[15] = 0.0f;
}


void mat_copy(float *a, float *b)
{
  a[0]  = b[0];  a[1]  = b[1];  a[2]  = b[2];  a[3]  = b[3];
  a[4]  = b[4];  a[5]  = b[5];  a[6]  = b[6];  a[7]  = b[7];
  a[8]  = b[8];  a[9]  = b[9];  a[10] = b[10]; a[11] = b[11];
  a[12] = b[12]; a[13] = b[13]; a[14] = b[14]; a[15] = b[15];
}


int gls_load_bitmap(gls_bitmap_t *bitmap, const char *filename)
{
  gls_bmp_header_t header;
  FILE *file;
  bitmap->width = 0;
  bitmap->height = 0;
  bitmap->bitmap = NULL;
  file = fopen(filename, "rb");
  if (file == NULL)
  {
    perror("Error: gls_load_bitmap: file open error.\n");
    return FALSE;
  }
  if (fread(&header, 1, sizeof(header), file) != sizeof(header))
  {
    perror("Error: gls_load_bitmap: header read error.\n");
    fclose(file);
    return FALSE;
  }
  if (header.file_type != 0x4d42)
  {
    perror("Error: gls_load_bitmap: not a bmp file.\n");
    return FALSE;
  }
  if (header.bpp != 32)
  {
    perror("Error: gls_load_bitmap: only 32bit bmp supported.\n");
    return FALSE;
  }
  if (header.compression != 0)
  {
    perror("Error: gls_load_bitmap: no compression supported.\n");
    return FALSE;
  }
  bitmap->width = header.width;
  bitmap->height = header.height;
  size_t size = header.width * header.height * header.bpp / 8;
  char *tmpbuf = malloc(size);
  if (tmpbuf == NULL)
  {
    fclose(file);
    return FALSE;
  }
  bitmap->bitmap = malloc(size);
  if (bitmap->bitmap == NULL)
  {
    free(tmpbuf);
    fclose(file);
    return FALSE;
  }
  fseek(file, header.data_offset, SEEK_SET);
  size_t size1 = fread(tmpbuf, 1, size, file);
  if (size1 != size)
  {
    perror("Error: gls_load_bitmap: bitmap read error\n");
    free(bitmap->bitmap);
    bitmap->bitmap = NULL;
    free(tmpbuf);
    fclose(file);
    return FALSE;
  }
  unsigned int x, y;
  for (y = 0; y < header.height; y++)
  {
    for (x = 0; x < header.width; x++)
    {
      unsigned int offset = (y * header.width + x) * (header.bpp / 8);
      uint32_t argb = *(uint32_t *)(tmpbuf + offset);
      uint32_t a = argb >> 24;
      uint32_t r = (argb >> 16) & 0xff;
      uint32_t g = (argb >> 8) & 0xff;
      uint32_t b = argb & 0xff;
      uint32_t rgba = (a << 24) | (b << 16) | (g << 8) | r;
      *(uint32_t *)(bitmap->bitmap + offset) = rgba;
    }
  }
  free(tmpbuf);
  fclose(file);
  return TRUE;
}


void gls_delete_bitmap(gls_bitmap_t *bitmap)
{
  free(bitmap->bitmap);
  bitmap->width = 0;
  bitmap->height = 0;
  bitmap->bitmap = NULL;
}


