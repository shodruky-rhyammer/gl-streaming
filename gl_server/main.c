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
#include <arpa/inet.h>
#include <string.h>

#include "glserver.h"
#include "main.h"


int main(int argc, char * argv[])
{
  static server_context_t sc;
  int opt;
  char my_ip[GLS_STRING_SIZE_PLUS];
  char his_ip[GLS_STRING_SIZE_PLUS];
  uint16_t my_port = 12345;
  uint16_t his_port = 12346;
  strncpy(my_ip, "127.0.0.1", GLS_STRING_SIZE);
  strncpy(his_ip, "127.0.0.1", GLS_STRING_SIZE);
  while ((opt = getopt(argc, argv, "s:c:h")) != -1)
  {
    switch (opt)
    {
      case 's':
        strncpy(my_ip, strtok(optarg, ":"), GLS_STRING_SIZE);
        my_port = atoi(strtok(NULL, ":"));
        break;
      case 'c':
        strncpy(his_ip, strtok(optarg, ":"), GLS_STRING_SIZE);
        his_port = atoi(strtok(NULL, ":"));
        break;
      case 'h':
      default:
        printf("Usage: %s [-s my_ip_address:port] [-c client_ip_address:port]\n", argv[0]);
        return 0;
    }
  }
  server_init(&sc);
  set_server_address_port(&sc, my_ip, my_port);
  set_client_address_port(&sc, his_ip, his_port);

  server_run(&sc, glserver_thread);

  return 0;
}

void initGLStreamMain()
{
  static server_context_t sc;
  int opt;
  char server_ip[GLS_STRING_SIZE_PLUS];
  char client_ip[GLS_STRING_SIZE_PLUS];
  uint16_t server_port = 12345;
  uint16_t client_port = 12346;
  strncpy(server_ip, "127.0.0.1", GLS_STRING_SIZE);
  strncpy(client_ip, "127.0.0.1", GLS_STRING_SIZE);
  server_init(&sc);
  set_server_address_port(&sc, server_ip, server_port);
  set_client_address_port(&sc, client_ip, client_port);

  server_run(&sc, glserver_thread);

  // return 0;
}

