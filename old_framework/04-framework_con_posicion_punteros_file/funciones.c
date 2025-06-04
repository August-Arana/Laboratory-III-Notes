#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "funciones.h"
#include <time.h>

void voMostrar(int *num){
    printf("\nvoMostrar\n");
    *num = 55; 
    printf("\nMuestro numero que es valor de la direcion %d", num);
    printf("\nMuestro valor, valor en hexa y direccion: %d %02x, %02x", *num, *num, &num);
    printf("\nFin voMostrar\n");
}

int inNumeroAleatorio(int m, int n){
    srand(time(0));
    return rand() % (n-m+1) + m;
}
