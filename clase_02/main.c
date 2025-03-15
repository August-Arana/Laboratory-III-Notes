#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]){

    int inNumero =0;
    int *inDinNumero;
    char *szDin;

    inDinNumero = (int *) malloc(sizeof( int )*1);
    szDin = (char *) malloc(sizeof( char )*(30+1));


    printf("\n El nombre del programa es: %s", argv[0]);
    if(argc == 2 ){
        inNumero = atoi(argv[1]);
    }

    //
    /*----------*/
    szDin[0]='F';
    szDin[1]='R';
    strcpy(&szDin[2],"pepe");
    //Un puntero de un lado es lo mismo que un corchete del otro, investigar

    printf("\n Muestro string Dinamico: %s - %02x \n", szDin, &szDin);
    printf("\n Entero estatico: %d - %02x,\n", inNumero, &inNumero);

    voMostrar(&inNumero);

    *inDinNumero = 10;

    printf("\n Entero Din: %d - %d - %02x", inDinNumero, *inDinNumero, &inDinNumero);

    *inDinNumero = 66;
    return 0;
}
