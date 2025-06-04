#include "sys/ipc.h"
#include "sys/sem.h"
#ifndef _SEMAFORO
#define _SEMAFORO

int creo_semaforo(void);
void inicio_semaforo(int id_semaforo, int valor);
void levanta_semaforo(int id_semaforo);
void espera_semaforo(int id_semaforo);
void eliminar_semaforo(int id_semaforo);
#endif
