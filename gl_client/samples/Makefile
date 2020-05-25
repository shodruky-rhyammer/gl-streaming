CFLAGS=-O3 -Wall

INCLUDES=-I.. -I../include -I../../common
LIBS=-L.. -lpthread -lm -lGLESv2
EXES=sample1 sample2

all: $(EXES)

sample1: sample1.c
	gcc -o sample1 $(CFLAGS) sample1.c $(OBJS) $(INCLUDES) $(LIBS)

sample2: sample2.c
	gcc -o sample2 $(CFLAGS) sample2.c $(OBJS) $(INCLUDES) $(LIBS)

clean:
	rm $(EXES)
