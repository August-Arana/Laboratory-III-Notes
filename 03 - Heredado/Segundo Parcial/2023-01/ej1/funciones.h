#ifndef _FUNCIONES_H
#define _FUNCIONES_H
 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#define ROJO 0
#define VERDE 

#define CLAVE_BASE 33
#define SEMAFORO0 0

#define LARGO_TMENSAJE 1024


typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long	long_dest; 						//Destinatario
	int 	int_rte;						//Remitente
	int 	int_evento;						//Numero de nevento
	char 	char_mensaje[LARGO_TMENSAJE];	//mensajse
};

key_t 	creo_clave(int r_clave);
int 	creo_id_memoria(int size, int clave);
void* 	creo_memoria(int id_memoria);
int 	creo_semaforo(int cuantos);
void 	inicio_semaforo(int id_semaforo, int cual,int valor);
void 	levanta_semaforo(int id_semaforo,int cual);
void 	espera_semaforo(int id_semaforo,int cual);
int 	creo_id_cola_mensajes(int clave);
int 	borrar_mensajes(int id_cola_mensajes);

#endif

