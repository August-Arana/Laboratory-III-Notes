#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "semaforos.h"
#include "archivos.h"
#include "define.h"

int main(int argc, char *argv[])
{
    /* Declaracion de variables */
	int id_semaforo;
    char cadena[TAMANO+1];
    int tipo;
    int precioTotal;
    char sistema[1+1];
    int totalMenus;
    long posicionPunteroFile;
    char esteControl[1+1];
    int postre;


    posicionPunteroFile = 0;
    totalMenus = 0;
    tipo = 0;
    postre = 0;

    strcpy(esteControl,argv[1]);

    printf("------------------");
    printf("\nInicio Sistema de control para menues tipo %s\n\n", esteControl);
    printf("------------------");


	id_semaforo = creo_semaforo();


	while(1)
	{
	   espera_semaforo(id_semaforo);
            inAbrirArchivo("menus.txt", "r");

            if(posicionPunteroFile != 0){
                inIrAPosicion(posicionPunteroFile);
            }

            /* Vacio la cadena utilizada */
            memset( cadena, 0x00, sizeof(cadena)); 

            if(inLeerLineaPorLinea(cadena,TAMANO) == 0){

                posicionPunteroFile = obtenerPosicionPuntero();

                sscanf(cadena,"%02d|%01d|%04d|%[^\n]",&tipo, &postre, &precioTotal, sistema);
                if(strcmp(sistema, esteControl) == 0){
                    
                    totalMenus++;
                    printf("\n\nSe han procesado %02d Menus tipo %01d\n", totalMenus, tipo);
                    
                    printf("El precio total del ultimo menu fue de %04d pesos", precioTotal);
                    
                    if(postre == 1){

                        printf(" y el mismo tenia postre incluido\n");

                    }else{

                        printf(" Y el mismo no tenia postre incluido\n");

                    }
                    
                }

            }

            inCerrarArchivo();
            levanta_semaforo(id_semaforo);
            usleep(100);
	};

	return 0;
}
