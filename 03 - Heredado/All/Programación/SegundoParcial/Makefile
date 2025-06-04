CC=gcc-4.1

CFLAGS= -Wall -O3 -std=gnu89 -pedantic-errors -lpthread
HEADERS= -I./
ARCHIVOS= clave.c memcom.c cola.c funciones.c threadAnimales.c

all : clean programa1 programa2

programa1 : animales.c def.h clave.h global.h clave.c memcom.c memcom.h cola.c cola.h funciones.c funciones.h threadAnimales.c threadAnimales.h
	$(CC) -o program1 animales.c $(ARCHIVOS) $(CFLAGS) $(HEADERS)

programa2 : pista.c def.h clave.h global.h clave.c memcom.c memcom.h cola.c cola.h threadAnimales.c threadAnimales.h funciones.c funciones.h
	$(CC) -o program2 pista.c $(ARCHIVOS) $(CFLAGS) $(HEADERS)

clean : 
	rm -rf *o programa1 programa2
