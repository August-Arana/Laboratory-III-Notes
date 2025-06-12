#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "memoria.h"
#include "claves_ipc.h"


void *crear_memoria(int size, int *r_id_memoria, key_t clave) {
    void *ptr_memoria;
    int id_memoria;
    id_memoria = shmget(clave, size, 0777 | IPC_CREAT);
    if (id_memoria == -1) {
        perror("No consigo id para memoria compartida");
        exit(0);
    }
    ptr_memoria = (void *) shmat(id_memoria, (char *) 0, 0);
    if (ptr_memoria == NULL) {
        perror("No consigo memoria compartida");
        exit(0);
    }
    *r_id_memoria = id_memoria;
    return ptr_memoria;
}

void *crear_memoria_hardcodeada(int size, int *r_id_memoria) {
    void *ptr_memoria;
    int id_memoria;
    id_memoria = shmget(crear_clave_ipc_hardcodeada(), size, 0777 | IPC_CREAT);
    if (id_memoria == -1) {
        perror("No consigo id para memoria compartida");
        exit(0);
    }
    ptr_memoria = (void *) shmat(id_memoria, (char *) 0, 0);
    if (ptr_memoria == NULL) {
        perror("No consigo memoria compartida");
        exit(0);
    }
    *r_id_memoria = id_memoria;
    return ptr_memoria;
}

void liberar_memoria(void *memoria, int id_memoria) {
    shmdt((char *) memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *) NULL);
}
