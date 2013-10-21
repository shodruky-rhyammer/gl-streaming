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


#include <stdlib.h>
#include <stdint.h>

#include "fifo.h"

int fifo_init(fifo_t *fifo, unsigned int fifo_size_in_bits, unsigned int fifo_packet_size_in_bits)
{
  fifo->fifo_size = 1 << fifo_size_in_bits;
  fifo->fifo_packet_size = 1 << fifo_packet_size_in_bits;
  unsigned int alignment = fifo->fifo_packet_size;
  fifo->buffer = (char *)malloc(fifo->fifo_size * fifo->fifo_packet_size + alignment);
  if (fifo->buffer == NULL)
  {
    return -1;
  }
#if __WORDSIZE == 64
  fifo->p_start = (char *)(((uint64_t)fifo->buffer + alignment - 1) & (uint64_t)(~ (alignment - 1)));
#else
  fifo->p_start = (char *)(((uint32_t)fifo->buffer + alignment - 1) & (uint32_t)(~ (alignment - 1)));
#endif
  fifo->idx_reader = 0;
  fifo->idx_writer = 0;
  return 0;
}

int fifo_delete(fifo_t *fifo)
{
  free(fifo->buffer);
  fifo->buffer = NULL;
  fifo->p_start = NULL;
  fifo->idx_reader = 0;
  fifo->idx_writer = 0;
  fifo->fifo_size = 0;
  fifo->fifo_packet_size = 0;
  return 0;
}
