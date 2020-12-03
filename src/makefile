CC = gcc
CFLAGS = -std=c99 -Wall
OBJS = utility.o main.o

all: CFLAGS += -D DEBUG=0
all: program

O2: CFLAGS += -D DEBUG=0 -O2
O2: program

fast: CFLAGS += -D DEBUG=0 -Ofast
fast: program

debug: CFLAGS += -D DEBUG=1 -g -Og
debug: program

program: $(OBJS)
	$(CC) $(CFLAGS) -o program $(OBJS) -fopenmp -lgomp

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

utility.o: utility.c utility.h types.h
	$(CC) $(CFLAGS) -c -o utility.o utility.c -fopenmp -lgomp

clean:
	rm -f $(OBJS) program
