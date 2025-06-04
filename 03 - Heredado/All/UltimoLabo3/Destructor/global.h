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
	EVT_VISION,
	EVT_PREPARACION,
	EVT_ATAQUE,  
	EVT_FIN
} Eventos;

typedef enum
{
	MSG_NADIE, 
	MSG_CAMPO, 
	MSG_PELEADOR 
} Destinos;


typedef struct {
	int nro_peleador;
	int valor_critico;
	int vida;
	int tipo;
    int id_cola_mensajes;

}hilo_peleadores;


#endif

