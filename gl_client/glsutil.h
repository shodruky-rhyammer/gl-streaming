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


#include <stdint.h>


typedef struct
{
  uint16_t file_type;
  uint32_t file_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t data_offset;
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t plane;
  uint16_t bpp;
  uint32_t compression;
  uint32_t image_size;
} __attribute__ ((__packed__)) gls_bmp_header_t;


typedef struct
{
  unsigned int width;
  unsigned int height;
  char *bitmap;
} gls_bitmap_t;


#ifdef __cplusplus
extern "C" {
#endif

void mat_mul(float *a, float *b);
void mat_rotate_x(float *a, float angle);
void mat_rotate_y(float *a, float angle);
void mat_rotate_z(float *a, float angle);
void mat_translate(float *a, float x, float y, float z);
void mat_identity(float *m);
void mat_transpose(float *m);
void mat_invert(float *m);
void mat_perspective(float *m, float aspect, float near, float far, float fview);
void mat_copy(float *a, float *b);
int gls_load_bitmap(gls_bitmap_t *bitmap, const char *filename);
void gls_delete_bitmap(gls_bitmap_t *bitmap);

#ifdef __cplusplus
}
#endif

