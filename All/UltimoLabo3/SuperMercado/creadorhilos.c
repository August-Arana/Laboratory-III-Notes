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
	
	hilo_caja *datos_caja;

	i=0;

	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CANTIDAD_CAJAS);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	datos_caja = (hilo_caja*)malloc(sizeof(hilo_caja) * CANTIDAD_CAJAS);


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
	
	for (i = 0; i < CANTIDAD_CAJAS; i++) {
		datos_caja[i].id_cola_mensajes = id_cola_mensajes;
    	datos_caja[i].nro_caja = i;
		datos_caja[i].total = 0;
		
    	pthread_create(&idHilo[i], &atributos, hilos, &datos_caja[i]);  
	}

    for (i = 0; i < CANTIDAD_CAJAS; i++) {
    	pthread_join(idHilo[i], NULL);
		printf("Caja %d cerrada\n", i);
	}

	free (idHilo);
	free (datos_caja);
	
	
    return 0;
}
