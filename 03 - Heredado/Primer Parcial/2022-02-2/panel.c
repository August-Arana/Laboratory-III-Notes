#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "definiciones.h"
#include "clave.h"
#include "semaforo.h"

int main(int argc, char *argv[])
{
    char archivo[20];
    char mensaje_anterior[LARGO_MENSAJE] = {0};
    char mensaje[LARGO_MENSAJE] = {0};
    FILE *puntero_archivo;
    int id_semaforo;
    int numero_panel;

    if (argc != 2)
    {
        printf("Por favor especifique el numero de panel por parametro.\n");
        return 0;
    }

    numero_panel = atoi(argv[1]);

    /*nombre del archivo compartido donde se guarda el mensaje*/
    sprintf(archivo, "panel%d.txt", numero_panel);

    puntero_archivo = fopen(archivo, "w");
    /*escribo mensaje inicial en el archivo*/
    sprintf(mensaje, "default");
    fputs(mensaje, puntero_archivo);
    fclose(puntero_archivo);

    id_semaforo = creo_semaforo();

    while (1)
    {
        espera_semaforo(id_semaforo);

        puntero_archivo = fopen(archivo, "r");
        /*leo el archivo*/
        fgets(mensaje, LARGO_MENSAJE, puntero_archivo);
        fclose(puntero_archivo);

        levanta_semaforo(id_semaforo);

        /*comparo con el mensaje anterior*/
        if (strcmp(mensaje_anterior, mensaje))
        {
            /*es diferente, entonces lo muestro*/
            printf("PANEL %d\n", numero_panel);
            printf("%s\n", mensaje);
            sprintf(mensaje_anterior, mensaje);
        }

        usleep(INTERVALO_CHEQUEO * 1000);
    }

    return 0;
}
