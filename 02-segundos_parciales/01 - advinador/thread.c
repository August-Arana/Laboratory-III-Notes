#include "cola.h"
#include "define.h"
#include "global.h"
#include "pthread.h"
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
/*  */

void *ThreadAdivinantes(void *parametro) {
  /* Variables comunes */
  int done;
  int intento;
  int ya_intentado;
  int j;

  /* Variables de mensajes */
  mensaje msg;
  char mensaje_final[100];

  /* Variables de hilos */
  adiv *datos_thread = (adiv *)parametro;
  int nro_jugador;
  int *alguien_acerto;
  int id_cola_mensajes;
  int *intentos;
  int *posicion;

  /* Asignacion de variables */
  nro_jugador = datos_thread->nro_jugador;
  alguien_acerto = datos_thread->alguien_acerto;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  intentos = datos_thread->intentos;
  posicion = datos_thread->posicion;

  done = 0;
  intento = 0;

  printf("\nSoy el jugador %d\n", nro_jugador + 1);
  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0) {
    pthread_mutex_lock(&mutex);
    /* Primero me fijo si alguien ya acerto */
    /* Si alguien ya adivino, no me meto y no bloqueo con 'recibir mensaje' */
    if (*alguien_acerto == 0) {

      ya_intentado = 0;
      /* Me invento un numero */
      while (ya_intentado == 0) {
        intento =
            rand() % (ADIVINADO_HASTA + 1 - ADIVINADO_DESDE) + ADIVINADO_DESDE;
        ya_intentado = 1;

        for (j = 0; j < 98; j++) {
          if (intento == intentos[j]) {
            ya_intentado = 0;
          }
        }
      }

      intentos[(*posicion)] = intento;
      (*posicion)++;
      /* Imprimo mensaje para mostrar quien soy, lo uno todo en mensaje final */
      printf("Soy el jugador %d quiero adivinar con %d", nro_jugador + 1,
             intento);
      sprintf(mensaje_final, "Es el numero %d?", intento);

      /* Le digo al pensador que quiero adivinar */

      enviar_mensaje(id_cola_mensajes, MSG_PIENSO, MSG_ADIVINANTE + nro_jugador,
                     EVT_NUMERO, mensaje_final);

      /* Veo que me responde el adivinador */
      recibir_mensaje(id_cola_mensajes, MSG_ADIVINANTE + nro_jugador, &msg);

      switch (msg.int_evento) {

      case EVT_NO_ACERTO:
        /* No acerte, sigue todo como antes */
        printf("\nPensador: %s\n", msg.char_mensaje);
        break;

      case EVT_ACERTO:
        /* Acerte! Le digo al adivinador que cierre el proceso */
        printf("\nPensador: %s\n", msg.char_mensaje);
        enviar_mensaje(id_cola_mensajes, MSG_PIENSO,
                       MSG_ADIVINANTE + nro_jugador, EVT_FINALIZAR,
                       mensaje_final);
        /* Y le aviso al resto de los threads que gane */
        *alguien_acerto = 1;
        break;

      default:
        printf("\nEvento sin definir\n");
        break;
      }

      sleep(1);

    } else {
      done = 1;
    }
    pthread_mutex_unlock(&mutex);

    sleep(1);
  };

  pthread_exit((void *)"Listo");
}
