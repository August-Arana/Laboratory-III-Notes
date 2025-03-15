CC=gcc-4.1

CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors 
HEADERS = -I./
all : clean programa

programa: main.c def.h funciones.h archivos.h clave.h
	$(CC) -o programa main.c funciones.c archivos.c clave.c $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o programa