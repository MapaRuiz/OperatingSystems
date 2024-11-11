all:main

main: main.o hilos.o
	gcc -o main main.o hilos.o -lpthread

main.o: main.c hilos.h
	gcc -c main.c

hilos.o: hilos.c hilos.h
	gcc -c hilos.c

clean: 
	rm -f *.o main

run: main
	./main
