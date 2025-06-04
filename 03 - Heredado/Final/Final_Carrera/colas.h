#ifndef _COLAS_H
#define _COLAS_H
/*
#include <errno.h>
*/

#define LARGO_TMENSAJE 1024

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
    long long_dest;                    /* Destinatario */
    int int_rte;                       /* Remitente */
    int int_evento;                    /* Numero de nevento */
    char char_mensaje[LARGO_TMENSAJE]; /* mensajse */
};

int creo_id_cola_mensajes(int);
int borrar_mensajes(int);
int recibir_mensaje(int, long, mensaje *);
int recibir_mensaje_sin_espera(int, long, mensaje *);
int enviar_mensaje(int, long, int, int, char *);

#endif

