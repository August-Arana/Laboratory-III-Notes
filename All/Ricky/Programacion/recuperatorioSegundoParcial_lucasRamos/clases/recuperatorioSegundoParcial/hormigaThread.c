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

void *hormigaThread(void *parametro){
	/*Declaracion de variables*/
	int nro_hormiga;
	int distancia_generada;
	int id_cola_mensajes;
	char *nombre_hormiga;
	int contador_vueltas;
	int pasos_total;
	int pasos_minimo;
	int pasos_maximo;
	int done;
	char cadena[50];
	hormiga *datos_thread;

	/*Inicializacion de variables*/
	done=0;
	pasos_total=0;
	contador_vueltas=0;

	datos_thread=(hormiga*) parametro;
	nro_hormiga = datos_thread->nro_hormiga;
	id_cola_mensajes = datos_thread -> id_cola_mensajes;
	nombre_hormiga = datos_thread -> nombre_hormiga;
	strcpy(nombre_hormiga, datos_thread -> nombre_hormiga);
	pasos_total = datos_thread -> pasos_total;
	pasos_minimo = datos_thread -> pasos_minimo;
	pasos_maximo = datos_thread -> pasos_maximo;
	contador_vueltas = datos_thread -> contador_vueltas;

	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);
	

	/*Logica hilo/emisor de mensajes*/
	while(done==0){
		pthread_mutex_lock(&mutex);	
				if(pasos_total<141)
				{
					
					distancia_generada=inDevolverAleatorio(pasos_minimo,pasos_maximo);
					pasos_total+= distancia_generada;
					contador_vueltas++;
					printf("\n---------------------------");
					printf("\nCorredor: %s",nombre_hormiga);
					printf("\nPasos recorridos esta vuelta: %d",distancia_generada);
					printf("\nPasos en total: %d",pasos_total);
					printf("\nNumero de vueltas: %d",contador_vueltas);
					printf("\n---------------------------\n");
					sprintf(cadena,"%d",distancia_generada);
					
					enviar_mensaje(id_cola_mensajes,MSG_PISTA,MSG_HORMIGA+nro_hormiga,EVT_RESULTADO,cadena);
					
					distancia_generada=0;
					memset(cadena,0,sizeof(cadena));	
				
				}else
				{	printf("\n-------------------------------------\n");
					printf("\n%s y finalizo la carrera",nombre_hormiga);
					printf("\nNumero de vueltas total: %d",contador_vueltas);
					printf("\n-------------------------------------\n");
					sprintf(cadena,"%d",contador_vueltas);
					
        				enviar_mensaje(id_cola_mensajes,MSG_PISTA,MSG_HORMIGA+nro_hormiga,EVT_FIN,cadena);
				
					memset(cadena,0,sizeof(cadena));
					done=1;

				}
				
				
								
			
		usleep(1000*300);
		pthread_mutex_unlock(&mutex);
		usleep(1000*300);
		
		
	}
	pthread_exit((void *)"Listo");
	

}
