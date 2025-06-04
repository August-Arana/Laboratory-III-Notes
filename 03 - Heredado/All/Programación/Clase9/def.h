#ifndef _DEF
#define _DEF

#define TRUE          1
#define FALSE         0
#define ROJO          0
#define VERDE         1
#define CANTIDAD      5
#define DESDE         0
#define HASTA         25

#define CLAVE_BASE    33
#define LARGO_MENSAJE 100

#define MSG_NADIE     0
#define MSG_PIENSO    1
#define MSG_JUGADOR   2


#define EVT_NINGUNO   0
#define EVT_NUMERO    1
#define EVT_ACERTO    2
#define EVT_NO_ACERTO 3
#define EVT_FIN       4

#define ESPERA        1

struct tipo_mensajes{
	long dest;
	int rte;
	int evento;
	char mensaje[LARGO_MENSAJE];
};

typedef struct tipo_mensajes mensaje;

struct tipo_dato{
	int numero;
	char letra;
};

typedef struct tipo_dato dato;

struct timeval 	t_inicio;
struct timeval 	t_final;



#endif
