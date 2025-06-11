#ifndef _DEFINE_H
#define _DEFINE_H

/* _________ Ejercicio adivinador _________ */
#define CLAVEBASE 33
#define LONGITUD 50

typedef enum {
  MSG_NADA,
  MSG_AUTOS,
  MSG_VIA
} msjs;

typedef enum {
  EVT_FINALIZA,
  EVT_VEHICULOS
} evts;

typedef struct via {
  int id_via;
  int id_cola_mensajes;
  int total_liberaciones;
  int *done;
} via;

#endif
