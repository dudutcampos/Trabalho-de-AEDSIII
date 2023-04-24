# _*_ MakeFile_*_

all: main.o event.o grafo.o queue.o arquivo.o
	gcc -g main.o event.o grafo.o queue.o arquivo.o -o tp

main.o: main.c event.o grafo.o queue.o
	gcc -g -c main.c

event.o: event.c event.h
	gcc -g -c event.c

grafo.o: grafo.c grafo.h
	gcc -g -c grafo.c

queue.o: queue.c queue.h event.o
	gcc -g -c queue.c

arquivo.o: arquivo.c arquivo.h
	gcc -g -c arquivo.c

clean:
	rm -f *.o tp