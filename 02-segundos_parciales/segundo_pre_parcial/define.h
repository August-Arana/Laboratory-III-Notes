#ifndef _DEFINE_H
#define _DEFINE_H

/* _________ Ejercicio adivinador _________ */
#define CLAVEBASE 33
#define LONGITUD 50

#define MSG_NADIE 0
#define MSG_ADMIN 1
#define MSG_CAJERO 2

#define EVT_CLT_INICIO 10
#define EVT_CLT_FIN 11
#define EVT_FINALIZAR 12

typedef struct cajero {
  int nro_cajero;
  int id_cola_mensajes;
  int *terminar;
  int *id_memoria;
} caj;

typedef struct producto {
  int precio;
  char descripcion[LONGITUD];
} prod;

typedef struct cliente {
  int id;
  prod producto;
} clt;

#endif
