CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors 
HEADERS = -I./
all : clean programa

programa: avion.c def.h funciones.h archivos.h clave.h semaforo.h
	$(CC) -o avion avion.c funciones.c archivos.c clave.c semaforo.c $(CFLAGS) $(HEADERS)


programa2: panel.c def.h funciones.h archivos.h clave.h semaforo.h
	$(CC) -o panel panel.c funciones.c archivos.c clave.c semaforo.c $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o avion panel