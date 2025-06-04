#ifndef _GLOBAL
#define _GLOBAL
#include "pthread.h"

extern pthread_mutex_t mutex;
extern int vueltasPerro;
extern int vueltasGato;	
extern int vueltasConejo;
extern int carrerafinal;


typedef enum{
	EVT_NINGUNO,
	EVT_INIT,
	EVT_INFO,
	EVT_FIN
}Eventos;

typedef enum{
	MSG_NADIE,
	MSG_NOTICIERO,
    MSG_CIUDADES
}Destinos;


typedef struct{
	int id_cola_mensajes;
	int nro_ciudad;
	char Nombre[100];
	int viento;
	int temperatura; 
	int lluvia;
}hilo_ciudad;


#endif

