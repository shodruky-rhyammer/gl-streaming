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

  while (quit == FALSE)
  {
    char* pushptr = fifo_push_ptr_get(&a->fifo);
    if (pushptr == NULL)
    {
      printf("FIFO full!\n");
      usleep(a->sleep_usec);
    }
    else
    {
      int recive_size = recvfrom(a->sock_fd, pushptr, a->max_packet_size, 0, NULL, NULL);
      if (recive_size == -1)
      {
        printf("Socket recvfrom Error.\n");
        quit = TRUE;
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


void socket_open(server_context_t *c)
{
  struct sockaddr_in sai;
  c->sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (c->sock_fd == -1)
  {
    printf("Server Socket Open Error.\n");
    exit(EXIT_FAILURE);
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
  }
}


void socket_close(server_context_t *c)
{
  close(c->sock_fd);
}


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
