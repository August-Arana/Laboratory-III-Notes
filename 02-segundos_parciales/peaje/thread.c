#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*  */

void *ThreadPeajes(void *parametro) {
  /* Variables comunes */
  int cantidad_vehiculos_en_cola;
  int vehiculos_recibidos;
  int done;
  int *terminar;
  int liberaciones;

  /* Variables de mensajes */
  mensaje msg;

  /* Variables de hilos */
  via *datos_thread = (via *)parametro;
  int id_via;
  int id_cola_mensajes;

  /* Asignacion de variables */
  id_via = datos_thread->id_via;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  terminar = datos_thread->done;
  done = 0;
  cantidad_vehiculos_en_cola = 0;
  liberaciones = 0;
  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento,
   * char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0) {
    recibir_mensaje(id_cola_mensajes, MSG_VIA + id_via, &msg);
    usleep(300 * 1000);

    printf("Soy uno de los threads, el %d, recibi un mensaje", id_via);

    pthread_mutex_lock(&mutex);

    /* Veo que hay adentro del mensaje */

    switch (msg.int_evento) {

    case EVT_VEHICULOS:

      vehiculos_recibidos = atoi(msg.char_mensaje);
      cantidad_vehiculos_en_cola += vehiculos_recibidos;

      if (cantidad_vehiculos_en_cola > 0 && cantidad_vehiculos_en_cola <= 10) {

        liberaciones = inNumeroAleatorio(1, 10);
        cantidad_vehiculos_en_cola -= liberaciones;

        if (cantidad_vehiculos_en_cola <= 0) {
          liberaciones += cantidad_vehiculos_en_cola;
          cantidad_vehiculos_en_cola = 0;
        }

      } else if (cantidad_vehiculos_en_cola > 10) {
        liberaciones = cantidad_vehiculos_en_cola;
        cantidad_vehiculos_en_cola = 0;
      }

      printf("Hay %d vehiculos en cola y he liberado %d vehiculos",
             cantidad_vehiculos_en_cola, liberaciones);

      datos_thread->total_liberaciones += liberaciones;

      break;

    case EVT_FINALIZA:
      done = 1;
      (*terminar)++;
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }

    usleep(300 * 1000);

    pthread_mutex_unlock(&mutex);
  };

  pthread_exit((void *)"Listo");
}
