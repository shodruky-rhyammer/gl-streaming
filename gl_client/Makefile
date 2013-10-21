CFLAGS=-O3 -Wall

LIBS=-lpthread -lm
OBJS=fifo.o server.o glclient.o

all: gl_client

fifo.o: fifo.c fifo.h
	gcc -c -o fifo.o $(CFLAGS) fifo.c

server.o: server.c server.h fifo.o
	gcc -c -o server.o $(CFLAGS) server.c

glclient.o: glclient.c glclient.h gls_command.h server.o
	gcc -c -o glclient.o $(CFLAGS) glclient.c

gl_client: main.c glclient.o
	gcc -o gl_client $(CFLAGS) $(LIBS) main.c $(OBJS)

clean:
	rm gl_client $(OBJS)
