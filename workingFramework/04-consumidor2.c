#include "define.h"
#include "memoria.h"
#include "global.h"
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int id_memoria1;
  int id_memoria2;
  int i;
  int *memoria = NULL;
  dat *memoria2 = NULL;

  memoria = (int *)creo_memoria(1, &id_memoria1, CLAVEBASE);
  memoria2 = (dat *)creo_memoria(sizeof(dat) * ITERACIONES, &id_memoria2, CLAVEBASE2);

  while (1) {
    while (memoria[0] != 1) {
      sleep(5);
    }
    printf("Leo memoria 2\n");
    for (i = 0; i < ITERACIONES; i++) {
      printf("Leido %d %c\n", memoria2[i].numero, memoria2[i].letra);
      sleep(1);
    }
    printf("Dejo de Leer memoria 2\n");
    global_counter--;
    printf("contador global: %d \n", global_counter);
    memoria[0]=0;
    sleep(5);
  }

  shmdt((char *)memoria);
  shmctl(id_memoria1, IPC_RMID, (struct shmid_ds *)NULL);

  shmdt((char *)memoria2);
  shmctl(id_memoria2, IPC_RMID, (struct shmid_ds *)NULL);

  return 0;
}

/*La idea es tener u a funcion en la cual se utilice lamemoria compartida para que siempre corra el proceso inicializador, el while de aca no esta mal, pero no es corrcto*/
/* poner , ocmo siempre, el readme con las considearciones adecuadas otra idea; utilizar seniales para, por ejemplo, limpiar memoria al tirar ctrl c*/
