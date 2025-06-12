#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include "pthread.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*  */

void *ThreadMosquitos(void *parametro) {
  /* Variables comunes */
  int *terminar;
  int *humo;
  int avance;
  int avance_total;
  int murio;
  char especie[15];

  /* Variables de mensajes */
  mensaje msg;
  char contenido_mensaje[100];
  int id_cola_mensajes;

  /* Variables de hilos */
  jug *datos_thread = (jug *)parametro;
  int id_mosquito;

  /* Asignacion de variables */
  id_mosquito = datos_thread->id_mosquito;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  terminar = datos_thread->done;
  humo = datos_thread->humo;
  avance_total = datos_thread->avance_total;

  memset(especie, 0, sizeof(especie));
  memset(contenido_mensaje, 0, sizeof(contenido_mensaje));
  avance = 0;
  murio = 0;

  /* Espero me avisen iniciar */
  recibir_mensaje(id_cola_mensajes, MSG_MOSQUITOS + id_mosquito, &msg);
  usleep(300 * 1000);
  switch (msg.int_evento) {

  case EVT_INICIO:
    avance_total = 0;
    break;
  }

  if (id_mosquito == 0) {
    strcpy(especie, "humo");
  } else {
    strcpy(especie, "mosquito");
  }

  while (avance_total < 96) {
    pthread_mutex_lock(&mutex);

    printf("Soy el %s %d, avanzo\n\n", especie, id_mosquito + 1);

    if (id_mosquito == 0) {
      avance = inNumeroAleatorio(1, 4);
      (*humo) += avance;
      avance_total += avance;
      sprintf(contenido_mensaje, "%d", avance);
      enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL, MSG_MOSQUITOS + id_mosquito,
                     EVT_AVANZO, contenido_mensaje);
    } else {
      avance = inNumeroAleatorio(3, 6);
      avance_total += avance;
      sprintf(contenido_mensaje, "%d", avance);
      if ((*humo >= avance_total)) {
        avance_total = 96;
        murio = 1;
        (*terminar)++;
        printf("Mosquito %d: AAAAHHHHHH\n\n", id_mosquito + 1);
        printf("\n\nYOU DIED\n\n");
        enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL,
                       MSG_MOSQUITOS + id_mosquito, EVT_MORI,
                       contenido_mensaje);
      } else {
        enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL,
                       MSG_MOSQUITOS + id_mosquito, EVT_AVANZO,
                       contenido_mensaje);
      }
    }

    pthread_mutex_unlock(&mutex);
    usleep(300 * 1000);
  };

  if (avance_total >= 96 && murio == 0) {
    enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL, MSG_MOSQUITOS + id_mosquito,
                   EVT_LLEGUE, contenido_mensaje);
    (*terminar)++;
  }

  pthread_exit((void *)"Listo");
}
