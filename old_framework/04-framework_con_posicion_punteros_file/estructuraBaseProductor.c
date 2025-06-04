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
    /* Declaracion de variables */
    int id_semaforo;
    int tamanio;
    int color;
    char cadena[TAMANO + 1];
    med medicamento;

    /* Semaforo */
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1)
    {
        /* Espera semaforo */
        espera_semaforo(id_semaforo);

        /* Purga inicial de variables */

        memset(&tamanio, 0, sizeof(tamanio));
        memset(&color, 0, sizeof(color));
        memset(cadena, 0x00, sizeof(cadena));

        /* Sprintf para pegar todas las variables */

        // sprintf(cadena,"%02d|%s|%s\n",medicamento.tipo,medicamento.color,medicamento.sistema);

        /* Purga final de variables */

        memset(&tamanio, 0, sizeof(tamanio));
        memset(&color, 0, sizeof(color));
        memset(cadena, 0x00, sizeof(cadena));

        /* Levanto semaforo */
        levanta_semaforo(id_semaforo);
        usleep(1000);
    };
    return 0;
}
