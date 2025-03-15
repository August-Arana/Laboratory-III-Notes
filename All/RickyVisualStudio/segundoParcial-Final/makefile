#mi makefile

CC = gcc
CFLAGS = -pedantic-errors -O3 -std=gnu89 -Wall -pthread
PHEADER = -I./
MISC1 = main.c funciones.c archivo.c claves.c semaforos.c memoria.c cola.c
MISC2 = main1.c funciones.c archivo.c claves.c semaforos.c memoria.c cola.c hormigaThread.c

all: clean programa1 programa2

programa1: main.c funciones.c archivo.c claves.c semaforos.c memoria.c cola.c funciones.h archivo.h claves.h semaforos.h memoria.h cola.h def.h global.h
	$(CC) -o pistaEjecutable $(MISC1) $(CFLAGS) $(PHEADER)

programa2: main1.c funciones.c archivo.c claves.c semaforos.c memoria.c cola.c hormigaThread.c funciones.h archivo.h claves.h semaforos.h memoria.h cola.h def.h global.h hormigaThread.h
	$(CC) -o hormigaEjecutable $(MISC2) $(CFLAGS) $(PHEADER)
	
clean: 
	rm -rf *.o programa1 programa2
