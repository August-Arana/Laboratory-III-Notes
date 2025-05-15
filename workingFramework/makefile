# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3
HEADER = -I./
MISC = funciones.c global.c archivos.c clave.c semaforos.c memoria.c cola.c

# El orden de los factores no altera el producto

all: clean programa1 programa2

programa2:
	$(CC) -o consumidor $(CFLAGS) $(HEADER) $(MISC) example_01.c -pthread

programa1:
	$(CC) -o productor $(CFLAGS) $(HEADER) $(MISC) example_02.c -pthread

clean:
	rm -f *.o productor consumidor
