CC=gcc-4.1
CFLAGS=-pedantic-errors -O3 -std=gnu89
LDFLAGS=-lpthread
HEADERS=-I./
C1=Coliseo.c archivos.c clave.c cola.c semaforo.c funciones.c memoria.c global.c 
C2=creadorhilos.c hilos.c archivos.c clave.c cola.c semaforo.c funciones.c memoria.c global.c

all: clean programa1 programa2 

programa1: Coliseo.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h cola.c cola.h memoria.c memoria.h global.c global.h
	$(CC) -o Coliseo $(C1) $(CFLAGS) $(HEADERS) $(LDFLAGS)

programa2: creadorhilos.c hilos.c hilos.h clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h cola.c cola.h memoria.c memoria.h global.c global.h
	$(CC) -o Peleadores $(C2) $(CFLAGS) $(HEADERS) $(LDFLAGS)
	touch suceso.txt
	rm suceso.txt
	touch suceso.txt

clean:
	rm -rf *.o Coliseo Peleadores 