#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include "glclient.h"
#include <fcntl.h>
#include <math.h>

void gls_initshared()
{
    static server_context_t sc;
    static int init = 0;
    if( init )
        return;
    int opt;
    char my_ip[GLS_STRING_SIZE_PLUS];
    char his_ip[GLS_STRING_SIZE_PLUS];
    uint16_t my_port = 18146;
    uint16_t his_port = 18145;
	
	const char* env_serverIp = getenv("GLS_SERVER_IP");
	
	if (env_serverIp == NULL) {
		env_serverIp = "127.0.0.1";
	} else {
		printf("GLS_SERVER_IP is set to %s\n", env_serverIp);
	}
	
    strncpy(my_ip, "127.0.0.1", GLS_STRING_SIZE);
    strncpy(his_ip, env_serverIp, GLS_STRING_SIZE);
    server_init(&sc);
    set_bind_address_port(&sc, my_ip, my_port);
    set_address_port(&sc, his_ip, his_port);

    server_start(&sc);
    gls_init(&sc);
    gls_cmd_get_context();
    init = 1;

    // return 0;
}

