#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "time.h"
#include "unistd.h"

#include "sys/ipc.h"
#include "sys/shm.h"
#include "pthread.h"

#include "def.h"
#include "funciones.h"
#include "archivo.h"
#include "claves.h"
#include "semaforos.h"
#include "memoria.h"
#include "global.h"
#include "cola.h"
#include "meseroThread.h"



int main(int arg,char *argv[]){

	int *memoria=NULL;
	int id_memoria;
	int i;
	int id_semaforo;
	int cantidad_hilos;
	int id_cola_mensajes;
	pthread_t* idHilo;
	pthread_attr_t atributos;
	mesero* meseros; /*Estructura de datos a utilizar*/
	
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	i=0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	cantidad_hilos = 3;
	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*cantidad_hilos);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	meseros = (mesero*)malloc(sizeof(mesero) * cantidad_hilos);

	id_semaforo = creo_semaforo();
   	memoria[1] = 0;
   	espera_semaforo(id_semaforo);
   	memoria[1] = 1;
   	levanta_semaforo(id_semaforo);

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[0] = 1)
     	{
         	levanta_semaforo(id_semaforo);
         	break;
     	}
      	else
      	{
         	levanta_semaforo(id_semaforo);
      	}
      		usleep(500 * 1000);
   	}
	
	/*Inicializacion de hilos*/
	for(i=0;i<cantidad_hilos;i++){
		meseros[i].nro_mesero=i;
		meseros[i].id_cola_mensajes = id_cola_mensajes;
		sleep(1);
		printf("\nCreando mesero n:%d",i+1);	
	}

	
	
	
	for(i=0;i<cantidad_hilos;i++){
		pthread_create(&idHilo[i],&atributos,meseroThread,&meseros[i]);	
	}
	
	
	for(i=0;i<cantidad_hilos;i++){
		pthread_join(idHilo[i],NULL);
	}
	
	
   	

	shmdt ((int *)memoria);
	shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);	

	return 0;

	

	



}
