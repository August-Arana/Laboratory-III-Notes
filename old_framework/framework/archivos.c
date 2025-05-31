#include "stdio.h"
#include "archivos.h"

    /*Construir lo que necesites. El framework es tuyo!*/
FILE *fp;

int inAbrirArchivo(char *szNombre, char *mod){
    fp = fopen(szNombre, mod);

    if(fp == NULL){
        printf("\n No se puede abrir el archivo!\n");
        return 1;
    }
    return 0;
}

int inLeerArchivo(char *formato, char *valor){
    
    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }else{
        if(fscanf(fp,formato, valor) != 1 ){ /*valor va sin * porque es de tipo void*/
            printf("\n Error al leer el archivo\n");
            return 1;
        }
    }
    return 0;
}

int inEscribirArchivo( char *formato, char *valor){
    
    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }else{
        fprintf(fp, formato,valor); /*valor va con * porque no es de tipo void*/

    }
    return 0;
}

int inCerrarArchivo(){
    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }
    fclose(fp);
    fp = NULL;
    return 0;
}
