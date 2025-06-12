#include "cola.h"
#include "define.h"
#include "global.h"
#include "memoria.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  /* Variables comunes */
  int cantidad_jugadores, done, i;

  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo;
  jug *datos_thread;

  /* Variables de mensajes */
  int id_cola_mensajes;

  /* Semaforo memoria */
  semaforo_de_memoria(0);

  /* Asignacion de Variables */
  done = 0;
  cantidad_jugadores = 2;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  /* Creo todo lo que necesito */
  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad_jugadores);
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&mutex, NULL);

  datos_thread = (jug *)malloc(sizeof(jug) * cantidad_jugadores);

  for (i = 0; i < cantidad_jugadores; i++) {

    datos_thread[i].id_jugador = i;
    datos_thread[i].id_cola_mensajes = id_cola_mensajes;
    datos_thread[i].done = &done;

    pthread_create(&idHilo[i], &atributos, ThreadJugadores, &datos_thread[i]);
  }

  srand(time(0));

  while (done != cantidad_jugadores) {
    pthread_mutex_lock(&mutex);

    printf("pantalla de principal\n\n");
    pthread_mutex_unlock(&mutex);
    usleep(500 * 1000);
  };

  for (i = 0; i < cantidad_jugadores; i++) {
    pthread_join(idHilo[i], NULL);
  }

  return 0;
}
