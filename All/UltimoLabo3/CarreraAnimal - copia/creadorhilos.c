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
	hilo_animal *datos_animal;

	vueltasConejo = 0;
	vueltasGato = 0;
	vueltasPerro = 0;
	
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	i=0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CANTIDAD_CORREDORES);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	datos_animal = (hilo_animal*)malloc(sizeof(hilo_animal) * CANTIDAD_CORREDORES);


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
	
	for (i = 0; i < CANTIDAD_CORREDORES; i++) {
		datos_animal[i].id_cola_mensajes = id_cola_mensajes;
    	datos_animal[i].nro_animal = i;
    	pthread_create(&idHilo[i], &atributos, hilos, &datos_animal[i]);  
		usleep(500 * 1000);
	}

    for (i = 0; i < CANTIDAD_CORREDORES; i++) {
    	pthread_join(idHilo[i], NULL);
		printf("Corredor %d terminado\n", i);
	}

	free (idHilo);
	free (datos_animal);
	
	
    return 0;
}
