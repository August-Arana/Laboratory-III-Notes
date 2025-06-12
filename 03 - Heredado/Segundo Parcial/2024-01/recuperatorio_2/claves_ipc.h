#ifndef CLAVES_IPC_H
#define CLAVES_IPC_H

#include <sys/types.h>

/**
 * Crea una clave de un archivo y un numero
 * @param ruta Ruta al archivo
 * @param id Identificador
 * @return Clave IPC
 */
key_t crear_clave_ipc(char *ruta, int id);

/**
 * Crea una clave hardcodeada con /bin/ls y un id provisto por el usuario
 * @param id Identificdor
 * @return clave IPC
 */
key_t crear_clave_ipc_ruta_hardcodeada(int id);

/**
 * Crea una clave hardcodeada con /bin/ls y parametro 33
 * @return
 */
key_t crear_clave_ipc_hardcodeada(void);


#endif
