#include "define.h"
#include "global.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* */

int main(int argc, char *argv[]) {

  /* Variables comunes */
  int i;
  int cantidad = 1;
  int bolillas[BOLILLA_HASTA] = {0};
  int bolilla = 0;
  int done = 0;
  int j, encontrado;

  /* Variables de hilos */
  pthread_t *idHilo;
  pthread_attr_t atributos;
  tjugador *datos_thread;

  /* Simplemente para conocer la cantidad de argumentos que se le pasan y me
   * quedo con el primero */
  if (argc > 1)
    cantidad = atoi(argv[1]);

  printf("%d\n", cantidad);

  srand(time(NULL));

  /* Programacion verdadera */
  /*
   * 1 - Mutex es global, ya esta hecho no te importa
   * 2 - IdHilo es lo que viene ahora
   */

  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
  /*
   * Lo que pasa ahi es MUY importante. Como vas a tener varios jugadores, lo
   * 'inteligente' es usar un hilo por jugador y lo inteligente en serio es
   * entonces tener un array de todos los hilos que vas a usar. Ese puntero
   * ahora tiene un total de 'cantidad' de hilos. Aca se ve lo que decia el
   * profesor al inicio, un * a la izquierda es un [] a la derecha. por eso
   * despues esto lo podes recorrer tranquilamente con un array y porcada
   * elemento, creas un thread. Excelente!
   */

  /*
   * 3 - Ahora viene la iniciacion y asignacion de los atributos
   */
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

  /*
   * Y ahora si, con los tres pasos cumplitos, inicias el mutex tranquilo
   */

  pthread_mutex_init(&mutex, NULL);

  /*
   * Igual que antes, usas un puntero para declarar todos los jugadores y luego
   * ir rellenando con la info inicial
   */

  /* Memoria de heap -> compartida por todo el proceso */
  datos_thread = (tjugador *)malloc(sizeof(tjugador) * cantidad);

  for (i = 0; i < cantidad; i++) {
    datos_thread[i].nro_jugador = i;
    datos_thread[i].cantidad_aciertos = 0;
    datos_thread[i].bolillas =
        bolillas; /* Estoy repitiendo la bolilla en todos lados.
                     POR ESO ES QUE BOLILLAS DENTRO DE LA ESTRUCTURA ES UN
                     PUNTERO!!! Bingo! */
    pthread_create(&idHilo[i], &atributos, ThreadJugadores, &datos_thread[i]); /* A cada proceso le doy su pedacito de memoria heap para que juegue */
  }

  while (done == 0) {

    pthread_mutex_lock(&mutex);
    if (g_control == 0) {
      /* g_control entiendo es un control global, por ende, una variable que
       * todos van a chequear en algun momento */
      g_control = cantidad;
      if (g_carton_lleno == 0) {
        /* Similar a g_global, ahora ire viendo */
        encontrado = 0;
        while (encontrado == 0) {
          /* busco un numero y lo marco como encontrado */
          bolilla =
              rand() % (BOLILLA_HASTA + 1 - BOLILLA_DESDE) + BOLILLA_DESDE;
          encontrado = 1;

          /* recorro el array de todas las bolillas, si una coincide cambio el
           * enocntrado */
          /* claro, esto es para asegurarme que el numero no salga dos veces. Si
           * encuentro el numero vuelvo a tirar */
          for (j = 0; j < BOLILLA_HASTA; j++) {
            if (bolilla == bolillas[j])
              encontrado = 0;
          }
        }
        /* No entiendo como es que este i puede valer 0 al principio */
        bolillas[i++] = bolilla;

        /* La bolilla tenia 2 opciones, ver la grabacion despues*/
        printf("BINGO: bolilla = %d\n", bolilla);
      } else {
        done = 1;
      }
    }
    pthread_mutex_unlock(&mutex);
    usleep(TIEMPO_BOLILLAS * 1000);
  };

  for (i = 0; i < cantidad; i++) {
    pthread_join(idHilo[i], NULL);
    printf("TERMINO\n");
    printf("PPAL: Jugador %d: %d aciertos\n", i + 1,
           datos_thread[i].cantidad_aciertos);
  }

  return 0;
}
