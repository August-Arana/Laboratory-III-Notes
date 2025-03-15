#ifndef _GLOBAL
#define _GLOBAL
#include "pthread.h"

extern pthread_mutex_t mutex;
extern int TotalCaja0;
extern int TotalCaja1;
extern int TotalCaja2;


typedef enum{
	EVT_NINGUNO,
	EVT_INIT,
	EVT_CONSULTA,
	EVT_CAJA,
	EVT_FIN
}Eventos;

typedef enum{
	MSG_NADIE,
	MSG_DERIVADOR,
    MSG_CAJA
}Destinos;


typedef struct{
	int id_cola_mensajes;
	int nro_caja;
	int total;
	
}hilo_caja;

typedef struct{
	char Descripcion[50];
	int precio;
	
}productos;

#endif

