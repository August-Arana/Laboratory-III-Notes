
#include "define.h"
#include "memoria.h"
#include "semaforos.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int id_semaforo;
  int aleatorio;
  int id_memoria;
  int i;
  dat *memoria = NULL;

  memoria = (dat *)creo_memoria(sizeof(dat) * 10, &id_memoria, CLAVEBASE);

  printf("%d\n", id_memoria);

  while (1) {
    printf("Escribimos en la memoria\n");
    for (i = 0; i < 10; i++) {
      aleatorio = rand() % (20 - 7) + 7;
      memoria[i].numero = aleatorio;
      memoria[i].letra = 0x41 + aleatorio;
      printf("Escrito %d %c\n", memoria[i].numero, memoria[i].letra);
      sleep(1);
    }
    printf("Dejamos de escribir en la memoria\n");
    printf("Memoria Ejemplo: %d %c\n", memoria[7].numero, memoria[7].letra);
    sleep(10);
  }

  shmdt((char *)memoria);
  shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

  return 0;
}
