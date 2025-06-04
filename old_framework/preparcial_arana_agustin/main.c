#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "funciones.h"
#include "clave.h"

int main(int argc, char *argv[]){

/*    int i;
    int numero;
    inAbrirArchivo("./prueba.txt", "w");
    for (i = 0; i<10; i++){
        inEscribirArchivo("PRODUCTO-%02d\n", &i);
    }

    inCerrarArchivo();

    inAbrirArchivo("./prueba.txt", "r");
    for (i = 0; i<10; i++){
        inLeerArchivo("PRODUCTO-%02d\n",&numero);
        printf("El valor leido es %02d\n", numero);
    }

    inCerrarArchivo();
*/

    key_t clave = creo_clave();
    printf("La clave es %d\n", clave);

    return 0;
}
