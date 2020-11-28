CC = gcc
CFLAGS = -std=c99
OBJS = utility.o main.o

all: CFLAGS += -D DEBUG=0
all: program

debug: CFLAGS += -D DEBUG=1 -g -Wall -Werror
debug: program

program: $(OBJS)
	$(CC) $(CFLAGS) -o program $(OBJS) -fopenmp -lgomp

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

utility.o: utility.c utility.h types.h
	$(CC) $(CFLAGS) -c -o utility.o utility.c -fopenmp -lgomp

clean:
	rm -f $(OBJS) program
