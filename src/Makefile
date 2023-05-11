CC=gcc

OBJ_DIR = object

all: start

start : clean main.o functions.o gfunctions.o ./include/grafos.h ./include/header.h 
	$(CC) -o start main.o functions.o gfunctions.o ./include/grafos.h ./include/header.h

main.o : main.c
	$(CC) -c main.c

functions.o : functions.c
	$(CC) -c functions.c

gfunctions.o : gfunctions.c
	$(CC) -c gfunctions.c

clean : 
	del /Q /F start.exe *.o || rm -f *.o start