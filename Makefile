CC=gcc
CFLAGS=-g -o main -lm

all:	main
	
log:	CFLAGS += -Dlogging
log:	clean main

delta:	CFLAGS += -DDELTA=1
delta:	clean main

main: main.c graph.h
	$(CC) $(CFLAGS) main.c

clean:
	-rm -f main
