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
    int PuntosArg = 0;
    int PuntosJap = 0; 
    int jugadaArg = 0;
    int jugadaJap = 0;
    char mensajePanel[101];
    char *contenido;
    int ronda = 0;

    /*Variables declaradas*/

    id_semaforo = creo_semaforo();
    inicio_semaforo(id_semaforo, VERDE);

    printf("\nBienvenidos a la Final Mundial de Ping Pong\nArgentina vs. Japón\n");

    while ((PuntosArg != 11) && (PuntosJap != 11)) {
        
        espera_semaforo(id_semaforo);
        
        jugadaArg = 0;
        jugadaJap = 0;
        ronda++;
        system("clear");
        if (!inAbrirArchivo("argentina.txt", "r")) {
            printf("Error al abrir archivo de Argentina\n");
            levanta_semaforo(id_semaforo);
            continue;
        }
    

        inContarAciertosLectura("anote", &jugadaArg);
        if (jugadaArg == 1) {
            PuntosArg++;
        }
        voCerrarArchivo();

        if (!inAbrirArchivo("japon.txt", "r")) {
            printf("Error al abrir archivo de Japón\n");
            levanta_semaforo(id_semaforo);
            continue;
        }

        inContarAciertosLectura("anote", &jugadaJap);
        if (jugadaJap == 1) {
            PuntosJap++;
        }
        voCerrarArchivo();

        if (!inAbrirArchivo("panel.txt", "w")) {
            printf("Error al abrir archivo del panel\n");
            levanta_semaforo(id_semaforo);
            continue;
        }
        printf("\n\n\n\n");
        sprintf(mensajePanel,"Partido argentina vs. Japón\nRonda: %d\nResultado entre Argentina y Japón: %d-%d\n",ronda, PuntosArg, PuntosJap);
        inEscribirArchivo(mensajePanel);
        voCerrarArchivo();
         
        
       if (!inAbrirArchivo("panel.txt", "r")) {
            printf("Error al abrir archivo de panel\n");
            levanta_semaforo(id_semaforo);
            continue;
        }
        contenido = inLeerArchivo();
        if (contenido != NULL) {
            printf("%s", contenido);
            free(contenido); 
        }
        voCerrarArchivo();
           
        levanta_semaforo(id_semaforo);
        
        usleep(TIEMPO_ESPERA);
    }

    
    if (inAbrirArchivo("argentina.txt", "w")) {
        inEscribirArchivo("Finalizo");
        voCerrarArchivo();
    }

    if (inAbrirArchivo("japon.txt", "w")) {
        inEscribirArchivo("Finalizo");
        voCerrarArchivo();
    }

    if (PuntosArg > PuntosJap) {
        printf("\nArgentina gana\n");
    } else if (PuntosJap > PuntosArg) {
        printf("\nJapón gana\n");
    } else {
        printf("\nEmpate\n");
    }

    printf("\nCerrando programa...\n");
    return 0;
}
