#include "stdio.h"
#include "archivos.h"
#include "string.h"

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

    int resultado;
    resultado = fscanf(fp,formato, valor); /* valor va sin * porque es de tipo void*/

    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }else{

        if(resultado == EOF){
            return -1;
        } else if(resultado != 1 ){ 
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

int inLeerLineaPorLinea(char *cadena, int largo){
    if(fp == NULL){
        printf("\n No existe el archivo o no se ha abierto!\n");
        return 1;
    }
    
    if(fgets(cadena, largo, fp) == NULL){
        cadena[strcspn(cadena, "\n")] = '\0';
        return -1;
    } 
    
    return 0;
}

long obtenerPosicionPuntero(){
    if(fp == NULL){
        printf("Archivo no abierto\n");
        return 1;
    }

    return ftell(fp);
}

int inIrAPosicion(long pos){
    if(fp == NULL){
        printf("Archivo no abierto\n");
        return 1;
    }
    
    return fseek(fp,pos,SEEK_SET);
}
