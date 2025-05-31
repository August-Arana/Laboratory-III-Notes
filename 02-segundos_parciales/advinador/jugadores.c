#include "define.h"
#include "cola.h"
#include "global.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int i, cantidad, done, alguien_acerto;
  int intentos[99] = {0};

  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo;
  adiv *datos_thread;

  /* Variables de mensajes */
  int id_cola_mensajes; 

  /* Asignacion de Variables */
  cantidad = 1;
  done = 0;
  alguien_acerto = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  borrar_mensajes(id_cola_mensajes);

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
    datos_thread[i].alguien_acerto = &alguien_acerto;
    datos_thread[i].intentos = intentos;
    datos_thread[i].cantidad_intentos = 0;
    datos_thread[i].id_cola_mensajes = id_cola_mensajes;

    pthread_create(&idHilo[i], &atributos, ThreadAdivinantes, &datos_thread[i]);
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);
      if (alguien_acerto == 0) {

        printf("\nNinguno de los jugadores acerto en esta ronda\n\n");

      } else {
        done = 1;
      }
    pthread_mutex_unlock(&mutex);
    usleep(3 * 1000);
  };

  for (i = 0; i < cantidad; i++) {
    pthread_join(idHilo[i], NULL);
  }
  printf("JUEGO TERMINADO\n");
  return 0;
}
