CC 		= g++ 

all : verificador solicitante 


verificador : verificador.c funciones.h definiciones.h funciones.o
	cc -o verificador verificador.c funciones.o

solicitante : solicitante.c funciones.h definiciones.h funciones.o
	cc -o solicitante solicitante.c funciones.o

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean: 
	rm -rf *o verificador solicitante *~
	
