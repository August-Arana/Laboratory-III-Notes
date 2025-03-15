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
#include "hormigaThread.h"



int main(int arg,char *argv[]){
	
	/*Declaracion de variables*/
	int *memoria=NULL;
	int id_memoria;
	int i;
	int id_semaforo;
	int cantidad_hilos;
	int id_cola_mensajes;
	pthread_t* idHilo;
	pthread_attr_t atributos;
	hormiga* hormigas; 
	
	/*Inicializacion de variables*/
	memoria = (int*)creoMemoria(sizeof(4), &id_memoria, CLAVE_BASE);
	i=0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	cantidad_hilos = 3;
	
	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*cantidad_hilos);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 
	pthread_mutex_init(&mutex,NULL);
	hormigas = (hormiga*)malloc(sizeof(hormiga) * cantidad_hilos);

	id_semaforo = creo_semaforo();
   	memoria[1] = 0;
   	espera_semaforo(id_semaforo);
   	memoria[1] = 1;
   	levanta_semaforo(id_semaforo);

	/*Compruebo si el proceso pista esta corriendo*/
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
      		usleep(500 * 1000);
   	}
	
	/*Inicializacion de hilos*/
	for(i=0;i<cantidad_hilos;i++){
		
		hormigas[i].nro_hormiga = i;
		hormigas[i].id_cola_mensajes = id_cola_mensajes;
		hormigas[i].pasos_total=0;
		hormigas[i].contador_vueltas=0;
		if(i==0)
		{	printf("\nCreando hormiga reina");
			strcpy(hormigas[i].nombre_hormiga,"hormiga reina");
			hormigas[i].pasos_minimo=3;
			hormigas[i].pasos_maximo=8;
		}
		else if(i==1)
		{
			printf("\nCreando hormiga roja");
			strcpy(hormigas[i].nombre_hormiga,"hormiga roja");
			hormigas[i].pasos_minimo=2;
			hormigas[i].pasos_maximo=7;
		}
		else
		{
			printf("\nCreando hormiga negra");
			strcpy(hormigas[i].nombre_hormiga,"hormiga negra");
			hormigas[i].pasos_minimo=1;
			hormigas[i].pasos_maximo=9;
		}
		usleep(1000*500);	
	}

	
	
	
	for(i=0;i<cantidad_hilos;i++){
		pthread_create(&idHilo[i],&atributos,hormigaThread,&hormigas[i]);	
	}
	
	
	for(i=0;i<cantidad_hilos;i++){
		pthread_join(idHilo[i],NULL);
	}
	
	
   	

	

	return 0;

	

	



}
