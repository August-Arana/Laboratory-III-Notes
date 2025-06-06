#include <stdlib.h>
#include <stdio.h>
#include "clave.h"

key_t creo_clave(int claveBase) {
    key_t clave;
    clave = ftok("/bin/ls", claveBase);
    if ( clave == (key_t)-1){
       printf("No puedo conseguir clave semaforo");
       exit(0);
    }
    return clave;
}
