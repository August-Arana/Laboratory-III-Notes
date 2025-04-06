#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforos.h"
#include "archivos.h"

int main(int argc, char *argv[])
{
	char cadena[80];
    /*De nuevo, ojo con el memset de cadena*/
	int cant_producto=0;
	int id_semaforo;
    int consumidor;
    int contador;
    contador = 0;
	id_semaforo =  creo_semaforo();
	
	while(1)
	{
		espera_semaforo(id_semaforo);
			
            consumidor = inAbrirArchivo("producto.txt", "r");
			if (consumidor!=1)
			{
				printf("\nCONSUMIMOS\n");
				while (contador < 10)
				{
                    inLeerArchivo("PRODUCTO-%04d-%04d\n",cadena);
					printf("%s\n", cadena);
					usleep(2*1000);
					cant_producto++;
                    contador++;
				}
                inCerrarArchivo();
				if(cant_producto>0)
				{
					printf("\nBORRAMOS\n");
                    /*ojo con el remove, es una llamada a linux, no es C verdadero.*/
					remove("producto.txt");
					cant_producto=0;
				}
			}
			else
				perror ("Error al abrir producto.txt");
			printf("\nESPERAMOS\n");
						
            /*Ojo con cadena, no se esta limpiando y esto es un error*/
		levanta_semaforo(id_semaforo);
		usleep(2*1000);
	};
	return 0;
}
