#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforos.h"
#include "archivos.h"
#include "define.h"

int main(int argc, char *argv[])
{
	char cadena[LARGO];
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

				while (contador < CANTIDAD_PARTIDA)
				{
                    inLeerArchivo("%s",cadena);
					printf("%s\n", cadena);
					usleep(INTERVALO_PRODUCTO*1000);
					cant_producto++;
                    contador++;
				}
                contador=0;

                inCerrarArchivo();

				printf("\nTERMINAMOS CONSUMIR PRODUCTOS\n");
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
		usleep(INTERVALO_PARTIDA*1000);
	};
	return 0;
}
