CC = gcc 

CFLAGS = -std=gnu89 -pedantic-errors -Wall -Werror

HEADERS_ROUTE = ./

HEADERS = -I$(HEADERS_ROUTE)

all: cci panel 
 
cci:
	$(CC) -o cci cci.c clave.c semaforo.c leer_panel.c escribir_panel.c consola.c $(CFLAGS) -I$(HEADERS)

panel:
	$(CC) -o panel panel.c clave.c semaforo.c $(CFLAGS) -I$(HEADERS)

clean:
	rm -rf  *.o cci panel

