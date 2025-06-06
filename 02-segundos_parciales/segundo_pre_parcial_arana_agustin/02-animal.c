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
  int cantidad, done, i;

  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo;
  ani *datos_thread;

  /* Variables de mensajes */
  int id_cola_mensajes;

  /* Asignacion de Variables */
  done = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  cantidad = 3;

  /* Semaforo memoria */
  semaforo_de_memoria(0);

  /* Srand */
  srand(time(0));

  
  /* Creo todo lo que necesito */
  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&mutex, NULL);

  datos_thread = (ani *)malloc(sizeof(ani) * cantidad);

  for (i = 0; i < cantidad; i++) {

    datos_thread[i].id_animal = i;
    datos_thread[i].id_cola_mensajes = id_cola_mensajes;
    datos_thread[i].terminar = &done;

    pthread_create(&idHilo[i], &atributos, ThreadAnimales, &datos_thread[i]);
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
    usleep(10 * 1000);
  };

  for (i = 0; i < cantidad; i++) {
    pthread_join(idHilo[i], NULL);
  }
  printf("JUEGO TERMINADO\n");
  return 0;
}
