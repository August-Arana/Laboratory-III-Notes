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
    int vida;
    int tipo;
    char cadena[50];
    char pulgar[50];
    int cont;
    int ataque;
    int id_cola_mensajes;
    int done;
    
    hilo_peleadores *datos_peleadores;
    mensaje msg;

    
    
    memset(pulgar,0,sizeof(pulgar));
    done = 0;
    cont = 0;
    ataque = 0;
    
    datos_peleadores = (hilo_peleadores*)parametro;
    nro_peleador = datos_peleadores->nro_peleador;
    id_cola_mensajes = datos_peleadores->id_cola_mensajes;
    vida = datos_peleadores->vida;
    tipo = datos_peleadores->tipo;
    
    borrar_mensajes(id_cola_mensajes);
/*
    printf("Esperando mensajes del jugador %d\n", nro_jugador);
    printf("Numero msg  %d\n", MSG_JUGADOR);
*/   
    sprintf(cadena,"%d",vida);
    enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_INICIO,cadena);
    while (done == 0) {
        pthread_mutex_lock(&mutex);	
        if (cont==0) {
            printf("Preparando jugador %d\n", nro_peleador);
        }
        if (cont>25) {
            enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_VISION,cadena);
            printf("Visualizando Campo..... \n ");
            recibir_mensaje(id_cola_mensajes,MSG_PELEADOR+nro_peleador,&msg);
            switch (msg.evento) {
                case EVT_PREPARACION:
                    if (nro_peleador>=0 && nro_peleador<=6) {
                        ataque= inDevolverNumeroAleatorio(1, 5);
                        printf("\n\n-----Ataque-----\n\n");
                        printf("Se prepara para atacar jugador %d\n", nro_peleador);    
                        printf("Ataque: %d\n",ataque);
                        printf("\n---Fin de ataque---\n");
                        sprintf(cadena,"%d",ataque);
                        enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_ATAQUE,cadena);
                        
                    }
                    if (nro_peleador == 7) {
                        printf("\n\n-----Ataque de Maximo-----\n\n");
                        printf("Se prepara para atacar jugador %d\n", nro_peleador);
                        ataque= inDevolverNumeroAleatorio(40, 70);
                        printf("Ataque: %d\n",ataque);
                        printf("\n---Fin de ataque---\n");
                        sprintf(cadena,"%d",ataque);
                        enviar_mensaje(id_cola_mensajes,MSG_CAMPO,MSG_PELEADOR+nro_peleador,EVT_ATAQUE,cadena);
                    }
                    


                break;
                case EVT_FIN:
                    strcpy(pulgar,msg.mensaje);
                    printf("%s",pulgar);
                    printf("Fuera de combate\n");
                    memset(pulgar,0,sizeof(pulgar));
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
