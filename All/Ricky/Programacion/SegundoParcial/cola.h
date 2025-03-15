#ifndef _COLA
#define _COLA
#include "def.h"

int inCreo_id_cola_mensajes(int clave);
int inEnviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char *rpCharMsg);
int inRecibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);
int inBorrar_mensajes(int id_cola_mensajes);

#endif
