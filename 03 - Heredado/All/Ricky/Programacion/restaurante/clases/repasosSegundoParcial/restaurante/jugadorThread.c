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


void *jugadorThread(void *parametro){

	int nro_jugador;
	int puntaje;
	int id_memoria;
	char cadena[50];
	int evento;
	int acumulador;
	int *ganador=NULL;
	int id_cola_mensajes;
	char *nombre_pais;
	int done;
	jugador *datos_thread;

	done=0;
	acumulador=0;
	evento=0;
	

	datos_thread=(jugador*) parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread -> id_cola_mensajes;
	nombre_pais = datos_thread -> nombre_pais;
	strcpy(nombre_pais, datos_thread -> nombre_pais);
	puntaje = datos_thread -> puntaje;
	ganador = (int*)datos_thread -> ganador;
	
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);
	
	
	while(done==0)
	{
		pthread_mutex_lock(&mutex);	
				if(*ganador==1)
				{
					printf("\n**************************\n");
					printf("\n Soy %s y perdi el partido",nombre_pais);
					printf("\n**************************");
					done=1;
				}
				else
				{
					evento = inDevolverAleatorio(1,2);
					enviar_mensaje(id_cola_mensajes,MSG_PANEL,MSG_JUGADOR+nro_jugador,evento,"tiro");
					if(evento == EVT_PUNTO)
					{
						printf("\n**************************");
						printf("\n%s metio punto",nombre_pais);
						printf("\n**************************");
						acumulador++;
						
					}
					else
					{
						printf("\n**************************");
						printf("\n%s erro su tiro",nombre_pais);
						printf("\n**************************");
					}
					if(acumulador >= 11)
					{
						printf("\n**************************");
						printf("\ngano %s",nombre_pais);
						printf("\n**************************\n");
						*ganador=1;	
						done=1;
						enviar_mensaje(id_cola_mensajes,MSG_PANEL,MSG_JUGADOR+nro_jugador,EVT_FIN,"finalizar");
						
					}
					evento=0;
					
				}
				pthread_mutex_unlock(&mutex);
				usleep(1000*500);
																					
		
		
	}
	usleep(1000*500);
	pthread_exit((void *)"Listo");
	

}
