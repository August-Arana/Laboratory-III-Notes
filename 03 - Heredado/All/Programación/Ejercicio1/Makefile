CC=gcc-4.1
CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./
all : clean programa1 programa2 

programa1: equipo.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h
	$(CC) -o equipo equipo.c archivos.c clave.c semaforo.c funciones.c $(CFLAGS) $(HEADERS)
	touch japon.txt
	rm japon.txt
	touch japon.txt
	touch argentina.txt
	rm argentina.txt
	touch argentina.txt


programa2: panel.c clave.h clave.c semaforo.h semaforo.c def.h archivos.c archivos.h funciones.c funciones.h
	$(CC) -o panel panel.c archivos.c clave.c semaforo.c funciones.c $(CFLAGS) $(HEADERS)
	touch panel.txt
	rm panel.txt
	touch panel.txt

clean:
	rm -rf *.o panel equipo
