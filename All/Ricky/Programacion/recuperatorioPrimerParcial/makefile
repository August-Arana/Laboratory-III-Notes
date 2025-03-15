CC=gcc-4.1
CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean programa1 programa2

programa1: equipo.c claves.h claves.c semaforos.h semaforos.c def.h archivo.c archivo.h funciones.c funciones.h
	$(CC) -o equipo equipo.c archivo.c claves.c semaforos.c funciones.c $(CFLAGS) $(HEADERS)
	rm equipos.txt
	touch equipos.txt


programa2: panel.c claves.h claves.c semaforos.h semaforos.c def.h archivo.c archivo.h funciones.c funciones.h
	$(CC) -o panel panel.c archivo.c claves.c semaforos.c funciones.c $(CFLAGS) $(HEADERS)


clean:
	rm -rf *.o panel equipo
