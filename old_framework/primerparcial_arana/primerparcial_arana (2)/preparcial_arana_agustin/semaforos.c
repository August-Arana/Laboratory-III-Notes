#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include "semaforos.h"
#include "clave.h"

int creo_semaforo(){

    key_t clave = creo_clave();
    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);

    if(id_semaforo == -1){
        printf("Error: no puedo crear semaforo\n");
        exit(0);
    }
    return id_semaforo;
}

void inicia_semaforo(int id_semaforo, int valor){
    semctl(id_semaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo){
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1; /*incrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion,1);
}

void espera_semaforo(int id_semaforo){
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = -1; /*decrementa el semaforo en 1*/
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion,1);
}
