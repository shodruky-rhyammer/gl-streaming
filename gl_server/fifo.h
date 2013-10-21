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


typedef struct
{
  char *buffer;
  char *p_start;
  int idx_reader;
  int idx_writer;
  unsigned int fifo_size;
  unsigned int fifo_packet_size;
} fifo_t;

static inline char* fifo_push_ptr_get(fifo_t *fifo)
{
  int next_idx = (fifo->idx_writer + 1) & (fifo->fifo_size - 1);
  if (next_idx == fifo->idx_reader)
  {
    return NULL;
  }
  return fifo->p_start + (fifo->idx_writer * fifo->fifo_packet_size);
}

static inline void fifo_push_ptr_next(fifo_t *fifo)
{
  int next_idx = (fifo->idx_writer + 1) & (fifo->fifo_size - 1);
  if (next_idx != fifo->idx_reader)
  {
    fifo->idx_writer = next_idx;
  }
}

static inline char* fifo_pop_ptr_get(fifo_t *fifo)
{
  if (fifo->idx_reader == fifo->idx_writer)
  {
    return NULL;
  }
  return fifo->p_start + (fifo->idx_reader * fifo->fifo_packet_size);
}

static inline void fifo_pop_ptr_next(fifo_t *fifo)
{
  int next_idx = (fifo->idx_reader + 1) & (fifo->fifo_size - 1);
  if (fifo->idx_reader != fifo->idx_writer)
  {
    fifo->idx_reader = next_idx;
  }
}


#ifdef __cplusplus
extern "C" {
#endif

int fifo_init(fifo_t *fifo, unsigned int fifo_size_in_bits, unsigned int fifo_packet_size_in_bits);

int fifo_delete(fifo_t *fifo);

#ifdef __cplusplus
}
#endif

