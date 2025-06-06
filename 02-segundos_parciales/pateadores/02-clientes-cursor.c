#include "cola.h"
#include "define.h"
#include "global.h"
#include "memoria.h"
#include "thread.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

  /* Variables comunes */
  int cantidad = 1;
  int done = 0;
  int i = 0;

  /* Variables de hilos */
  pthread_attr_t atributos;
  pthread_t *idHilo = NULL;
  caj *datos_thread = NULL;

  /* Variables de mensajes */
  int id_cola_mensajes = -1;

  /* Variables de memoria */
  int id_memoria = -1;

  /* Semaforo memoria */
  semaforo_de_memoria(0);

  /* Asignacion de Variables */
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  if (id_cola_mensajes == -1) {
    printf("Error al crear cola de mensajes\n");
    return 1;
  }
  borrar_mensajes(id_cola_mensajes);

  if (argc > 1) {
    cantidad = atoi(argv[1]);
  }

  /* Creo todo lo que necesito */
  idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
  if (idHilo == NULL) {
    printf("Error al asignar memoria para hilos\n");
    return 1;
  }

  pthread_attr_init(&atributos);
  pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&mutex, NULL);

  datos_thread = (caj *)malloc(sizeof(caj) * cantidad);
  if (datos_thread == NULL) {
    printf("Error al asignar memoria para datos de thread\n");
    free(idHilo);
    return 1;
  }

  memset(datos_thread, 0, sizeof(caj) * cantidad);

  for (i = 0; i < cantidad; i++) {

    datos_thread[i].nro_cajero = i;
    datos_thread[i].id_cola_mensajes = id_cola_mensajes;
    datos_thread[i].id_memoria = &id_memoria;
    datos_thread[i].terminar = &done;

    pthread_create(&idHilo[i], &atributos, ThreadCajeros, &datos_thread[i]);
  }

  while (done == 0) {
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
    usleep(10 * 1000);
  };

  for (i = 0; i < cantidad; i++) {
    pthread_join(idHilo[i], NULL);
  }

  /* Limpieza final */
  pthread_attr_destroy(&atributos);
  pthread_mutex_destroy(&mutex);
  
  if (idHilo != NULL) {
    free(idHilo);
  }
  if (datos_thread != NULL) {
    free(datos_thread);
  }
  if (id_cola_mensajes != -1) {
    borrar_mensajes(id_cola_mensajes);
  }

  printf("JUEGO TERMINADO\n");
  return 0;
}
