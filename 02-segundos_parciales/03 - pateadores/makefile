# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3 -pthread
HEADER = -I./
MISC = funciones.c global.c archivos.c clave.c semaforos.c memoria.c cola.c thread.c

# El orden de los factores no altera el producto

all: clean cajeros derivador

cajeros:
	$(CC) -o cajeros $(CFLAGS) $(HEADER) $(MISC) 02-clientes.c

derivador:
	$(CC) -o derivador $(CFLAGS) $(HEADER) $(MISC) 01-supermercado.c
clean:
	rm -f *.o cajeros derivador
