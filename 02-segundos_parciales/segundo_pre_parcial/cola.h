#ifndef _COLA_H
#define _COLA_H

typedef struct mensaje {
  long long_dest;
  int int_rte;
  int int_evento;
  char char_mensaje[100];
} mensaje;

int creo_id_cola_mensajes(int);
int enviar_mensaje(int, long, int, int, char *);
int recibir_mensaje(int, long, mensaje *);
int borrar_cola_de_mensajes(int);
int borrar_mensajes(int);

#endif
/* OJO LAS LLAMADAS DE MENSAJES SON EVENTOS BLOQUEANTES */
