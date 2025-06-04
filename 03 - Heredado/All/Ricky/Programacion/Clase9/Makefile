CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./
all : clean main main2

main: main.c def.h funciones.h archivo.h clave.h semaforo.h memoria.h thread.h global.h
	$(CC) -o main main.c funciones.c archivo.c clave.c semaforo.c memoria.c thread.c global.c $(CFLAGS) $(HEADERS)

main2: main2.c def.h funciones.h archivo.h clave.h semaforo.h memoria.h thread.h global.h cronometro.h
	$(CC) -o main2 main2.c funciones.c archivo.c clave.c semaforo.c memoria.c thread.c global.c cronometro.c $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o main2 main
	
	
	
