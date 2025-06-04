#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "semaforos.h"
#include "archivos.h"
#include "define.h"

int main(int argc, char *argv[])
{
	int id_semaforo;
    char cadena[TAMANO];
    int tipo;

    char color[COLOR+1];
    char sistema[1+1];

    int esteControlInt;
    char esteControl[1+1];

    int totalMedicamentos;
    int totalPastillas;

    long posicionPunteroFile;

    posicionPunteroFile = 0;

    totalMedicamentos = 0;
    totalPastillas = 0;

	id_semaforo =  creo_semaforo();

    esteControlInt = atoi(argv[1]); 

    if( esteControlInt == 5 ){
        strcpy(esteControl,"A");

    }else if(esteControlInt == 10){
        strcpy(esteControl,"B");

    }else if(esteControlInt == 20){
        strcpy(esteControl,"C");
    }	

printf("Sistema de control para medicamentos tipo %s", esteControl);

	while(1)
	{
	   espera_semaforo(id_semaforo);
            inAbrirArchivo("medicamentos.txt", "r");

            if(posicionPunteroFile != 0){
                inIrAPosicion(posicionPunteroFile);
            }

            if(inLeerLineaPorLinea(cadena,TAMANO) == 0){

                posicionPunteroFile = obtenerPosicionPuntero();

                sscanf(cadena,"%02d|%[^|]|%[^\n]",&tipo, color, sistema);
                if(strcmp(sistema, esteControl) == 0){
                    
                    totalMedicamentos++;
                    totalPastillas = totalPastillas + esteControlInt;        
                    printf("Se han procesado %02d Medicamentos y %03d pastillas\n", totalMedicamentos, totalPastillas);
                }

            }

            inCerrarArchivo();
            levanta_semaforo(id_semaforo);
            usleep(1000);
	};

	return 0;
}
