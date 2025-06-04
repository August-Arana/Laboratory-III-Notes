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
#include "threadCiudad.h"


int main(int arg, char *argc[]){
	
	int nro_jugador;
	int id_cola_mensajes;
	int done;
	int i;
	int cant_ciudades;
	int numero;
	char cadena[50];
	char nombre_ciudad[100];
	mensaje mensaje;
	pthread_t* idHilo;
	pthread_attr_t atributos;
	tciudad* tciudades;
	int id_memoria;
	int *memoria;

	cant_ciudades=6;
	done=0;
	i=0;

	tciudades = (tciudad*) malloc(sizeof(tciudad) * cant_ciudades);
	idHilo = (pthread_t*) malloc(sizeof(pthread_t)*cant_ciudades);
	memoria = (int *) creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
   	*memoria = 0;

	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE);
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	printf("id_cola: %d\n",id_cola_mensajes);

	pthread_mutex_init(&mutex,NULL);		
	
	srand(time(NULL));
	*memoria = 0;
	
	for(i=0;i<cant_ciudades;i++){
		tciudades[i].nro_ciudad = i;
		tciudades[i].id_colamensaje = id_cola_mensajes;
		printf("Ingrese nombre de ciudad: ");
		scanf("%s",nombre_ciudad);
		strcpy(tciudades[i].nombre_ciudad, nombre_ciudad);
		tciudades[i].velocidad_viento=0;
		tciudades[i].temperatura=0;
		tciudades[i].proba_lluvia=0;

	}
	*memoria=1;
	printf("memori: %d\n",*memoria);
	for(i=0;i<cant_ciudades;i++){
		pthread_create (&idHilo[i], &atributos, threadCiudad,&tciudades[i]);
	}

	for(i=0;i<cant_ciudades;i++){
		pthread_join(idHilo[i],NULL);
	}
	shmdt ((char *)memoria);
	shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);	

	return 0;


}
