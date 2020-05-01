CFLAGS=-O3 -Wall

LIBS=-lpthread -lm
OBJS=fifo.o server.o glclient.o glsutil.o
EXES=sample1 sample2
TOOLCHAIN=aarch64-linux-gnu-gcc
all: $(EXES)

fifo.o: fifo.c fifo.h
	$(TOOLCHAIN) -c -o fifo.o $(CFLAGS) fifo.c

server.o: server.c server.h fifo.o
	$(TOOLCHAIN) -c -o server.o $(CFLAGS) server.c

glclient.o: glclient.c glclient.h gls_command.h server.o
	$(TOOLCHAIN) -c -o glclient.o $(CFLAGS) glclient.c

glsutil.o: glsutil.c glsutil.h
	$(TOOLCHAIN) -c -o glsutil.o $(CFLAGS) glsutil.c

sample1: sample1.c glclient.o glsutil.o
	$(TOOLCHAIN) -o sample1 $(CFLAGS) sample1.c $(OBJS) $(LIBS)

sample2: sample2.c glclient.o glsutil.o
	$(TOOLCHAIN) -o sample2 $(CFLAGS) sample2.c $(OBJS) $(LIBS)

clean:
	rm $(EXES) $(OBJS)
