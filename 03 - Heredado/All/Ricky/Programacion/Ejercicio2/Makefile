CC=gcc-4.1
CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean programa1 programa2 

programa1: caja.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h
	$(CC) -o caja caja.c archivos.c clave.c semaforo.c funciones.c $(CFLAGS) $(HEADERS)

programa2: derivador.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h
	$(CC) -o derivador derivador.c archivos.c clave.c semaforo.c funciones.c $(CFLAGS) $(HEADERS)
	touch caja.txt
	rm caja.txt
	touch caja.txt

clean:
	rm -rf *.o derivador caja
