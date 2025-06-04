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
	EVT_CORRO,
	EVT_FIN
}Eventos;

typedef enum{
	MSG_NADIE,
	MSG_CARRERA,
	MSG_PERRO,
    MSG_GATO,
    MSG_CONEJO
}Destinos;


typedef struct {
	int nro_animal;
	int pasos;
    int id_cola_mensajes;
}hilo_animal;


#endif

