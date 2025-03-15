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

void *hilos(void *parametro){


	int nro_pateador;
	int id_memoria;
	char cadena[50];
	

	int cont;
	int id_cola_mensajes;
	int done;
	hilo_pateadores *datos_pateadores;
    mensaje msg;

    tiros=0;
	done=0;
	datos_pateadores=(hilo_pateadores*) parametro;
	nro_pateador = datos_pateadores->nro_pateador;
	id_cola_mensajes = datos_pateadores -> id_cola_mensajes;
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);


    

    
    pthread_mutex_lock(&mutex);	
    usleep(TIEMPO_ESPERA);
    
    enviar_mensaje(id_cola_mensajes,MSG_ARQUERO,MSG_PATEADOR+nro_pateador,EVT_TIRO,"");
    recibir_mensaje(id_cola_mensajes,MSG_PATEADOR+nro_pateador,&msg);
    switch(msg.evento)
    {
        case EVT_GOL:
            datos_pateadores[nro_pateador].goles++;
            sprintf(cadena,"El Pateador %d hizo Gol",nro_pateador);
            printf("Goooool\n");
            goles_hilos++;
            break;
        case EVT_PALO:
            sprintf(cadena,"El Pateador %d dio en el Palo",nro_pateador);
            printf("Ufff\n");
            break;
        case EVT_TRAVESANO:
            sprintf(cadena,"El Pateador %d dio en el Travesaño",nro_pateador);
            printf("Ufff\n");
            break;
        case EVT_FUERA:
            sprintf(cadena,"El Pateador %d tiró afuera",nro_pateador);
            printf("Ufff\n");
            break;
    }
    
    
        
        	
	pthread_mutex_unlock(&mutex);
	usleep(TIEMPO_ESPERA);
    

    printf("%s\n",cadena);
    printf("Goles totales %d\n",goles_hilos);
    

    pthread_exit(NULL);


}
