#include <stdio.h>
#include "definiciones.h"
#include "semaforo.h"

void escribir_panel(int id_semaforo)
{
    int panel;
    char archivo[20];
    char mensaje[LARGO_MENSAJE] = {0};
    FILE *puntero_archivo;

    /*pregunto numero panel*/
    printf("Ingrese el numero de panel: ");
    scanf("%d", &panel);
    sprintf(archivo, "panel%d.txt", panel);

    espera_semaforo(id_semaforo);

    /*abro el archivo*/
    puntero_archivo = fopen(archivo, "r+");
    if (puntero_archivo)
    {
        /*pregunto por el nuevo mensaje*/
        printf("Ingrese el nuevo mensaje: ");
        scanf("%s", mensaje);

        /*escribo el mensaje en el archivo*/
        fputs(mensaje, puntero_archivo);
        fclose(puntero_archivo);
    }
    else
    {
        printf("El panel no existe.\n");
    }

    levanta_semaforo(id_semaforo);
}
