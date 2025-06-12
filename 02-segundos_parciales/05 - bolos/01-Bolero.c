#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "memoria.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int done;
  int i, j;
  int jugador;
  int cantidad_pinos_tirados;
  int pinos_disponibles;
  int posicion_tirado;
  int done_tirado;
  int puntos_finales;

  pin jugadores[2];

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;
  char contenido_mensaje[100];

  /* Asignacion de variables y limpieza memoria */
  done = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  memset(contenido_mensaje, 0, sizeof(contenido_mensaje));
  puntos_finales = 0;

  /* Asignacion inicial datos jugadores */
  for (i = 0; i < 2; i++) {
    jugadores[i].tiros_totales = 0;
    for (j = 0; j < 10; j++) {
      jugadores[i].posicion_pinos[j] = 1;
    }
    jugadores[i].cantidad_pinos_disponibles = 10;
  }

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  /* rand */
  srand(time(0));

  /* Le envio inicio a los jugadores */
  for (i = 0; i < 2; i++) {

    enviar_mensaje(id_cola_mensajes, MSG_JUGADORES + i, MSG_BOLOS, EVT_INICIO,
                   contenido_mensaje);
  }

  while (done != 2) {

    recibir_mensaje(id_cola_mensajes, MSG_BOLOS, &msg);
    usleep(300 * 1000);

    switch (msg.int_evento) {

    case EVT_TIRO:

      puntos_finales = 0;
      jugador = msg.int_rte - 2;
      jugadores[jugador].tiros_totales++;
      pinos_disponibles = jugadores[jugador].cantidad_pinos_disponibles;
      cantidad_pinos_tirados = inNumeroAleatorio(1, pinos_disponibles);

      jugadores[jugador].cantidad_pinos_disponibles -= cantidad_pinos_tirados;
      pinos_disponibles -= cantidad_pinos_tirados;
      puntos_finales += cantidad_pinos_tirados;

      printf("Jugador %d tiro %d y le faltan %d\n\n", msg.int_rte-2, cantidad_pinos_tirados, pinos_disponibles);

      if (pinos_disponibles == 0 || jugadores[jugador].tiros_totales == 3) {

        if (cantidad_pinos_tirados == 10) {
          printf("\n\nCHUZA!\n\n");
          cantidad_pinos_tirados = 20;
        }

        sprintf(contenido_mensaje, "%d", cantidad_pinos_tirados);

        enviar_mensaje(id_cola_mensajes, MSG_JUGADORES + jugador, MSG_BOLOS,
                       EVT_FIN, contenido_mensaje);
        done++;

      } else {

        for (i = 0; i < cantidad_pinos_tirados; i++) {
          posicion_tirado = inNumeroAleatorio(0, 9);
          done_tirado = 0;

          while (done_tirado == 0 && pinos_disponibles == 0) {

            if (jugadores[jugador].posicion_pinos[posicion_tirado] == 1) {

              jugadores[jugador].posicion_pinos[posicion_tirado] = 0;
              done_tirado = 1;

            } else {

              posicion_tirado = inNumeroAleatorio(0, 9);
            }
          }
        }
      }

      sprintf(contenido_mensaje, "%d", puntos_finales);
      enviar_mensaje(id_cola_mensajes, MSG_JUGADORES + jugador, MSG_BOLOS,
                     EVT_RESULTADO, contenido_mensaje);
      break;
    }

    usleep(300 * 1000);
  };

  printf("FIN DE BOLOS\n");
  return 0;
}
