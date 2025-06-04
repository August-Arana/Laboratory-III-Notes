all : ej2 

ej2 : ej2.c funciones.h funciones.o
	cc -o ej2 ej2.c funciones.o -pthread

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean: 
	rm -rf *o ej2 *~
	
