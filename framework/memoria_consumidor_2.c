
#include "define.h"
#include "memoria.h"
#include "semaforos.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int aleatorio;
  int id_memoria1;
  int id_memoria2;
  int i;
  int *memoria = NULL;
  dat *memoria2 = NULL;

  memoria = (int *)creo_memoria(1, &id_memoria1, CLAVEBASE);
  memoria2 = (dat *)creo_memoria(sizeof(dat) * 10, &id_memoria2, CLAVEBASE2);

  while(memoria != 1){
    sleep(5);
  }

  while (1) {
    printf("Leo memoria 2\n");
    for (i = 0; i < 10; i++) {
      printf("Leido: %d %c\n", memoria2[i].numero, memoria2[i].letra);
      sleep(1);
    }
    printf("Dejo de leer memoria 2\n");
    sleep(10);
  }

  shmdt((char *)memoria);
  shmctl(id_memoria1, IPC_RMID, (struct shmid_ds *)NULL);

  shmdt((char *)memoria2);
  shmctl(id_memoria2, IPC_RMID, (struct shmid_ds *)NULL);

  return 0;
}
