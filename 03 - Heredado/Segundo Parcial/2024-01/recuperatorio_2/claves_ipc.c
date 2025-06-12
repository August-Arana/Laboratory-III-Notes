#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "claves_ipc.h"

key_t crear_clave_ipc(char *ruta, int id) {
    key_t clave;
    clave = ftok(ruta, id);
    if (clave == (key_t) -1) {
        printf("No se pudo crear la clave IPC\n");
        exit(-1);
    }
    return (clave);
}

key_t crear_clave_ipc_ruta_hardcodeada(int id) {
    return crear_clave_ipc("/bin/ls", id);
}

key_t crear_clave_ipc_hardcodeada(void) {
    return crear_clave_ipc("/bin/ls", 33);
}
