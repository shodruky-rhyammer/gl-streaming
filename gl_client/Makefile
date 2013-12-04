CFLAGS=-O3 -Wall

LIBS=-lpthread -lm
OBJS=fifo.o server.o glclient.o glsutil.o
EXES=sample1 sample2

all: $(EXES)

fifo.o: fifo.c fifo.h
	gcc -c -o fifo.o $(CFLAGS) fifo.c

server.o: server.c server.h fifo.o
	gcc -c -o server.o $(CFLAGS) server.c

glclient.o: glclient.c glclient.h gls_command.h server.o
	gcc -c -o glclient.o $(CFLAGS) glclient.c

glsutil.o: glsutil.c glsutil.h
	gcc -c -o glsutil.o $(CFLAGS) glsutil.c

sample1: sample1.c glclient.o glsutil.o
	gcc -o sample1 $(CFLAGS) sample1.c $(OBJS) $(LIBS)

sample2: sample2.c glclient.o glsutil.o
	gcc -o sample2 $(CFLAGS) sample2.c $(OBJS) $(LIBS)

clean:
	rm $(EXES) $(OBJS)
