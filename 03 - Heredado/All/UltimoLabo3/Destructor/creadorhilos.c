#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "sys/shm.h"
#include "unistd.h"
#include "time.h"
#include "pthread.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "cola.h"
#include "funciones.h"
#include "hilos.h"
#include "semaforo.h"


int main(int arc, char *argv[]){
    int *memoria=NULL;
	int id_memoria;
	int i;
	int id_semaforo;
	int id_cola_mensajes;
	pthread_t *idHilo;
	pthread_attr_t atributos;
	hilo_peleadores *datos_peleadores;
	

	srand(time(NULL));
	/*Cantidad_Jugadores = inDevolverNumeroAleatorio(1, 3);*/
	/*printf("Cantidad de jugadores: %d\n",Cantidad_Jugadores);*/
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	i=0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CANTIDAD_JUGADORES);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	datos_peleadores = (hilo_peleadores*)malloc(sizeof(hilo_peleadores) * CANTIDAD_JUGADORES);


	id_semaforo = creo_semaforo();
   	memoria[1] = 0;
   	espera_semaforo(id_semaforo);
   	memoria[1] = 1;
   	levanta_semaforo(id_semaforo);

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[0] == 1)
     	{
         	levanta_semaforo(id_semaforo);
         	break;
     	}
      	else
      	{
         	levanta_semaforo(id_semaforo);
      	}
      		usleep(TIEMPO_ESPERA);
   	}
	
	for (i = 0; i < CANTIDAD_JUGADORES; i++) {
		if (i >= 0 && i < 3) {
			datos_peleadores[i].id_cola_mensajes = id_cola_mensajes;
			datos_peleadores[i].nro_peleador = i;
			datos_peleadores[i].valor_critico = inDevolverNumeroAleatorio(1, 100);
			datos_peleadores[i].tipo = 0;
			
		}
		if (i == 3) {
			datos_peleadores[i].id_cola_mensajes = id_cola_mensajes;
			datos_peleadores[i].nro_peleador = i;
			datos_peleadores[i].valor_critico = inDevolverNumeroAleatorio(1, 1000);
			datos_peleadores[i].tipo = 1;
			
		}
    	pthread_create(&idHilo[i], &atributos, hilos, &datos_peleadores[i]);  
		/*printf("Hilo %d creado\n", i);*/
		usleep(500 * 1000);
	}

    for (i = 0; i < CANTIDAD_JUGADORES; i++) {
    	pthread_join(idHilo[i], NULL);
	}




	
	free (idHilo);
	free (datos_peleadores);
	






	
	
    return 0;
}
