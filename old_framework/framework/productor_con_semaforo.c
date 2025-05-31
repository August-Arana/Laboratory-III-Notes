#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforos.h"
#include "archivos.h"

int main(int argc, char *argv[])
{
	int nro_producto=0, nro_partida=0;
	int id_semaforo;
    int productor;
	
	id_semaforo =  creo_semaforo();
	inicia_semaforo(id_semaforo, 1);
	
	while(1)
	{
		espera_semaforo(id_semaforo);
			
			printf("\nPRODUCIMOS-PARTIDA-%04d\n",nro_partida);
            productor = inAbrirArchivo("producto.txt", "a");

			if (productor!=1)
			{
				for (nro_producto=0; nro_producto<10; nro_producto++)
				{
                    inEscribirArchivo("PRODUCTO-%04d",nro_partida);
                    inEscribirArchivo("-%04d\n",nro_producto);
					usleep(2*1000);
				}

                inCerrarArchivo();
				nro_partida++;
				printf("\nESPERAMOS\n");
			}
			else
			{
				perror ("Error al abrir producto.txt");
			}
			
		levanta_semaforo(id_semaforo);
		usleep(2*1000);
	};
	return 0;
}
