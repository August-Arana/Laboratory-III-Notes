# En realidad tendria que ser CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3
HEADER = -I./
MISCP = funciones.c global.c productor_con_semaforo.c archivos.c clave.c semaforos.c
MISCC = funciones.c global.c consumidor_con_semaforo.c archivos.c clave.c semaforos.c

# El orden de los factores no altera el producto
all: clean programa

# OJO TENDRIAS QUE HABER USADO DOS REGLAS!!!!
programa:
	$(CC) -o consumido $(CFLAGS) $(HEADER) $(MISCC) -pthread
	$(CC) -o productor $(CFLAGS) $(HEADER) $(MISCP) -pthread

clean:
	rm -f *.o productor consumido
