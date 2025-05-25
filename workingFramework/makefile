# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3 -pthread
HEADER = -I./
MISC = funciones.c global.c archivos.c clave.c semaforos.c memoria.c cola.c thread.c

# El orden de los factores no altera el producto

all: clean bingo

bingo:
	$(CC) -o bingo $(CFLAGS) $(HEADER) $(MISC) bingo_threads.c

# banco:
# 	$(CC) -o banco $(CFLAGS) $(HEADER) $(MISC) elBanco.c
# cajero:
# 	$(CC) -o cajero $(CFLAGS) $(HEADER) $(MISC) elCajero.c
clean:
	rm -f *.o bingo
