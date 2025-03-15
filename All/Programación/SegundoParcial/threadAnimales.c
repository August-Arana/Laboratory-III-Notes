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
#include "memcom.h"
#include "cola.h"
#include "funciones.h"
#include "threadAnimales.h"

void *threadAnimales(void *parametro){

	int done=0, id_cola_mensajes, animal;
	int pasos=0, pasos_totales=0;
	char cadena1[50], cadena2[50];
	mensaje msg;
	tanimal *datos_thread;
	int id_memoria;
	banderas *memoria = NULL;

	memoria=(banderas*)voCreo_memoria(sizeof(banderas)*CANTIDAD, &id_memoria, CLAVE_BASE);

	/*STRUCT MENSAJE: desarmo*/
	datos_thread = (tanimal*) parametro;
	animal = datos_thread->nro_animal;
	id_cola_mensajes = datos_thread->id_cola_mensajes;

	pthread_mutex_init(&mutex,NULL);
	srand(time(NULL));

	while(done==0){
		pthread_mutex_lock(&mutex);
		if(memoria[0].fin==1){
			done=1;
		}else{
			inRecibir_mensaje(id_cola_mensajes, MSG_ANIMAL+animal, &msg);
			if(msg.int_evento==EVT_CORRO){
				switch(animal){
				case 0:
					pasos=inDevolverAleatorio(4,11);
					printf("El conejo avanzo %d pasos\n", pasos);
					pasos_totales += pasos;
					break;
				case 1:
					pasos=inDevolverAleatorio(1,12);
					printf("El gato avanzo %d pasos\n", pasos);
					pasos_totales += pasos;
					break;
				case 2:
					pasos=inDevolverAleatorio(3,10);
					printf("El perro avanzo %d pasos\n", pasos);
					pasos_totales += pasos;
					break;
				}
				printf("\n");
				sprintf(cadena1, "%d", pasos);
				sprintf(cadena2, "%d", pasos_totales);
				if(pasos_totales>50){
					inEnviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_ANIMAL+animal, EVT_FINALIZAR, cadena2);
					memoria[0].fin=1;
					if(animal==0){
						printf("Gano el conejo\n");
					}else if(animal==1){
						printf("Gano el gato\n");
					}else{
						printf("Gano el perro\n");
					}
					done=1;
				}else{
					inEnviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_ANIMAL+animal, EVT_CORRO, cadena1);
				}

			}	
		}
		pthread_mutex_unlock(&mutex);
		sleep(4);
	};

	pthread_exit((void*)"Listo");

}
