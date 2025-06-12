#ifndef _DEFINE_H
#define _DEFINE_H

/* _________ Ejercicio adivinador _________ */
#define CLAVEBASE 33
#define LONGITUD 50

typedef enum { MSG_NADA, MSG_BOLOS, MSG_JUGADORES } msjs;

typedef enum { EVT_INICIO, EVT_RESULTADO, EVT_TIRO, EVT_FIN } evts;

typedef struct jugador {
  int id_jugador;
  int id_cola_mensajes;
  int *done;
} jug;

typedef struct tablero_pinos {
  int posicion_pinos[10];
  int tiros_totales;
  int cantidad_pinos_disponibles;
} pin;

#endif
