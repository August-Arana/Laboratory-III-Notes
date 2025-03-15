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
	hilo_pateadores *datos_pateadores;


	
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	i=0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CANTIDAD_PATEADORES);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	datos_pateadores = (hilo_pateadores*)malloc(sizeof(hilo_pateadores) * CANTIDAD_PATEADORES);


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
	
	for (i = 0; i < CANTIDAD_PATEADORES; i++) {
		datos_pateadores[i].id_cola_mensajes = id_cola_mensajes;
    	datos_pateadores[i].nro_pateador = i;
    	pthread_create(&idHilo[i], &atributos, hilos, &datos_pateadores[i]);  
		usleep(500 * 1000);
	}

    for (i = 0; i < CANTIDAD_PATEADORES; i++) {
    	pthread_join(idHilo[i], NULL);
	}

	free (idHilo);
	free (datos_pateadores);
	
	
    return 0;
}
