#ifndef _FUNCIONES_H
#define _FUNCIONES_H

#include "defs.h"

typedef struct tipo_mensajes t_mensaje;

struct tipo_mensajes {
    long destinatario; /* Destinatario */
    int remitente; /* Remitente */
    int evento; /* Numero de nevento */
    char mensaje[BUFFER_SIZE]; /* Mensajes */
};

/**
 * Crea una cola de mensajes
 * @param clave clave de la cola de mensajes
 * @return id de la cola de mensaje creada
 */
int creo_id_cola_mensajes(int clave);

/**
 * Envia un mensaje a una cola
 * @param id_cola_mensajes id de la cola de mensaje
 * @param destinatario destinatario
 * @param remitente remitente
 * @param evento id de event
 * @param char_msg mensaje
 * @return 0 si no hay errores
 */
int enviar_mensaje(int id_cola_mensajes, long destinatario, int remitente, int evento, char *char_msg);

/**
 * Recibe mensajes de una cola
 * @param id_cola_mensajes id de la cola de mensaje
 * @param destinatario destinatario
 * @param mensaje mensaje
 * @return
 */
int recibir_mensaje(int id_cola_mensajes, long destinatario, t_mensaje *mensaje);

/**
 * Bora los mensajes de una cola de mensajes (recibiendo todos los mensajes)
 * @param id_cola_mensajes id de la cola de mensaje
 * @return 0 si no hay errores
 */
int borrar_mensajes(int id_cola_mensajes);

/**
 * Elimina del sistema una cola de mensajes
 * @param id_cola_mensajes id de la cola de mensajes
 * @return
 */
int borrar_cola_de_mensajes(int id_cola_mensajes);

#endif
