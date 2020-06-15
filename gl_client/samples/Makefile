CFLAGS=-O3 -Wall

INCLUDES=-I.. -I../include -I../../common
LIBS=-lpthread -lm -ldl
OBJS=../fifo.o ../server.o ../glclient.o ../glsutil.o ../clientegl.o ../clientgles.o
EXES=sample1 sample2

all: $(EXES)

fifo.o: ../../common/fifo.c ../../common/fifo.h
	gcc -c -o ../fifo.o $(CFLAGS) $(INCLUDES) ../../common/fifo.c

server.o: ../../common/server.c ../../common/server.h ../fifo.o
	gcc -c -o ../server.o $(CFLAGS) $(INCLUDES) ../../common/server.c

glclient.o: ../glclient.c ../glclient.h ../../common/gls_command.h ../server.o
	gcc -c -o ../glclient.o $(CFLAGS) $(INCLUDES) ../glclient.c

glsutil.o: ../glsutil.c ../glsutil.h
	gcc -c -o ../glsutil.o $(CFLAGS) $(INCLUDES) ../glsutil.c

clientegl.o: ../clientegl.c ../include/EGL/egl.h
	gcc -c -o ../clientegl.o $(CFLAGS) ../clientegl.c

clientgles.o: ../clientgles.c ../include/GLES2/gl2.h
	gcc -c -o ../clientgles.o $(CFLAGS) ../clientgles.c

sample1: sample1.c ../glclient.o ../glsutil.o ../clientegl.o ../clientgles.o
	gcc -o sample1 $(CFLAGS) $(INCLUDES) sample1.c $(OBJS) $(LIBS)

sample2: sample2.c ../glclient.o ../glsutil.o ../clientegl.o ../clientgles.o
	gcc -o sample2 $(CFLAGS) $(INCLUDES) sample2.c $(OBJS) $(LIBS)

