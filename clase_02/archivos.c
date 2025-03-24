#include "stdio.h"
#include "archivos.h"

/*ACA usas un FP global de archivo, NO DE PROYECTO*/

FILE *fp;

int inAbrirArchivo(char *szNombre){
    /*Construir lo que necesites. El framework es tuyo!*/
    *fp = fopen(szNombre, "r");
    if(fp == NULL){
        printf("\n No se puede abrir el archivo!\n");
        return 1;
    }else{

    }
    return 0;
}

int inEscribirArchivo(char *szNombre){
    
    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }else{
        fprintf()
    }
    return 0
}
