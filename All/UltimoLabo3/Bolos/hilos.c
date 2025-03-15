#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "time.h"
#include "pthread.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "cola.h"
#include "funciones.h"
#include "hilos.h"

void *hilos(void *parametro) {
    int nro_jugador;
    int id_memoria;
    int puntos;
    char cadena[50];
    int cont;
    int id_cola_mensajes;
    int done;
    int ronda;
    hilo_jugadores *datos_jugadores;
    mensaje msg;

    
    
    tiros = 0;
    done = 0;
    ronda = 0;
    datos_jugadores = (hilo_jugadores*)parametro;
    nro_jugador = datos_jugadores->nro_jugador;
    id_cola_mensajes = datos_jugadores->id_cola_mensajes;
    puntos = datos_jugadores->puntos;
    
    borrar_mensajes(id_cola_mensajes);
/*
    printf("Esperando mensajes del jugador %d\n", nro_jugador);
    printf("Numero msg  %d\n", MSG_JUGADOR);
*/  

    while (done == 0) {
        pthread_mutex_lock(&mutex);	
        usleep(TIEMPO_ESPERA);
        ronda++;
        sprintf(cadena, "%d",ronda);
        enviar_mensaje(id_cola_mensajes, MSG_BOLERA, MSG_JUGADOR + nro_jugador, EVT_TIRO, cadena);
        printf("tiro el jugador %d en la ronda %d\n",nro_jugador,ronda);
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, &msg);
        switch (msg.evento) {
            case EVT_RESULTADO:
                datos_jugadores[nro_jugador].puntos = atoi(msg.mensaje);
                printf("\n");
                sprintf(cadena, "El jugador %d tiene %d puntos", nro_jugador, datos_jugadores[nro_jugador].puntos);
                printf("\n%s\n", cadena);
                
                break;
            case EVT_FIN:
                done = 1;
                datos_jugadores[nro_jugador].puntos = atoi(msg.mensaje);
                sprintf(cadena, "El jugador %d termina con %d puntos", nro_jugador, datos_jugadores[nro_jugador].puntos);
                finalizado++;
                
                printf("\n%s\n", cadena);

                break;
        }
        memset(cadena,0,sizeof(cadena));
        pthread_mutex_unlock(&mutex);
        usleep(TIEMPO_ESPERA);
    }
    if (nro_jugador == 0){ 
        puntaje0 = datos_jugadores[0].puntos;
        /*printf("El jugador 0 tiene %d puntos\n", puntaje0);*/
    }
    if (nro_jugador == 1){
        puntaje1 = datos_jugadores[1].puntos;
        /*printf("El jugador 1 tiene %d puntos\n", puntaje1);*/
    }
    if (nro_jugador == 2){
        puntaje2 = datos_jugadores[2].puntos;
        /*printf("El jugador 2 tiene %d puntos\n", puntaje2);*/
    }
   
    
    
    pthread_exit(NULL);
}
