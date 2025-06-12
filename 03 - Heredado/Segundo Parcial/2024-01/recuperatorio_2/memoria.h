#ifndef MEMORIA_H
#define MEMORIA_H

#include <sys/ipc.h>

/**
 * Crea memoria compartida
 * @param size tamaño de la memoria
 * @param r_id_memoria id de la memoria compartida
 * @param clave clave de la memoria compartida
 * @return Memoria compartida creada o NULL si no se pudo crear
 */
void *crear_memoria(int size, int *r_id_memoria, key_t clave);

/**
 * Crea memoria compartida
 * @param size tamaño de la memoria
 * @param r_id_memoria id de la memoria compartida
 * @return Memoria compartida creada o NULL si no se pudo crear
 */
void *crear_memoria_hardcodeada(int size, int *r_id_memoria);

/**
 * Libera la memoria compartida
 * @param memoria Memoria a liberar
 * @param id_memoria id de la memoria
 */
void liberar_memoria(void *memoria, int id_memoria);

#endif
