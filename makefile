
default: release
	
debug: main.c
	gcc -o program.o main.c -fopenmp -lgomp -g -DDEBUG=1

release: main.c
	gcc -o program.o main.c -fopenmp -lgomp -g -DDEBUG=0

clean:
	rm -f *.o