#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
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

void *ThreadJugadores(void *parametro) {
  /* Variables comunes */
  int cantidad_aciertos = 0;
  /* recorda que esta funcion se va a 'instanciar' la cantidad de veces que sea
   * necesaria y, hasta donde cada una de esas instancias va a tener su copia de
   * variables */
  int carton[CANT_CARTON] = {0};
  int *bolillas;
  int nro_jugador;
  int encontrado;
  int done;
  int bolilla;
  int i, j;

  /* Variables de hilos */
  tjugador *datos_thread = (tjugador *)parametro;
  nro_jugador = datos_thread->nro_jugador;
  bolillas = datos_thread->bolillas;

  encontrado = 0;
  done = 0;
  bolilla = 0;

  printf("\nSoy el jugador %d\n", nro_jugador + 1);

  for (i = 0; i < CANT_CARTON; i++) {
    /* En esta seccion se CREA el carton del jugador */
    encontrado = 0;
    while (encontrado == 0) {
      bolilla = rand() % (BOLILLA_HASTA + 1 - BOLILLA_DESDE) + BOLILLA_DESDE;
      encontrado = 1;
      for (j = 0; j < CANT_CARTON; j++) {
        if (bolilla == carton[j])
          encontrado = 0;
      }
    }
    /* El nombre de las variables no es el mejor, aunque, es codigo reciclado */
    /* Pero el tema es que aca se esta usando 'bolilla' como variable de
     * creacion del numero de carton */
    carton[i] = bolilla;
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);
    if (g_control != 0) {
      g_control--;
      if (g_carton_lleno == 0) {
        for (i = 0; i < CANT_CARTON; i++) {
          if (carton[i] != 0) {
            /* PAra cada numero del carton */
            for (j = 0; j < BOLILLA_HASTA; j++) {
              /* recorrer cada bolilla */
              /* Agarro un numero del carton y lo comparo con todas las bolillas
               */
              if (carton[i] == bolillas[j] && carton[i] != 0) {
                carton[i] = 0;
                cantidad_aciertos++;
              }
            }
          }
        }
        printf("JUGADOR %d ", nro_jugador + 1);
        for (j = 0; j < CANT_CARTON; j++) {
          printf(" %02d ", carton[j]);
        }
        if (cantidad_aciertos == CANT_CARTON) {
          g_carton_lleno = nro_jugador + 1;
        }
        printf(" Aciertos=%d g_control=%d g_carton_lleno=%d\n",
               cantidad_aciertos, g_control, g_carton_lleno);
      } else {
        done = 1;
      }
    }
    pthread_mutex_unlock(&mutex);

    usleep(TIEMPO_COMPRUEBA * 1000);
  };

  datos_thread->cantidad_aciertos = cantidad_aciertos;
  pthread_exit((void *)"Listo");
}
