CFLAGS=-O3 -Wall -I../common -I. -I./include -fPIC
# Move to define in C code.
# CFLAGS+=-DGL_CLIENT=1

LIBS=-lpthread -lm
OBJS=fifo.o server.o glclient.o

LIB_GLES=libGLESv2.so.2

EXES=$(LIB_GLES)

all: $(EXES)

fifo.o: ../common/fifo.c ../common/fifo.h
	gcc -c -o fifo.o $(CFLAGS) ../common/fifo.c

server.o: ../common/server.c ../common/server.h fifo.o
	gcc -c -o server.o $(CFLAGS) ../common/server.c

glclient.o: glclient.c glclient.h ../common/gls_command.h server.o
	gcc -c -o glclient.o $(CFLAGS) glclient.c

$(LIB_GLES): $(OBJS) glsshared.c
	gcc -shared -o $(LIB_GLES) $(CFLAGS) glsshared.c $(OBJS) -Wl,--no-undefined -pthread -ldl

clean:
	rm $(EXES) $(OBJS)
