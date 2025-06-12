#ifndef SEMAFOROS_H
#define SEMAFOROS_H

/**
 * Crea un semaforo
 * 
 * @param clave_base clave base para crear el semaforo
 * @param ruta ruta al archivo para crear la clave
 * @return
 */
int crear_semaforo(int clave_base, char *ruta);

/**
 * Inicializa un semaforo
 *
 * @param id_semaforo
 * @param valor 
 */
void inicializar_semaforo(int id_semaforo, int valor);

/**
 * Levanta un semaforo
 *
 * @param id_semaforo 
 */
void levantar_semaforo(int id_semaforo);

/**
 * Espera un semaforo
 *
 * @param id_semaforo
 */
void esperar_semaforo(int id_semaforo);

#endif
