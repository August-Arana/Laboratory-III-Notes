#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0
#define LARGO 100

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 34

#define TIEMPO_ESPERA 500

#define CANTIDAD 10

#define MSG_JOSE 1
#define MSG_PEPITO 2

#define EVT_MENSAJE 1
#define EVT_FIN 2

#define ESPERA 1

struct tipo_mensajes{
	long dest;
	int rte;
	int evento;
	char mensaje[LARGO];
};

typedef struct tipo_mensajes mensaje;



#endif
