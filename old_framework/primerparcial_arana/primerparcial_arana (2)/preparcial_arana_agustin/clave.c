#include <stdlib.h>
#include <stdio.h>
#include "clave.h"
#include "define.h"

key_t creo_clave() {
    key_t clave;
    /*meter en def.h lo que se usa en ftok*/
    clave = ftok("/bin/ls", CLAVEBASE);
    if ( clave == (key_t)-1){
       printf("No puedo conseguir clave semaforo");
       exit(0);
    }
    return clave;
}
