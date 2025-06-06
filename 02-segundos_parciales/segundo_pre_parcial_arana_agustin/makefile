# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3 -pthread
HEADER = -I./
MISC = funciones.c global.c archivos.c clave.c semaforos.c memoria.c cola.c thread.c

# El orden de los factores no altera el producto

all: clean animales pista

animales:
	$(CC) -o animales $(CFLAGS) $(HEADER) $(MISC) 02-animal.c

pista:
	$(CC) -o pista $(CFLAGS) $(HEADER) $(MISC) 01-pista.c
clean:
	rm -f *.o animales pista
