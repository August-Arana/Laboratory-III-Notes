#include "cola.h"
#include "define.h"
#include "global.h"
#include "pthread.h"
#include <stdio.h>
#include <unistd.h>
/*  */

void *ThreadJugadores(void *parametro) {
  /* Variables comunes */
  int done;
  int *terminar;
  int puntos_totales;
  int puntos_este_tiro;

  /* Variables de mensajes */
  mensaje msg;
  char contenido_mensaje[100];
  int id_cola_mensajes;

  /* Variables de hilos */
  jug *datos_thread = (jug *)parametro;
  int id_jugador;

  /* Asignacion de variables */
  id_jugador = datos_thread->id_jugador;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  terminar = datos_thread->done;
  done = 1;
  puntos_totales = 0;

  /* Espero me avisen iniciar */
  recibir_mensaje(id_cola_mensajes, MSG_JUGADORES + id_jugador, &msg);
  usleep(300 * 1000);
  switch (msg.int_evento) {

  case EVT_INICIO:
    done = 0;
    break;
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);

    printf("Soy el jugador %d, y voy a tirar\n\n", id_jugador + 1);

    enviar_mensaje(id_cola_mensajes, MSG_BOLOS, MSG_JUGADORES + id_jugador,
                   EVT_TIRO, contenido_mensaje);

    recibir_mensaje(id_cola_mensajes, MSG_JUGADORES + id_jugador, &msg);
    usleep(300 * 1000);

    sscanf(msg.char_mensaje, "%d", &puntos_este_tiro);
    puntos_totales += puntos_este_tiro;

    switch (msg.int_evento) {

    case EVT_RESULTADO:
      /* no muestro total, solo lo que se tiro en estea ronda */
      printf("Tire %d y voy %d puntos\n", puntos_este_tiro, puntos_totales);

      break;

    case EVT_FIN:
      printf("Soy el jugador %d, termino con %d puntos\n\n", id_jugador+1,
             puntos_totales);
      done = 1;
      (*terminar)++;
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }
    pthread_mutex_unlock(&mutex);
    usleep(300 * 1000);
  };

  pthread_exit((void *)"Listo");
}
