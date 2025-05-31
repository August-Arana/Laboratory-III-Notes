#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "funciones.h"
#include "clave.h"

int main(int argc, char *argv[]){

    key_t clave = creo_clave();
    printf("La clave es %d\n", clave);

    return 0;
}
