CC = gcc 

CFLAGS = -std=gnu89 -pedantic-errors -Wall -Werror -pthread

HEADERS_ROUTE = ./

HEADERS = -I$(HEADERS_ROUTE)

all: circuito autos 
 
circuito:
	$(CC) -o circuito circuito.c clave.c colas.c aleatorios.c $(CFLAGS) -I$(HEADERS)

autos:
	$(CC) -o autos autos.c funcion_auto.c clave.c colas.c aleatorios.c $(CFLAGS) -I$(HEADERS)

clean:
	rm -rf  *.o circuito autos

