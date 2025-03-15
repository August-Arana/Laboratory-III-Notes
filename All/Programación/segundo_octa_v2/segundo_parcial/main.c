#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "def.h"
#include "unistd.h"
#include "time.h"
#include "memoria.h"
#include "sys/shm.h"
#include "sys/time.h"
#include "pthread.h"
#include "tiempos.h"
#include "funciones.h"
#include "global.h"
#include "cola_mensajes.h"

int main(int arg, char *argc[]){

	int id_cola_mensajes;
	int nro_ciudad;
	int cadena[50];
	int cant_ciudades;
	int done;
	int i;
	int cont;
	int cantidad_recibida;
	int listo;
	mensaje mensaje;
	int id_memoria;
	int *memoria;
	int id_semaforo;
	
	memoria = (int *) creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);

	cant_ciudades=6;
	done=0;
	cont=0;
	cantidad_recibida=0;
	listo=0;

	srand(time(NULL));
	

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	printf("Esperando por ciudades");
   	fflush(stdout);
    	while (*memoria == 0) {
		sleep(1);
		printf(".");
		fflush(stdout);
    	}
   	printf("\nInicializando panel\n");

	

	while(done==0){
		printf("memory: %d\n",*memoria);
		
			enviar_mensaje(id_cola_mensajes,MSG_CIUDAD+cont,MSG_PANEL,EVT_INIT,"inicio");
			cont++;
			recibir_mensaje(id_cola_mensajes, MSG_PANEL, &mensaje);
			nro_ciudad = mensaje.rte-MSG_CIUDAD;		

			switch(mensaje.evento){
				case EVT_INFO:
					printf("Recibiendo info de %d\n",nro_ciudad);
					printf("Mensaje: %s\n",mensaje.mensaje);
					if(cont>=cant_ciudades){
						for(i=0;i<cant_ciudades;i++){
							printf("Enviando mensaje final a: %d\n",MSG_CIUDAD+i);
							enviar_mensaje(id_cola_mensajes,MSG_CIUDAD+i,MSG_PANEL,EVT_FINALIZAR,"fin");
						}
						listo=1;
					}
					cantidad_recibida++;	
					if(listo==1){
						done=1;
					}			

					break;
				default:
					printf("\nTablero: %d Evento sin definir\n", nro_ciudad);
				break;
		
			}
		

	};
	

	return 0;

}
