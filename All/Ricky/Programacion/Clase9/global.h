#ifndef _GLOBAL
#define _GLOBAL

extern pthread_mutex_t mutex;


typedef enum{
	EVT_NINGUNO,
	EVT_NUMERO,
	EVT_ACIERTO,
	EVT_NO_ACERTO,
	EVT_FINALIZAR
}Eventos;

typedef enum{
	MSG_NADIE,
	MSG_PIENSO,
	MSG_JUGADOR
}Destinos;


struct tipo_jugador{
	int nro_jugador;
	int id_colamensaje;
	int cant_jugadores;	
};

typedef struct tipo_jugador tjugador;

#endif
