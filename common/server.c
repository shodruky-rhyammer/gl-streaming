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

#include "server.h"

#ifdef __ANDROID__
#include "fastlog.h"
#endif


#define TRUE 1
#define FALSE 0

void server_init(server_context_t *c)
{
  c->err = FALSE;
  c->fifo_packet_size_in_bits = FIFO_PACKET_SIZE_IN_BITS;
  c->fifo_size_in_bits = FIFO_SIZE_IN_BITS;
  c->sleep_usec = SLEEP_USEC;
  c->max_mbps = MAX_MBPS;
}


void * server_thread(void * arg)
{
  server_context_t * a = (server_context_t *)arg;
  int quit = FALSE;

  while (quit == FALSE) {
    char* pushptr = fifo_push_ptr_get(&a->fifo);
    if (pushptr == NULL) {
      LOGW("FIFO full!\n");
      usleep(a->sleep_usec);
    } else {
      int recive_size = recvfrom(a->sock_fd, pushptr, a->max_packet_size, 0, NULL, NULL);
      if (recive_size == -1) {
        LOGE("Socket recvfrom Error.\n");
        quit = TRUE;
      } else {
        LOGI("Socket recvfrom Success!\n");
	  }
      fifo_push_ptr_next(&a->fifo);
    }
  }

  pthread_exit(NULL);
}


void set_fifo_packet_size_in_bits(server_context_t *c, unsigned int bits)
{
  c->fifo_packet_size_in_bits = bits;
}


void set_fifo_size_in_bits(server_context_t *c, unsigned int bits)
{
  c->fifo_size_in_bits = bits;
}


void set_sleep_time(server_context_t *c, unsigned int usec)
{
  c->sleep_usec = usec;
}


void set_max_mbps(server_context_t *c, unsigned int mbps)
{
  c->max_mbps = mbps;
}


#ifdef __ANDROID__ // GL_SERVER
void set_server_address_port(server_context_t *c, char * addr, uint16_t port)
{
  strncpy(c->server_thread_arg.addr, addr, sizeof(c->server_thread_arg.addr));
  c->server_thread_arg.port = port;
}


void set_client_address_port(server_context_t *c, char * addr, uint16_t port)
{
  strncpy(c->popper_thread_arg.addr, addr, sizeof(c->popper_thread_arg.addr));
  c->popper_thread_arg.port = port;
}


void set_client_user_context(server_context_t *c, void *ptr)
{
  c->popper_thread_arg.user_context_ptr = ptr;
}


#else // GL_CLIENT
void set_address_port(server_context_t *c, char * addr, uint16_t port)
{
  strncpy(c->addr, addr, sizeof(c->addr));
  c->port = port;
}


void set_bind_address_port(server_context_t *c, char * addr, uint16_t port)
{
  strncpy(c->bind_addr, addr, sizeof(c->bind_addr));
  c->bind_port = port;
}

#endif // GL_CLIENT


