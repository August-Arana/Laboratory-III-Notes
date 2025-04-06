#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforos.h"
#include "archivos.h"
#include "define.h"

int main(int argc, char *argv[])
{
	char cadena[LARGO];
	int nro_producto=0, nro_partida=0;
	int id_semaforo;
    int productor;
	
	id_semaforo =  creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	
	while(1)
	{
		espera_semaforo(id_semaforo);
			
			printf("\nPRODUCIMOS-PARTIDA-%04d\n",nro_partida);
            productor = inAbrirArchivo("producto.txt", "a");

			if (productor!=1)
			{

				for (nro_producto=0; nro_producto<10; nro_producto++)
				{
                    sprintf(cadena, "PRODUCTO-%04d-%04d\n", nro_partida, nro_producto);
                    inEscribirArchivo("%s",cadena);
					usleep(INTERVALO_PRODUCTO*1000);
				}

                inCerrarArchivo();
				nro_partida++;
				printf("\nTERMINAMOS CREAR PRODUCTOS\n");
				printf("\nESPERAMOS\n");
			}
			else
			{
				perror ("Error al abrir producto.txt");
			}
			
		levanta_semaforo(id_semaforo);
		usleep(INTERVALO_PARTIDA*1000);
	};
	return 0;
}
