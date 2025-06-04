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


	int nro_jugador;
	int id_memoria;
    int puntos;
	char cadena[50];
	

	int cont;
	int id_cola_mensajes;
	int done;
	hilo_jugadores *datos_jugadores;
    mensaje msg;

    tiros=0;
    goles_hilos=0;
	done=0;
	datos_jugadores=(hilo_jugadores*) parametro;
	nro_jugador = datos_jugadores->nro_jugador;
	id_cola_mensajes = datos_jugadores -> id_cola_mensajes;
    puntos = datos_jugadores -> puntos;
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);


    

    recibir_mensaje(id_cola_mensajes,MSG_JUGADOR+nro_jugador,&msg);
    switch (msg.evento)
    {
    case EVT_INICIO:

        while (done==0)
        {
            pthread_mutex_lock(&mutex);	
            usleep(TIEMPO_ESPERA);
            
            enviar_mensaje(id_cola_mensajes,MSG_BOLERA,MSG_JUGADOR+nro_jugador,EVT_TIRO,"");
            recibir_mensaje(id_cola_mensajes,MSG_JUGADOR+nro_jugador,&msg);
            switch(msg.evento)
            {
                case EVT_RESULTADO:
                    datos_jugadores[nro_jugador].puntos=atoi(msg.mensaje);
                    sprintf(cadena,"El jugador %d tiene %d puntos",nro_jugador,datos_jugadores[nro_jugador].puntos);
                    printf( "%s\n",cadena);
                    goles_hilos++;
                    break;
                case EVT_FIN:
                    done=1;
                    datos_jugadores[nro_jugador].puntos=atoi(msg.mensaje);
                    sprintf(cadena,"El jugador %d termina con %d puntos",nro_jugador,datos_jugadores[nro_jugador].puntos);
                    printf("%s\n",cadena);
                    break;
                
            }
        
        
            
                
            pthread_mutex_unlock(&mutex);
            usleep(TIEMPO_ESPERA);
        
    }
        break;
    
    
  
    
   

    

    pthread_exit(NULL);


}
