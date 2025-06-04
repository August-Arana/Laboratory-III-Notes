#include <stdio.h>
#include "definiciones.h"
#include "semaforo.h"

void leer_panel(int id_semaforo)
{
    int panel;
    char archivo[20];
    char mensaje[LARGO_MENSAJE] = {0};
    FILE *puntero_archivo;

    /*pregunto numero de panel*/
    printf("Ingrese el numero de panel: ");
    scanf("%d", &panel);
    sprintf(archivo, "panel%d.txt", panel);

    espera_semaforo(id_semaforo);

    /*abro el archivo*/
    puntero_archivo = fopen(archivo, "r");
    if (puntero_archivo)
    {
        /*leo el mensaje*/
        fgets(mensaje, LARGO_MENSAJE, puntero_archivo);
        printf("Mensaje actual en el panel %d: %s\n", panel, mensaje);
        fclose(puntero_archivo);
    }
    else
    {
        printf("El panel no existe.\n");
    }

    levanta_semaforo(id_semaforo);
}
