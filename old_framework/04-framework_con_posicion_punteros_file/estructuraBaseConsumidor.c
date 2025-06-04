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

    /* puntero de un file */
    long posicionPunteroFile;
    posicionPunteroFile = 0;

    id_semaforo = creo_semaforo();

    /* para obtener argumentos*/
    /*  esteControlInt = atoi(argv[1]);  */

    while (1)
    {

        /* Espera semaforo */
        espera_semaforo(id_semaforo);
        inAbrirArchivo("medicamentos.txt", "r");

        /* Purga inicial de variables */

        //memset(&tamanio, 0, sizeof(tamanio));
        //memset(&color, 0, sizeof(color));
        //memset(cadena, 0x00, sizeof(cadena));


        /* ir a posicion */

        if (posicionPunteroFile != 0)
        {
            inIrAPosicion(posicionPunteroFile);
        }

        /*

        if(inLeerLineaPorLinea(cadena,TAMANO) == 0){

            posicionPunteroFile = obtenerPosicionPuntero();

            sscanf(cadena,"%02d|%[^|]|%[^\n]",&tipo, color, sistema);
            if(strcmp(sistema, esteControl) == 0){

                totalMedicamentos++;
                totalPastillas = totalPastillas + esteControlInt;
                printf("Se han procesado %02d Medicamentos y %03d pastillas\n", totalMedicamentos, totalPastillas);
            }

        }

        */

        /* cerrar archivo */

        inCerrarArchivo();

        /* Purga final de variables */

        // memset(&tamanio, 0, sizeof(tamanio));
        // memset(&color, 0, sizeof(color));
        // memset(cadena, 0x00, sizeof(cadena));

        /* Levanto semaforo */
        levanta_semaforo(id_semaforo);
        usleep(1000);
    };

    return 0;
}
