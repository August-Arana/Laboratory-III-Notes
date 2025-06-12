#ifndef _DEFINE_H
#define _DEFINE_H

/* _________ Ejercicio adivinador _________ */
#define CLAVEBASE 33

#define ADIVINADO_DESDE 1
#define ADIVINADO_HASTA 99


#define MSG_NADIE 0
#define MSG_PIENSO 1
#define MSG_JUGADOR 2

#define EVT_NINGUNO 0
#define EVT_NUMERO 1
#define EVT_ACERTO 2
#define EVT_NO_ACERTO 3
#define EVT_FINALIZAR 4

#define MSG_ADIVINADOR 1
#define MSG_ADIVINANTE 2

typedef struct tipo_adivinante {
  int nro_jugador;
  int *alguien_acerto;
  int intento;
  int *intentos;
  int *posicion;
  int cantidad_intentos;
  int id_cola_mensajes;
} adiv;

#endif
