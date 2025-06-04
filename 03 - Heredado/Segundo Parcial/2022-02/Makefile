CC = gcc 

CFLAGS = -std=gnu89 -pedantic-errors -Wall -Werror -pthread

HEADERS_ROUTE = ./

HEADERS = -I$(HEADERS_ROUTE)

all: arquero pateadores 
 
arquero:
	$(CC) -o arquero arquero.c clave.c colas.c aleatorios.c memoria.c $(CFLAGS) -I$(HEADERS)

pateadores:
	$(CC) -o pateadores pateadores.c funcion_pateador.c clave.c colas.c memoria.c $(CFLAGS) -I$(HEADERS)

clean:
	rm -rf  *.o arquero pateadores

