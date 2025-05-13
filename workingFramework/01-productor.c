#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "semaforos.h"
#include "archivos.h"
#include "funciones.h"
#include "define.h"

int main(int argc, char *argv[])
{
    /*Declaracion de variables*/
	int id_semaforo;
    int inPostre;
    char cadena[TAMANO+1];
    men menu;

	id_semaforo =  creo_semaforo(CLAVEBASE);
	inicia_semaforo(id_semaforo, VERDE);

	while(1)
	{
        

        /* Espera semaforo */
		espera_semaforo(id_semaforo);
			
        /*Vacio el contenido de variables*/
        inPostre = 0;
        memset( cadena, 0x00, sizeof(cadena)); 

        /* Tipo de menu al azar */

        menu.tipo = inNumeroAleatorio(1,3);
        printf("Seleccion de tipo de menu al azar, el tipo es %01d\n\n", menu.tipo);

        /*solicito si se quiere postre o no*/


        menu.postre = inPostre;


        /*Configuro el precio y el tipo de sistema para el menu*/

        if(menu.tipo == 1){
    
            strcpy(menu.sistema, "A");
            menu.precioTotal = 1000;

        }else if(menu.tipo == 2){

            strcpy(menu.sistema, "B");
            menu.precioTotal = 2000;
        
        }else if(menu.tipo == 3){

            strcpy(menu.sistema, "C");
            menu.precioTotal = 3000;

        }


        /* Modifico el precio total si el menu posee postre */

        if(menu.postre == 1){

            menu.precioTotal = menu.precioTotal + 200;

        }
        

        /* Unifico todas las variables en una unica cadena */

        sprintf(cadena,"%02d|%01d|%04d|%s\n",menu.tipo,menu.postre,menu.precioTotal, menu.sistema);

        /* Abro archivo, imprimo dentro del mismo, lo cierro*/

        inAbrirArchivo("menus.txt", "a");
        inEscribirArchivo("%s",cadena);
        inCerrarArchivo();
			
        printf("\tDesea agregar postre al menu?\n\t\t1 - Si\n\t\t2 - No\n\n\t");
        scanf("%d",&inPostre);

        /* Levanto semaforo de productor */
		levanta_semaforo(id_semaforo);
		usleep(1000);

	};
	return 0;
}
