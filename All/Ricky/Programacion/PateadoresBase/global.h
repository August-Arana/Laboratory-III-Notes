#ifndef _GLOBAL
#define _GLOBAL
#include "pthread.h"

extern pthread_mutex_t mutex;
extern int tiros;
extern int goles_hilos;



typedef enum
{
	EVT_NINGUNO, 
	EVT_INT,
	EVT_TIRO, 
	EVT_GOL, 
	EVT_PALO, 
	EVT_TRAVESANO, 
	EVT_FUERA
} Eventos;

typedef enum
{
	MSG_NADIE, 
	MSG_ARQUERO, 
	MSG_PATEADOR 
} Destinos;


typedef struct {
	int nro_pateador;
	int goles;
    int id_cola_mensajes;

}hilo_pateadores;


#endif

