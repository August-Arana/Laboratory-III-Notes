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
  int cantidad_vias, done, i, total_liberaciones;

  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo;
  via *datos_thread;

  /* Variables de mensajes */
  int id_cola_mensajes;

  /* Semaforo memoria */
  semaforo_de_memoria(0);

  /* Asignacion de Variables */
  done = 0;
  total_liberaciones = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  if (argc > 1) {
    cantidad_vias = atoi(argv[1]);
  } else {
    cantidad_vias = 1;
  }


  /* Creo todo lo que necesito */
  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad_vias);
  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&mutex, NULL);

  datos_thread = (via *)malloc(sizeof(via) * cantidad_vias);

  for (i = 0; i < cantidad_vias; i++) {

    datos_thread[i].id_via = i;
    datos_thread[i].id_cola_mensajes = id_cola_mensajes;
    datos_thread[i].total_liberaciones = 0;
    datos_thread[i].done = &done;

    pthread_create(&idHilo[i], &atributos, ThreadPeajes, &datos_thread[i]);
  }

  srand(time(0));

  while (done != cantidad_vias) {
    pthread_mutex_lock(&mutex);
    total_liberaciones = 0;
    for (i = 0; i < cantidad_vias; i++) {
        total_liberaciones+= datos_thread[i].total_liberaciones;
        printf("\nLa via %d libero un total de %d autos\n", datos_thread[i].id_via, datos_thread[i].total_liberaciones); 
    }
    printf("Se han liberado un total de %d autos\n\n", total_liberaciones);

    pthread_mutex_unlock(&mutex);
    usleep(500 * 1000);
  };

  for (i = 0; i < cantidad_vias; i++) {
    pthread_join(idHilo[i], NULL);
  }
  return 0;
}
