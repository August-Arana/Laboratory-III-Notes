#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "define.h"
#include "global.h"
#include "thread.h"

int main(int argc, char *argv[]) {
  int i;
  pthread_t *idHilo;
  int cantidad = 1;
  pthread_attr_t atributos;
  int bolillas[BOLILLA_HASTA] = {0};
  int bolilla = 0;
  tjugador *datos_thread;
  int done = 0;
  int j, encontrado;

  if (argc > 1)
    cantidad = atoi(argv[1]);

  printf("%d\n", cantidad);

  srand(time(NULL));

  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init(&mutex, NULL);

  datos_thread = (tjugador *)malloc(sizeof(tjugador) * cantidad);

  for (i = 0; i < cantidad; i++) {
    datos_thread[i].nro_jugador = i;
    datos_thread[i].cantidad_aciertos = 0;
    datos_thread[i].bolillas = bolillas;
    pthread_create(&idHilo[i], &atributos, ThreadJugadores, &datos_thread[i]);
  }

  while (done == 0) {

    pthread_mutex_lock(&mutex);
    if (g_control == 0) {
      g_control = cantidad;
      if (g_carton_lleno == 0) {
        encontrado = 0;
        while (encontrado == 0) {
          bolilla = rand() % (BOLILLA_HASTA + 1 - BOLILLA_DESDE) + BOLILLA_DESDE;
          encontrado = 1;
          for (j = 0; j < BOLILLA_HASTA; j++) {
            if (bolilla == bolillas[j])
              encontrado = 0;
          }
        }
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
