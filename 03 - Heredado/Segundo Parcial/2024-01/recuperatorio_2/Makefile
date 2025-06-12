CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I./

all: clean cancha jugadores

%.o: %.c
	$(CC) -g -c $(CFLAGS) $(PHEADER) $< -o $@

cancha: colas.o claves_ipc.o semaforos.o memoria.o aleatorios.o utils.o cancha.o
	$(CC) -o $@ $^

jugadores: colas.o claves_ipc.o semaforos.o memoria.o aleatorios.o utils.o thread.o jugadores.o
	$(CC) -o $@ $^

clean:
	rm -f *.o jugadores cancha *.dat
