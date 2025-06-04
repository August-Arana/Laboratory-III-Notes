#include "clave.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

void *creo_memoria(int size, int *r_id_memoria, int clave_base) {
  void *ptr_memoria;
  int id_memoria;
  id_memoria = shmget(creo_clave(clave_base), size, 0777 | IPC_CREAT);
  if (id_memoria == -1) {
    printf("No consigo id para memoria compartida\n");
    exit(0);
  }
  ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);
  if (ptr_memoria == NULL) {
    printf("No consigo memoria compartida\n");
    exit(0);
  }
  *r_id_memoria = id_memoria;
  return ptr_memoria;
}

void semaforo_de_memoria(int inicia_proceso) {

  int *flag_ptr;
  int id_flag;

  flag_ptr = (int *)creo_memoria(sizeof(int), &id_flag, 7698);

  if (inicia_proceso) {

    flag_ptr[0] = inicia_proceso;

  } else {

    while (flag_ptr[0] != 1) {
      sleep(1);
    }
  }

  return;
}
