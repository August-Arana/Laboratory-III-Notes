#include "pthread.h"
#ifndef _DEF
#define _DEF

pthread_mutex_t mutex;
#define CANTIDADALEATORIOS 10
#define TRUE 1
#define FALSE 0
#define CANTIDAD 10
#define DESDE 0
#define HASTA 25
#define CLAVE_BASE 33

#include "pthread.h"

typedef enum{

	EVT_NULO,
	EVT_CORRO,
	EVT_RESULTADO,
	EVT_FIN


}Eventos;

typedef enum{
	MSG_NULO,
	MSG_PISTA,
	MSG_HORMIGA

}Destinatarios;


struct tipo_mensajes{
	long dest;
	int rte;
	int evento;
	char mensaje[100];
};

typedef struct tipo_mensajes mensaje;

typedef struct {

	int nro_hormiga;
	int id_cola_mensajes;
	int pasos_minimo;
	int pasos_maximo;
	int pasos_total;
	int contador_vueltas;
	char nombre_hormiga[50];
	
	

}hormiga;



#endif
