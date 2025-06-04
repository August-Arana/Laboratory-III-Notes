#ifndef _GLOBAL
#define _GLOBAL
#include "pthread.h"
#include "funciones.h"

extern pthread_mutex_t mutex;
extern int tiros;
extern int goles_hilos;
extern int Cantidad_Jugadores = inDevolverNumeroAleatorio(1, 3);


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
	int puntaje;
    int id_cola_mensajes;

}hilo_jugadores;


#endif

