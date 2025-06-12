#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "claves_ipc.h"
#include "semaforos.h"

int crear_semaforo(int clave_base, char *ruta) {
    key_t clave = crear_clave_ipc(ruta, clave_base);
    int id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);
    if (id_semaforo == -1) {
        printf("Error: no puedo crear semaforo\n");
        exit(0);
    }
    return id_semaforo;
}

void inicializar_semaforo(int id_semaforo, int valor) {
    semctl(id_semaforo, 0, SETVAL, valor);
}

void levantar_semaforo(int id_semaforo) {
    struct sembuf operacion;
    printf("Levanta SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}

void esperar_semaforo(int id_semaforo) {
    struct sembuf operacion;
    printf("Espera SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}
