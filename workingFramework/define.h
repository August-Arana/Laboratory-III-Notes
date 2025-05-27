#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33
#define CLAVEBASE2 34
#define ROJO 0
#define VERDE 1
#define TAMANO 30
#define ITERACIONES 5

/* __________ Ejercicio de banco __________ */
#define MSG_BANCO 11
#define MSG_CAJERO 12
#define EVT_MENSAJE 13
#define INTERVALO 5
#define CANTIDAD_CLIENTES 100

/* Por ahora lo defino sin struct */
#define EVT_NINGUNO 0
#define EVT_CONSULTA_SALDO 1
#define EVT_DEPOSITO 2
#define EVT_EXTRACCION 3
#define EVT_RTA_SALDO 4
#define EVT_RTA_SALDO_NOK 5
#define EVT_RTA_DEPOSITO_OK 6
#define EVT_RTA_DEPOSITO_NOK 7
#define EVT_RTA_EXTRACCION_OK 8
#define EVT_RTA_EXTRACCION_NOK 9
#define EVT_FIN 10
/* Por ahora lo defino sin struct */

typedef struct cliente {
  int id_cliente;
  int saldo;
} clt;

/* __________ Ejercicio de bingo __________ */

#define CANT_CARTON 		5
#define BOLILLA_DESDE 		1
#define BOLILLA_HASTA 		99
#define TIEMPO_COMPRUEBA	10
#define TIEMPO_BOLILLAS		500

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int 	nro_jugador;	
	int*	bolillas;						
	int  	cantidad_aciertos;
	
};

/* _________ Ejercicio adivinador _________ */

#define ADIVINADO_DESDE 	1
#define ADIVINADO_HASTA 	99

typedef struct tipo_adivinante
{
	int 	nro_jugador;	
	int	    pensado;						
	int*    alguien_acerto;
    int     intento;
    int*    intentos;
    int*    posicion;
    int     cantidad_intentos;
}adiv;

#endif
