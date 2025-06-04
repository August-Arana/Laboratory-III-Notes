#ifndef _GLOBAL
#define _GLOBAL
#include "pthread.h"
#include "funciones.h"

extern pthread_mutex_t mutex;
extern int tiros;
extern int finalizado;
extern int puntaje0;
extern int puntaje1;
extern int puntaje2;
extern int Cantidad_Jugadores;


typedef enum
{
	EVT_NINGUNO, 
	EVT_INICIO,
	EVT_TIRO, 
	EVT_RESULTADO, 
	EVT_FIN
} Eventos;

typedef enum
{
	MSG_NADIE, 
	MSG_BOLERA, 
	MSG_JUGADOR 
} Destinos;


typedef struct {
	int nro_jugador;
	int puntos;
    int id_cola_mensajes;

}hilo_jugadores;


#endif

