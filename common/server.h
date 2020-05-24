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


#include <arpa/inet.h>

#include "fifo.h"


#define SLEEP_USEC 1000
#define FIFO_SIZE_IN_BITS 10
#define FIFO_PACKET_SIZE_IN_BITS 11
#define MAX_MBPS 100

typedef struct
{
  pthread_t server_th;
  int err;
  fifo_t fifo;
  unsigned int fifo_packet_size_in_bits;
  unsigned int fifo_size_in_bits;
  unsigned int sleep_usec;
  unsigned int max_mbps;
  size_t max_packet_size;
  uint16_t port;
  char addr[256];
  char bind_addr[256];
  uint16_t bind_port;
  int sock_fd;
  struct sockaddr_in sai;
} server_context_t;


#ifdef __cplusplus
extern "C" {
#endif

  void * server_thread(void * arg);
  void server_init(server_context_t *c);
  void *server_start(server_context_t *c);
  void server_stop(server_context_t *sc);
  void set_address_port(server_context_t *c, char * addr, uint16_t port);
  void set_bind_address_port(server_context_t *c, char * addr, uint16_t port);
  void set_fifo_packet_size_in_bits(server_context_t *c, unsigned int bits);
  void set_fifo_size_in_bits(server_context_t *c, unsigned int bits);
  void set_sleep_time(server_context_t *c, unsigned int usec);
  void set_max_mbps(server_context_t *c, unsigned int mbps);
  void socket_open(server_context_t *c);
  void socket_close(server_context_t *c);

#ifdef __cplusplus
}
#endif


