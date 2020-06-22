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
#include "pthread.h"

#define SLEEP_USEC 1000
#define FIFO_SIZE_IN_BITS 10
#define FIFO_PACKET_SIZE_IN_BITS 11
#define MAX_MBPS 100


// GL_SERVER
typedef struct
{
  struct sockaddr_in sai;
  int sock_fd;
  char addr[256];
  uint16_t port;
  fifo_t * fifo;
  size_t max_packet_size;
  useconds_t sleep_usec;
  int max_mbps;
  void * user_context_ptr;
} server_thread_args_t;


typedef struct
{
  pthread_t server_th, popper_th;
  int err;
  fifo_t fifo;
  int sock_fd;
  size_t max_packet_size;
  unsigned int fifo_packet_size_in_bits;
  unsigned int fifo_size_in_bits;
  unsigned int sleep_usec;
  unsigned int max_mbps;
  
  // GL_SERVER
  server_thread_args_t server_thread_arg, popper_thread_arg;
  
  // GL_CLIENT
  uint16_t port;
  char addr[256];
  char bind_addr[256];
  uint16_t bind_port;
  struct sockaddr_in sai;
} server_context_t;


#ifdef __cplusplus
extern "C" {
#endif

  void* server_thread(void* arg);
  void server_init(server_context_t *c);
  void set_fifo_packet_size_in_bits(server_context_t *c, unsigned int bits);
  void set_fifo_size_in_bits(server_context_t *c, unsigned int bits);
  void set_sleep_time(server_context_t *c, unsigned int usec);
  void set_max_mbps(server_context_t *c, unsigned int mbps);
  
  // GL_SERVER
  void set_server_address_port(server_context_t *c, char * addr, uint16_t port);
  void set_client_address_port(server_context_t *c, char * addr, uint16_t port);
  void set_client_user_context(server_context_t *c, void *ptr);
  void server_run(server_context_t *c, void *(*popper_thread)(void *));

  // GL_CLIENT
  void socket_open(server_context_t *c);
  void socket_close(server_context_t *c);

#ifdef __cplusplus
}
#endif



