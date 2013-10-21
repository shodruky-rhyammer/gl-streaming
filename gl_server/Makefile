CFLAGS=-O3 -Wall

LIBS=-L/opt/vc/lib/ -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt
INCLUDES=-I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux
OBJS=fifo.o glcontrol.o server.o glserver.o

all: gl_server

fifo.o: fifo.c fifo.h
	gcc -c -o fifo.o $(CFLAGS) fifo.c

glcontrol.o: glcontrol.c glcontrol.h
	gcc -c -o glcontrol.o $(CFLAGS) $(INCLUDES) glcontrol.c

server.o: server.c server.h fifo.o
	gcc -c -o server.o $(CFLAGS) server.c

glserver.o: glserver.c glserver.h gls_command.h glcontrol.o server.o
	gcc -c -o glserver.o $(CFLAGS) $(INCLUDES) glserver.c

gl_server: main.c glserver.o
	gcc -o gl_server $(CFLAGS) $(INCLUDES) $(LIBS) main.c $(OBJS)

clean:
	rm gl_server $(OBJS)
