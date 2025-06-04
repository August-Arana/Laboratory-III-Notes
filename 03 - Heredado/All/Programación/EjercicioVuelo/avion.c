#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"
#include "string.h"
#include "archivos.h"
#include "semaforo.h"
#include "unistd.h"
#include "time.h"

int main(int arg, char *argv[]) {
    int id_semaforo;
    char mensajeAvion[100+1];
    int confirmar = 0;
    int i = 0;
    char NombreCiudad[100+1];

    printf("Ya declaré las variables.\n");

    
    if (arg < 2) {
        printf("Error: Se requiere el número de avión como argumento.\n");
        return 1;
    }


    id_semaforo = creo_semaforo();
    if (id_semaforo == -1) {
        printf("Error al crear el semáforo.\n");
        return 1;
    }
    inicio_semaforo(id_semaforo,ROJO);

    while (i != 1) {
        printf("Esperando semáforo...\n");
        espera_semaforo(id_semaforo);
        printf("Semáforo obtenido.\n");

        confirmar++;
        if (confirmar == CANTIDAD+1) {
            printf("\nVuelos Cerrados\n");
            i = 1;
        } else {
       
            if (inAbrirArchivo("vuelos.txt", "a") == -1) {
                printf("Error al abrir el archivo en modo escritura.\n");
                levanta_semaforo(id_semaforo);
                continue;
            }

            printf("\nIngrese Ciudad: ");
            scanf("%100s", NombreCiudad); 
            sprintf(mensajeAvion, "Número de Avion: %s, Origen del Avion: %s\n", argv[1], NombreCiudad);
            inEscribirArchivo(mensajeAvion);
            voCerrarArchivo();
        }

        usleep(TIEMPO_ESPERA);
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA);
    }

    printf("\nSaliendo del programa...\n");
    return 0;
}
