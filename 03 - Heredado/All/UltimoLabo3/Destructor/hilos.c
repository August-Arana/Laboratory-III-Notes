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
    int nro_peleador;
    int id_memoria;
    int valor_critico;
    int tipo;
    char cadena[50];
    int cont;
    int ataque;
    int id_cola_mensajes;
    int done;
    
    hilo_peleadores *datos_peleadores;
    mensaje msg;

    
    

    done = 0;
    cont = 0;
    ataque = 0;
    
    datos_peleadores = (hilo_peleadores*)parametro;
    nro_peleador = datos_peleadores->nro_peleador;
    id_cola_mensajes = datos_peleadores->id_cola_mensajes;
    valor_critico = datos_peleadores->valor_critico;
    tipo = datos_peleadores->tipo;
    
    borrar_mensajes(id_cola_mensajes);
/*
    printf("Esperando mensajes del jugador %d\n", nro_jugador);
    printf("Numero msg  %d\n", MSG_JUGADOR);
*/   
    sprintf(cadena,"%d",valor_critico);
    enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_INICIO,cadena);
    while (done == 0) {
        pthread_mutex_lock(&mutex);	
        if (cont==0) {
            printf("Preparando jugador %d\n", nro_peleador);
        }
        if (cont>20) {
            enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_VISION,cadena);
            printf("Visualizando Campo..... \n ");
            recibir_mensaje(id_cola_mensajes,MSG_PELEADOR+nro_peleador,&msg);
            switch (msg.evento) {
                case EVT_PREPARACION:
                    if (nro_peleador>=0 && nro_peleador<=2) {
                        ataque= inDevolverNumeroAleatorio(1, 1000);
                        printf("\n\n-----Ataque de Guerro-----\n\n");
                        printf("Se prepara para atacar jugador %d\n", nro_peleador);    
                        printf("Ataque: %d\n",ataque);
                        printf("\n---Fin de ataque---\n");
                        sprintf(cadena,"%d",ataque);
                        enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_ATAQUE,cadena);
                        
                    }
                    if (nro_peleador == 3) {
                        printf("\n\n-----Ataque de Destructor-----\n\n");
                        printf("Se prepara para atacar jugador %d\n", nro_peleador);
                        ataque= inDevolverNumeroAleatorio(1, 100);
                        printf("Ataque: %d\n",ataque);
                        printf("\n---Fin de ataque---\n");
                        sprintf(cadena,"%d",ataque);
                        enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_ATAQUE,cadena);
                    }
                    


                break;
                case EVT_FIN:
                    printf("Fuera de combate\n");
                    done = 1;
                break;

            }
            
        }
        
        cont++;
        
        memset(cadena,0,sizeof(cadena));
        pthread_mutex_unlock(&mutex);
        usleep(TIEMPO_ATAQUE);
    }
    
    
    
    pthread_exit(NULL);
}
