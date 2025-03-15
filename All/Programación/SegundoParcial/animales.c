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
#include "memcom.h"
#include "cola.h"
#include "funciones.h"
#include "threadAnimales.h"

int main(int arc, char *argv[]){

	int id_cola_mensajes, i;
	pthread_t* idHilo;
	tanimal *datos_thread;
	pthread_attr_t atributos;
	int id_memoria;
	banderas *memoria = NULL;

	memoria=(banderas*)voCreo_memoria(sizeof(banderas)*CANTIDAD, &id_memoria, CLAVE_BASE);
	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*CANT_ANIMALES);
	datos_thread = (tanimal*) malloc(sizeof(tanimal)*CANT_ANIMALES);

	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE);
	
	id_cola_mensajes = inCreo_id_cola_mensajes(CLAVE_BASE);
	inBorrar_mensajes(id_cola_mensajes);

	memoria[0].fin=0;
	memoria[0].flag2=1;
	while(memoria[0].flag1==0){
		sleep(1);
	}

	/*CREo CANTIDAD DE HILOS INGRESADA*/
	for(i=0;i<CANT_ANIMALES;i++){
		datos_thread[i].nro_animal = i;
		datos_thread[i].id_cola_mensajes = id_cola_mensajes;	

		pthread_create(&idHilo[i], &atributos, threadAnimales, &datos_thread[i]);

	}

	/*FINALIZAN HILOS*/
	for(i=0;i<CANT_ANIMALES;i++){
		pthread_join(idHilo[i],NULL);
		printf("Termino hilo %d\n", i+1);
	}


	/*LIBERO MEMORIA DINAMICA*/
	free(idHilo);
	free(datos_thread);

	voLiberar_memoria(&memoria,id_memoria);	

	return 0;

}




