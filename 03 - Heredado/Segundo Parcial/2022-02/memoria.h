#ifndef _MEMORIA_H
#define _MEMORIA_H

void *creo_memoria(int size, int *r_id_memoria, int clave_base);
void libero_memoria(void *memoria);
void borro_memoria(int id_memoria);

#endif

