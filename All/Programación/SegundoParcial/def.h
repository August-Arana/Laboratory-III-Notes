#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define DESDE 1
#define HASTA 101

#define CANTIDAD 10
#define CANTIDAD_TOTAL 15
#define FINAL 100

/*CLAVES*/
#define CLAVE_BASE 33
#define CLAVE_MAIN 34

#define LARGO 100

#define INTERVALO1 1000
#define INTERVALO2 2000

#define CANT_ANIMALES 3

typedef struct {
	long long_dest;
	int int_rte;
	int int_evento;
	char char_mensaje[50];
}mensaje;

typedef enum{
	EVT_NINGUNO,
	EVT_INICIO,
	EVT_CORRO,
	EVT_FINALIZAR
}Eventos;


typedef enum{
	MSG_NADIE,
	MSG_PISTA,
	MSG_ANIMAL
}Destinos;

#endif 
