CC=gcc-4.1

CFLAGS =  -O3 -std=gnu89 -pedantic-errors -pthread
HEADERS = -I./
all : clean tablero ciudad 

tablero: main.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h memoria.c memoria.h cola_mensajes.c cola_mensajes.h tiempos.c tiempos.h global.c global.h
	$(CC) -o tablero main.c archivos.c clave.c semaforo.c funciones.c memoria.c tiempos.c cola_mensajes.c global.c $(CFLAGS) $(HEADERS)

ciudad: main2.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h memoria.c memoria.h cola_mensajes.c cola_mensajes.h threadCiudad.c threadCiudad.h tiempos.c tiempos.h global.c global.h
	$(CC) -o ciudad main2.c archivos.c clave.c semaforo.c funciones.c memoria.c threadCiudad.c tiempos.c cola_mensajes.c global.c $(CFLAGS) $(HEADERS)



clean:
	rm -rf *o tablero ciudad