void socket_open(server_context_t *c)
{
// There's nothing same to merge
#ifdef __ANDROID__ // GL_SERVER
  c->server_thread_arg.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (c->server_thread_arg.sock_fd == -1)
  {
    LOGE("Server Socket Open Error.");
    // exit(EXIT_FAILURE);
  } else {
    LOGI("Server Socket Open Success!\n");
  }

  c->popper_thread_arg.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (c->popper_thread_arg.sock_fd == -1)
  {
    LOGE("Client Socket Open Error.");
    // exit(EXIT_FAILURE);
  } else {
    LOGI("Client Socket Open Success!\n");
  }

  c->server_thread_arg.sai.sin_family = AF_INET;
  c->server_thread_arg.sai.sin_port = htons(c->server_thread_arg.port);
  c->server_thread_arg.sai.sin_addr.s_addr = inet_addr(c->server_thread_arg.addr);

  c->popper_thread_arg.sai.sin_family = AF_INET;
  c->popper_thread_arg.sai.sin_port = htons(c->popper_thread_arg.port);
  c->popper_thread_arg.sai.sin_addr.s_addr = inet_addr(c->popper_thread_arg.addr);

  if (bind(c->server_thread_arg.sock_fd, (struct sockaddr *)&c->server_thread_arg.sai, sizeof(struct sockaddr_in)) == -1)
  {
    LOGE("Socket Bind Error.");
    // exit(EXIT_FAILURE);
  } else {
    printf("Socket Bind Success!\n");
  }
#else // GL_CLIENT
  struct sockaddr_in sai;
  c->sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (c->sock_fd == -1)
  {
    printf("Server Socket Open Error.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Server Socket Open Success!\n");
  }

  c->sai.sin_family = AF_INET;
  c->sai.sin_port = htons(c->port);
  c->sai.sin_addr.s_addr = inet_addr(c->addr);

  sai.sin_family = AF_INET;
  sai.sin_port = htons(c->bind_port);
  sai.sin_addr.s_addr = inet_addr(c->bind_addr);

  if (bind(c->sock_fd, (struct sockaddr *)&sai, sizeof(struct sockaddr_in)) == -1)
  {
    printf("Socket Bind Error.\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Socket Bind Success!\n");
  }
#endif // GL_CLIENT
}


void socket_close(server_context_t *c)
{
#ifdef __ANDROID__ // GL_SERVER
  close(c->server_thread_arg.sock_fd);
  close(c->popper_thread_arg.sock_fd);
#else // GL_CLIENT
  close(c->sock_fd);
#endif // GL_CLIENT
}


#ifdef __ANDROID__ // GL_SERVER
void server_run(server_context_t *c, void *(*popper_thread)(void *))
{
  fifo_init(&c->fifo, c->fifo_size_in_bits, c->fifo_packet_size_in_bits);
  c->server_thread_arg.fifo = &c->fifo;
  c->popper_thread_arg.fifo = &c->fifo;
  c->server_thread_arg.max_packet_size = 1 << c->fifo_packet_size_in_bits;
  c->popper_thread_arg.max_packet_size = 1 << c->fifo_packet_size_in_bits;
  c->server_thread_arg.sleep_usec = c->sleep_usec;
  c->popper_thread_arg.sleep_usec = c->sleep_usec;
  c->server_thread_arg.max_mbps = c->max_mbps;
  c->popper_thread_arg.max_mbps = c->max_mbps;
  socket_open(c);
  pthread_create(&c->server_th, NULL, (void* (*)(void*))server_thread, &c->server_thread_arg);
  pthread_create(&c->popper_th, NULL, popper_thread, &c->popper_thread_arg);
  pthread_join(c->popper_th, NULL);
  
  // From https://github.com/tinmaniac/gl-streaming/blob/master/gl_server/server.c#L188
// #ifdef __ANDROID__
  // this is wrong, but android has no pthread_cancel
  // see stack overflow for a better solution that uses a SIGUSR1 handler
  // that I don't have time to implement right now
  // http://stackoverflow.com/questions/4610086/pthread-cancel-alternatives-in-android-ndk
//   pthread_kill(c->server_th, SIGUSR1);
// #else
//   pthread_cancel(c->server_th);
// #endif
  
  socket_close(c);
  fifo_delete(&c->fifo);
}


#else // GL_CLIENT
void *server_start(server_context_t *c)
{
  fifo_init(&c->fifo, c->fifo_size_in_bits, c->fifo_packet_size_in_bits);
  c->max_packet_size = 1 << c->fifo_packet_size_in_bits;

  socket_open(c);

  pthread_create(&c->server_th, NULL, (void* (*)(void*))server_thread, c);
  return c;
}


void server_stop(server_context_t *c)
{
    pthread_cancel(c->server_th);

    socket_close(c);
    fifo_delete(&c->fifo);
}
#endif // GL_CLIENT
