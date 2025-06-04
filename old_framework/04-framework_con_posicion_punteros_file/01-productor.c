#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"
#include "define.h"

int main(int argc, char *argv[])
{
    /*Declaracion de variables*/
	int id_semaforo;
    int tamanio;
    int color;
    char cadena[TAMANO+1];
    med medicamento;

	id_semaforo =  creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	

	while(1)
	{
        
		espera_semaforo(id_semaforo);
			
        /*Vacio el contenido de variables*/

        memset( &tamanio, 0, sizeof(tamanio) );
        memset( &color, 0, sizeof(color) );
        memset( cadena, 0x00, sizeof(cadena));

        /* Tipo de medicamento al azar */

        medicamento.tipo = inNumeroAleatorio(1,3);

        /* Color de Capsula */

        color = inNumeroAleatorio(1,3);

        if(color == 1){

            strcpy(medicamento.color,"Rojo"); 

        }else if(color == 2){
             
            strcpy(medicamento.color,"Amarillo"); 

        }else if (color ==3){
            
            strcpy(medicamento.color,"Fucsia"); 

        }

        /*solicito tamanio de lote*/

        printf("\nIngrese cantidad de pastillas a fabricar\n");
        scanf("%d",&tamanio);

        if(tamanio == 5){

            strcpy(medicamento.sistema,"A"); 

        }else if(tamanio == 10){

            strcpy(medicamento.sistema,"B"); 
        
        }else if(tamanio == 20){

            strcpy(medicamento.sistema,"C"); 

        }

        sprintf(cadena,"%02d|%s|%s\n",medicamento.tipo,medicamento.color,medicamento.sistema);

        printf("Abrir archivo\n");
        inAbrirArchivo("medicamentos.txt", "a");
        inEscribirArchivo("%s",cadena);

        printf("Cerrar archivo\n");
        inCerrarArchivo();
			
        printf("antes semaforo productor\n");
		levanta_semaforo(id_semaforo);
		usleep(1000);
        printf("despues semaforo productor\n");
	};
	return 0;
}
