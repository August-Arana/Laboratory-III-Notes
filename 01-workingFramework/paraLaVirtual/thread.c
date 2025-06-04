#include "define.h"
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
  int pensado;
  int ya_intentado;
  int j;

  /* Variables de hilos */
  adiv *datos_thread = (adiv *)parametro;
  nro_jugador = datos_thread->nro_jugador;
  alguien_acerto = datos_thread->alguien_acerto;
  posicion = datos_thread->posicion;
  pensado = datos_thread->pensado;
  intentos = datos_thread->intentos;

  ya_intentado = 0;

  printf("\nSoy el jugador %d\n", nro_jugador + 1);

  while (done == 0) {
    pthread_mutex_lock(&mutex);
    if (g_control != 0) {
      /* es el turno de este thread */
      g_control--;
      if (*alguien_acerto == 0) {
        /* nadie acerto todavia */
        /* Voy a probar un numero nuevo */
        ya_intentado = 0;
        while (ya_intentado == 0) {
          /* El numero que voy a intentar, todavia no lo intente */
          intento = rand() % (ADIVINADO_HASTA + 1 - ADIVINADO_DESDE) +
                    ADIVINADO_DESDE;
          ya_intentado = 1;
          for (j = 0; j < 99; j++) {
            /* Me fijo y comparo con intentos anteriores de todos los jugadores
             */
            if (intento == intentos[j]) {
              /* como ya se intento ese numero, pienso otro */
              ya_intentado = 0;
            }
          }
        }
        /* Aumento cont. y guardo el numero que quise adivinar */
        datos_thread->cantidad_intentos++;
        intentos[(*posicion)] = intento;
        (*posicion)++;

        printf("Jugador %d: Es el numero %d ?\n", nro_jugador + 1, intento);

        if (intento == pensado) {
          *alguien_acerto = nro_jugador + 1;
        }

      } else {
        done = 1;
      }
    }
    pthread_mutex_unlock(&mutex);

    usleep(TIEMPO_COMPRUEBA * 1000);
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
  int bolilla_local;
  int i, j;

  /* Variables de hilos */
  tjugador *datos_thread = (tjugador *)parametro;
  nro_jugador = datos_thread->nro_jugador;

  encontrado = 0;
  done = 0;
  bolilla_local = 0;

  printf("\nSoy el jugador %d\n", nro_jugador + 1);

  for (i = 0; i < CANT_CARTON; i++) {
    /* En esta seccion se CREA el carton del jugador */
    encontrado = 0;
    while (encontrado == 0) {
      bolilla_local =
          rand() % (BOLILLA_HASTA + 1 - BOLILLA_DESDE) + BOLILLA_DESDE;
      encontrado = 1;
      for (j = 0; j < CANT_CARTON; j++) {
        if (bolilla_local == carton[j])
          encontrado = 0;
      }
    }
    
    /* El nombre de las variables no es el mejor, aunque, es codigo reciclado */
    /* Pero el tema es que aca se esta usando 'bolilla' como variable de
     * creacion del numero de carton */
    carton[i] = bolilla_local;
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);
    if (g_control != 0) {
      g_control--;
      if (g_carton_lleno == 0) {
        for (i = 0; i < CANT_CARTON; i++) {

          /* PAra cada numero del carton */

          /* recorrer cada bolilla */
          /* Agarro un numero del carton y lo comparo con todas las bolillas
           */
          printf("La bollilla que salio es: %d", bolilla);
          if (carton[i] == bolilla && carton[i] != 0) {
            carton[i] = 0;
            cantidad_aciertos++;
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
