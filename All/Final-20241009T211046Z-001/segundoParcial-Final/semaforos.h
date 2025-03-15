#ifndef _SEMAFOROS
#define _SEMAFOROS

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 33

int creo_semaforo();
void inicia_semaforo(int id_semaforo, int valor);
void levanta_semaforo(int id_semaforo);
void espera_semaforo(int id_semaforo);
void elimina_semaforo(int id_semaforo);

#endif
