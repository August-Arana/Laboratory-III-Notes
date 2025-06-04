CC=gcc-4.1
CFLAGS=-pedantic-errors -O3 -std=gnu89
LDFLAGS=-lpthread
HEADERS=-I./
C1=Derivador.c archivos.c clave.c cola.c semaforo.c funciones.c memoria.c global.c 
C2=creadorhilos.c hilos.c archivos.c clave.c cola.c semaforo.c funciones.c memoria.c global.c

all: clean programa1 programa2 

programa1: $(C1) clave.h semaforo.h def.h archivos.h funciones.h cola.h memoria.h global.h
	$(CC) -o Derivador $(C1) $(CFLAGS) $(HEADERS) $(LDFLAGS)

programa2: $(C2) hilos.h clave.h semaforo.h def.h archivos.h funciones.h cola.h memoria.h global.h
	$(CC) -o Cajas $(C2) $(CFLAGS) $(HEADERS) $(LDFLAGS)

clean:
	rm -rf *.o Derivador Cajas