#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#include <pthread.h>

#define LARGO_MINIMO_CIRCUITO 100
#define LARGO_MAXIMO_CIRCUITO 1000
#define MINIMO_AVANCE_AUTO 1
#define MAXIMO_AVANCE_AUTO 10
#define LARGO_MENSAJE 100
#define ESPERA_AUTO 300

typedef struct auto_carrera
{
    int id_cola_mensajes;
    int nro_auto;
} t_auto_carrera;

typedef enum
{
    MSG_NADIE,    /* 0*/
    MSG_CIRCUITO,  /* 1*/
    MSG_AUTOS  /* 2 Cada hilo le suma uno a este define.*/
} Destinos;

typedef enum
{
    EVT_NINGUNO,   /* 0 */
    EVT_INICIO,      /* 1 */
    EVT_AVANZA,       /* 2 */
    EVT_BANDERIN,      /* 3 */
    EVT_AUTOS       /* 4 Envio la cantidad de autos al circuito*/
} Eventos;

#endif
