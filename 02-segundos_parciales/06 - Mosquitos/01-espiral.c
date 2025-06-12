#include "cola.h"
#include "define.h"
#include "memoria.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int done;
  int i;
  int posiciones[3] = {0};
  int avance;
  char especie[15];

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;
  char contenido_mensaje[100];

  /* Asignacion de variables y limpieza memoria */
  done = 0;
  avance = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  memset(contenido_mensaje, 0, sizeof(contenido_mensaje));

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  /* rand */
  srand(time(0));

  /* Le envio inicio a los jugadores */
  for (i = 0; i < 3; i++) {
    enviar_mensaje(id_cola_mensajes, MSG_MOSQUITOS + i, MSG_ESPIRAL, EVT_INICIO,
                   contenido_mensaje);
  }

  while (done != 3) {

    recibir_mensaje(id_cola_mensajes, MSG_ESPIRAL, &msg);
    usleep(300 * 1000);

    switch (msg.int_evento) {

    case EVT_AVANZO:
      sscanf(msg.char_mensaje, "%d", &avance);
      posiciones[msg.int_rte - 2] += avance;
      if (msg.int_rte - 2 == 0) {
        strcpy(especie, "humo");
        printf("El %s avanza %d metros este turno, va un total de %d\n\n",
               especie, avance, posiciones[msg.int_rte - 2]);
      } else {
        strcpy(especie, "mosquito");
        printf("El %s %d avanza %d metros este turno, va un total de %d\n\n",
               especie, msg.int_rte - 2, avance, posiciones[msg.int_rte - 2]);
      }

      break;

    case EVT_MORI:
      printf("El mosquito %d murio a los %d metros.\n\n", msg.int_rte - 2,
             posiciones[msg.int_rte]);
      done++;
      break;

    case EVT_LLEGUE:
      if (msg.int_rte - 2 == 0) {
        printf("El humo llego!!\n\n");
      } else {
        printf("El mosquito %d llego!!\n\n", msg.int_rte - 2);
      }
      done++;
      break;
    }

    usleep(300 * 1000);
  };

  printf("FIN CARRERA ESPIRAL\n");
  return 0;
}
