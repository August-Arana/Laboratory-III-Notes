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
    int confirmar = 0;
    int i = 0;
    int caja = 0;
    char *contenido = NULL; 
    char cajero[100 + 1];
    char *compra = NULL;  
   

    if (arg < 2) {
        printf("Error: Se requiere el numero de caja como argumento.\n");
        return 1;
    }
    caja = atoi(argv[1]);
    sprintf(cajero, "Caja: %d\n", caja);

    id_semaforo = creo_semaforo();
    if (id_semaforo == -1) {
        printf("Error al crear el semáforo.\n");
        return 1;
    }
    srand(time(NULL));
    inicio_semaforo(id_semaforo, ROJO);

    while (confirmar != 1) {

        espera_semaforo(id_semaforo);
        if (i != 0) {
            inAbrirArchivo("caja.txt", "r");
            inContarAciertosLectura("Cerro", &confirmar);
            voCerrarArchivo();
        }

        if (confirmar == 1) {
            printf("\nCaja Cerrada \n");
        } else {
            if (inAbrirArchivo("caja.txt", "r") == -1) {
                printf("Error al abrir el archivo en modo lectura.\n");
                levanta_semaforo(id_semaforo);
                continue;
            }

            contenido = inLeerArchivoPrimeraLinea(60);
            printf("\nContenido:%s-\n",contenido);
            printf("\ncajero:%s-\n",cajero);
            if (contenido != NULL) {  
                if (strcmp(contenido, cajero) == 0) {
                    printf("Cajero: %s\n", contenido);
                    compra = inLeerArchivo();
                    if (compra != NULL) {
                        printf("%s", compra);
                        free(compra);  
                    }
                } else {
                    printf("Caja libre.\n");
                }
                free(contenido);  
            } else {
                printf("abriendo cajas\n");
            }

            voCerrarArchivo();
            i++;
        }

        usleep(TIEMPO_ESPERA);
        levanta_semaforo(id_semaforo);
        usleep(TIEMPO_ESPERA);
    }

    printf("\nCerrando Super\n");
    printf("\nSaliendo del programa...\n");
    return 0;
}
