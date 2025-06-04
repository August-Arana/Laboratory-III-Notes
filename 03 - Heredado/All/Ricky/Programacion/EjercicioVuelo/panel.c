#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"
#include "string.h"
#include "archivos.h"
#include "semaforo.h"
#include "unistd.h"
#include "time.h"


int main( ){

    int id_semaforo;
    int contador = 0;
    


    id_semaforo = creo_semaforo();
    inicio_semaforo(id_semaforo,VERDE);


    printf("\nBienvenidos al aeropuerto MDQ\n a continuación se listan los vuelos\n");

    while (contador<CANTIDAD)
    {
        espera_semaforo(id_semaforo);
        printf("\nVuelos del dia de hoy\n");

        inAbrirArchivo("vuelos.txt","r");
        inLeerArchivo();
        voCerrarArchivo();
        inAbrirArchivo("vuelos.txt","w");
        voCerrarArchivo();
        contador++;

        if (contador==CANTIDAD){
            inAbrirArchivo("vuelos.txt","a");
            inEscribirArchivo("\nFin de los Vuelos");
            voCerrarArchivo();
            printf("\nNo más vuelos por hoy\n");
        }
    usleep(TIEMPO_ESPERA);
    levanta_semaforo(id_semaforo);
    usleep(TIEMPO_ESPERA);

    }
    printf("\nCerrando programa...\n");
    return 0;
}
