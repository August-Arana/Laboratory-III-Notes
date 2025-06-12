#ifndef _DEFINE_H
#define _DEFINE_H

#define CLAVEBASE 33

typedef enum
{
  MSG_NADA,
  MSG_ESPIRAL,
  MSG_MOSQUITOS
} msjs;

typedef enum
{
  EVT_INICIO,
  EVT_AVANZO,
  EVT_MORI,
  EVT_LLEGUE
} evts;

typedef struct mosquito
{
  int id_mosquito;
  int id_cola_mensajes;
  int avance_total;
  int *done;
  int *humo;
} jug;

#endif
