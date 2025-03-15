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
	char *nombres[CIUDADES];
	hilo_ciudad *datos_ciudad;


	i=0;
	nombres[0] = "Buenos Aires";
	nombres[1] = "Cordoba";
	nombres[2] = "Rosario";
	nombres[3] = "Mendoza";
	nombres[4] = "Mar del Plata";
	nombres[5] = "La Plata";
	
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CIUDADES);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	datos_ciudad = (hilo_ciudad*)malloc(sizeof(hilo_ciudad) * CIUDADES);


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
	
	for (i = 0; i < CIUDADES; i++) {
		datos_ciudad[i].id_cola_mensajes = id_cola_mensajes;
    	datos_ciudad[i].nro_ciudad = i;
		strcpy(datos_ciudad[i].Nombre, nombres[i]);
    	pthread_create(&idHilo[i], &atributos, hilos, &datos_ciudad[i]);  
	}

    for (i = 0; i < CIUDADES; i++) {
    	pthread_join(idHilo[i], NULL);
		printf("Reportaje %d terminado\n", i);
	}

	free (idHilo);
	free (datos_ciudad);
	
	
    return 0;
}
