#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "funciones.h"

void voMostrar(int *num){

    printf("\nvoMostrar\n");
    *num = 55; //Si, se esta pasando por referencia, pero porque es una variable dinamica
    printf("\nMuestro numero que es valor de la direcion %d", num);
    printf("\nMuestro valor, valor en hexa y direccion: %d %02x, %02x", *num, *num, &num);
    printf("\nFin voMostrar\n");
    // %02x muestra valores en hexa
    //
}
