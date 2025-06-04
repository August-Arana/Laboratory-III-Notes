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
    char mensajeJapon[100+1];
    char mensajeArgentina[100+1];
    int PuntosArg = 0;
    int confirmar = 0;
    int PuntosJap = 0;
    int jugadaArg = 0;
    int jugadaJap = 0;
    int i = 0;
    int equipo = 0;
    char *contenido;
    /*Variables declaradas*/

    
    if (arg < 2) {
        printf("Error: Se requiere el numero de equipo como argumento.\n");
        return 1;
    }
    equipo=atoi(argv[1]);
    

    id_semaforo = creo_semaforo();
    if (id_semaforo == -1) {
        printf("Error al crear el semáforo.\n");
        return 1;
    }
    srand(time(NULL));
    inicio_semaforo(id_semaforo,ROJO);

    while (PuntosArg!= 11 && PuntosJap!= 11 && i!=1) {
        
        espera_semaforo(id_semaforo);
    
        if (equipo==1) {
            if(PuntosArg!=0){
                inAbrirArchivo("argentina.txt","r");
                inContarAciertosLectura("Finalizo",&confirmar);
                voCerrarArchivo();
            }
            if (confirmar == 1) {
                printf("\nPartido terminado\n");
                i = 1;
            } 
            else{
                if (inAbrirArchivo("argentina.txt", "w") == -1) {
                    printf("Error al abrir el archivo en modo escritura.\n");
                    levanta_semaforo(id_semaforo);
                    continue;
                }

                jugadaArg=inDevolverNumeroAleatorio(1,2);
                if (jugadaArg == 1 ) {
                    printf("\nJugada de Argentina\n");
                    PuntosArg++;
                    sprintf(mensajeArgentina,"anote");
                    printf(mensajeArgentina);
                    inEscribirArchivo(mensajeArgentina);
                    voCerrarArchivo();
                } 
                if (jugadaArg == 2) {
                    printf("\nJugada de Argentina\n");
                    sprintf(mensajeArgentina,"erre");
                    printf(mensajeArgentina);
                    inEscribirArchivo(mensajeArgentina);
                    voCerrarArchivo();
                 }
            }
        }
        if (equipo==2) {
            if(PuntosJap!=0){
                inAbrirArchivo("japon.txt","r");
                inContarAciertosLectura("Finalizo",&confirmar);
                voCerrarArchivo(); 
            }
            
            if (confirmar == 1) {
                printf("\nPartido terminado\n");
                i = 1;
            } 
            else {
                if (inAbrirArchivo("japon.txt", "w") == -1) {
                    printf("Error al abrir el archivo en modo escritura.\n");
                    levanta_semaforo(id_semaforo);
                    continue;
                }
                jugadaJap=inDevolverNumeroAleatorio(1,2);
                if (jugadaJap == 1 ) {
                    printf("\nJugada de Japon\n");
                    PuntosJap++;
                    sprintf(mensajeJapon,"anote");
                    printf(mensajeJapon);
                    inEscribirArchivo(mensajeJapon);
                    voCerrarArchivo();
                    } 
                    if (jugadaJap == 2) {
                        printf("\nJugada de Japon\n");
                        sprintf(mensajeJapon,"erre");
                        printf(mensajeJapon);
                        inEscribirArchivo(mensajeJapon);
                        voCerrarArchivo();
                    }
                }

            
            }
            
            if(i==1){
                if(inAbrirArchivo("ganador.txt","r") == -1){
                    printf("Error al abrir el archivo en modo lectura.\n");
                }            
                contenido = inLeerArchivo();
                voCerrarArchivo();
            }
            usleep(TIEMPO_ESPERA);
            levanta_semaforo(id_semaforo);
            
            usleep(TIEMPO_ESPERA);
        }

    printf("\nGGWP\n");

    printf("\nSaliendo del programa...\n");
    return 0;
}
