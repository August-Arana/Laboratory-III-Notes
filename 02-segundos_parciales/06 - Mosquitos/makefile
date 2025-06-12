# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3 -pthread
HEADER = -I./
MISC = funciones.c global.c archivos.c clave.c semaforos.c memoria.c cola.c thread.c

# El orden de los factores no altera el producto

all: clean espiral mosquitos

mosquitos:
	$(CC) -o mosquitos $(CFLAGS) $(HEADER) $(MISC) 02-mosquitos.c

espiral:
	$(CC) -o espiral $(CFLAGS) $(HEADER) $(MISC) 01-espiral.c
clean:
	rm -f *.o espiral mosquitos
