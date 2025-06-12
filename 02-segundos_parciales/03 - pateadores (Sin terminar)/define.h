#ifndef _DEFINE_H
#define _DEFINE_H

/* _________ Ejercicio adivinador _________ */
#define CLAVEBASE 33
#define LONGITUD 50

#define EVT_CLT_INICIO 10
#define EVT_CLT_FIN 11
#define EVT_FINALIZAR 12

typedef enum {
  MSG_NADIE,
  MSG_ARQUERO,
  MSG_PATEADOR,
} Destinos;

typedef enum {
  EVT_NINGUNO,
  EVT_TIRO,
  EVT_GOL,
  EVT_PALO,
  EVT_TRAVESAÑO,
  EVT_FUERA
} Eventos;

typedef struct pateador {
  int nro_pateador;
  char resultado[20];
  int id_cola_mensajes;
  int *done;
} pat;

typedef struct para_memoria{
  pat pateadores[5];
  int *goles;
}memo;

#endif
