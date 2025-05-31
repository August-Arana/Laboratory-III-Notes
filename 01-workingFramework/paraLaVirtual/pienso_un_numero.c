#include "define.h"
#include "funciones.h"
#include "global.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int i, cantidad, done, alguien_acerto, pensado;
  int intentos[99] = {0};
  int posicion;
  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo;
  adiv *datos_thread;

  cantidad = 1;
  done = 0;
  pensado = 0;
  alguien_acerto = 0;
  posicion = 0;

  pensado = inNumeroAleatorio(ADIVINADO_DESDE, ADIVINADO_HASTA);

  if (argc > 1)
    cantidad = atoi(argv[1]);

  /* Creo todo lo que necesito */
  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&mutex, NULL);

  datos_thread = (adiv *)malloc(sizeof(adiv) * cantidad);

  for (i = 0; i < cantidad; i++) {
    datos_thread[i].nro_jugador = i;
    datos_thread[i].pensado = pensado;
    datos_thread[i].alguien_acerto = &alguien_acerto;
    datos_thread[i].intentos = intentos;
    datos_thread[i].posicion = &posicion;
    datos_thread[i].cantidad_intentos = 0;
    pthread_create(&idHilo[i], &atributos, ThreadAdivinantes, &datos_thread[i]);
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);
    if (g_control == 0) {
      /* g_control es como una turnera, segun el numero, es a quien le toca
       * jugar */
      g_control = cantidad;
      if (alguien_acerto == 0) {

        printf("Narrador: Nadie adivino el numero %d en esta ronda\n\n",
               pensado);

        printf("Numeros intentados:\n");
        for (i = 0; i < 99; i++) {
          if (intentos[i] != 0) {
            if (i == 0) {
              printf("%d", intentos[i]);
            } else {
              printf(", %d", intentos[i]);
            }
          }
        }
        printf("\n___________________\n\n");

      } else {
        done = 1;
        printf("\nEl jugador %d adivino\n", alguien_acerto);
        for (i = 0; i < cantidad; i++) {
          printf("El jugador %d jugo %d intentos\n",
                 datos_thread[i].nro_jugador,
                 datos_thread[i].cantidad_intentos);
        }
      }
    }
    pthread_mutex_unlock(&mutex);
    usleep(TIEMPO_BOLILLAS * 1000);
  };

  for (i = 0; i < cantidad; i++) {
    pthread_join(idHilo[i], NULL);
  }
  printf("JUEGO TERMINADO\n");
  return 0;
}
