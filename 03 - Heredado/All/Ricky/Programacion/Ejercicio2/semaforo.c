#include "stdlib.h"
#include "stdio.h"
#include "def.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "clave.h"
#include "def.h"
#include "semaforo.h"

struct sembuf operacion;

int creo_semaforo() {
    key_t clave = creo_clave(CLAVE_BASE); 
    int id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);

    if (id_semaforo == -1) {
        perror("Error al crear semáforo"); 
        exit(EXIT_FAILURE); 
    }
    return id_semaforo;
}
void inicio_semaforo(int id_semaforo, int valor)
{   
    printf("iniciando semáforo...\n");
	semctl(id_semaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo)
{	
    printf("levantando semáforo...\n");
	operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    if (semop(id_semaforo, &operacion, 1) == -1) {
        perror("Error al liberar el semáforo");
    }
}

void espera_semaforo(int id_semaforo)
{
	printf("Esperando semáforo...\n");
	operacion.sem_num = 0;
	operacion.sem_op = -1;
	operacion.sem_flg = 0;
	semop(id_semaforo, &operacion, 1);

}

void eliminar_semaforo(int id_semaforo)
{
    
    if (semctl(id_semaforo, 0, IPC_RMID) == -1) {
        perror("Error al eliminar el semáforo");
    } else {
        printf("Semáforo eliminado correctamente.\n");
    }
}
