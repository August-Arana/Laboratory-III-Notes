#include "define.h"
#include "funciones.h"
#include "global.h"
#include "memoria.h"
#include <stdio.h>
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
  memoria2 = (dat *)creo_memoria(sizeof(dat) * ITERACIONES , &id_memoria2, CLAVEBASE2);

  while (1) {
    printf("Escribo memoria 2\n");
    for (i = 0; i < ITERACIONES; i++) {
      aleatorio = inNumeroAleatorio(7, 20);
      memoria2[i].numero = aleatorio;
      memoria2[i].letra = 0x41 + aleatorio;
      printf("Escrito %d %c\n", memoria2[i].numero, memoria2[i].letra);
      sleep(1);
    }
    global_counter++;
    printf("contador global: %d \n", global_counter);
    memoria[0] = 1;
    while (memoria[0] != 0) {
      sleep(5);
    }
  }

  shmdt((char *)memoria);
  shmctl(id_memoria1, IPC_RMID, (struct shmid_ds *)NULL);

  shmdt((char *)memoria2);
  shmctl(id_memoria2, IPC_RMID, (struct shmid_ds *)NULL);

  return 0;
}
