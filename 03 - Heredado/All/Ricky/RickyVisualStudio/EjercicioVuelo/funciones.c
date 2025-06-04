#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "funciones.h"



int inDevolverNumeroAleatorio(int inDesde,int inHasta)
{


    int inValorAleatorio=0;
    inValorAleatorio=rand()%(inHasta-inDesde+1)+inDesde;

    return inValorAleatorio;


}

void convertirAMayusculas(char *cadena) {
    while (*cadena) {
        *cadena = toupper((unsigned char) *cadena);
        cadena++;
    }
}
