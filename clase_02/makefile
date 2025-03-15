# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3
HEADER = -I./
MISC = funciones.c global.c main.c

# El orden de los factores no altera el producto
all: clean programa

programa:
	$(CC) -o prog1 $(CFLAGS) $(HEADER) $(MISC) -pthread

clean:
	rm -f *.o prog1
