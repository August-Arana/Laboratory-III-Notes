#include "archivos.h"
#include "cola.h"
#include "define.h"
#include "global.h"
#include "memoria.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*  */

void *ThreadPateadores(void *parametro) {
  /* Variables comunes */
  int *done;
  int cantidad;

  /* Variables de mensajes */
  mensaje msg;

  /* Variables de hilos */
  pat *datos_thread = (pat *)parametro;
  int nro_pateador;
  int id_cola_mensajes;

  /* Variables de Memoria */
  int *goles;

  /* Asignacion de variables */
  nro_pateador = datos_thread->nro_pateador;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  goles = datos_thread->goles;
  done = datos_thread->done;

  printf("\nSoy el pateador %d\n", nro_pateador + 1);
  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  recibir_mensaje(id_cola_mensajes, MSG_PATEADOR + nro_pateador, &msg);
  printf("Voy a patear, envio mensaje al arquero\n");
  pthread_mutex_lock(&mutex);

  enviar_mensaje(id_cola_mensajes, MSG_ARQUERO, MSG_PATEADOR + nro_pateador,
                 EVT_TIRO, "TIROOO!");

  (*done)++;

  recibir_mensaje(id_cola_mensajes, MSG_PATEADOR + nro_pateador, &msg);

  /* Veo que hay adentro del mensaje */

  switch (msg.int_evento) {

  case EVT_GOL:
    printf("GOOOOOOOOL!!\n");
    (*goles)++;

    break;

  case EVT_PALO:
    printf("UUHHH!\n");

    break;

  case EVT_TRAVESAÑO:
    printf("UUHHH!\n");

    break;

  case EVT_FUERA:

    break;

  default:
    printf("\nEvento sin definir\n");
    break;
  }

  usleep(500 * 1000);

  pthread_mutex_unlock(&mutex);

  usleep(500 * 1000);

  pthread_exit((void *)"Listo");
}
