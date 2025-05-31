#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include "pthread.h"
#include <stdio.h>
#include <unistd.h>
/*  */

void *ThreadAdivinantes(void *parametro) {
  /* recorda que esta funcion se va a 'instanciar' la cantidad de veces que sea
   * necesaria y, hasta donde cada una de esas instancias va a tener su copia de
   * variables */
  int *alguien_acerto;
  int *posicion;
  int *intentos;
  int nro_jugador;
  int done = 0;
  int intento = 0;
  int ya_intentado;
  int j;
  int id_cola_mensajes;
  mensaje msg;
  char mensaje_final[100];

  /* Variables de hilos */
  adiv *datos_thread = (adiv *)parametro;
  nro_jugador = datos_thread->nro_jugador;
  alguien_acerto = datos_thread->alguien_acerto;
  posicion = datos_thread->posicion;
  intentos = datos_thread->intentos;
  id_cola_mensajes = datos_thread->id_cola_mensajes;

  ya_intentado = 0;

  printf("\nSoy el jugador %d\n", nro_jugador + 1);
/*Aca podria ir un recibir mensaje para "Iniciar el juego" */
/* sin recibirlo, no arranca */
/* Igual, recorda, no hay silver bullets para estos ejercicios */
  while (done == 0) {
    pthread_mutex_lock(&mutex);
    if (*alguien_acerto == 0) {

      intento = inNumeroAleatorio(ADIVINADO_DESDE, ADIVINADO_HASTA);
      datos_thread->cantidad_intentos++;
      intentos[(*posicion)] = intento;
      (*posicion)++;

      sprintf(mensaje_final, "quiero adivinar con %d", intento);

      printf("Jugador %d: Es el numero %d ?\n", nro_jugador + 1, intento);

      enviar_mensaje(id_cola_mensajes, MSG_ADIVINADOR,
                     MSG_ADIVINANTE + nro_jugador, EVT_INTENTO_ADIVINAR,
                     mensaje_final);

      recibir_mensaje(id_cola_mensajes, MSG_ADIVINANTE + nro_jugador, &msg);
      printf("%s\n", msg.char_mensaje);

      sleep(1);

    } else {
      done = 1;
    }
    pthread_mutex_unlock(&mutex);

    sleep(1);
  };

  pthread_exit((void *)"Listo");
}

