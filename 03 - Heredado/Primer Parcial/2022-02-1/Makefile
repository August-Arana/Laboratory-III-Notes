 	
CC=gcc 
CFLAGS=-std=gnu89 -pedantic-errors -Wall -Werror
DEPS=definiciones.h aleatorios.h clave.h semaforo.h consola.h producto.h

all: super_derivador cajero

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

super_derivador: super_derivador.o aleatorios.o clave.o semaforo.o consola.o
	$(CC) -o super_derivador super_derivador.o aleatorios.o clave.o semaforo.o consola.o $(CFLAGS)

cajero: cajero.o aleatorios.o clave.o semaforo.o
	$(CC) -o cajero cajero.o clave.o semaforo.o aleatorios.o $(CFLAGS)

clean:
	rm -f super_derivador cajero *.o
