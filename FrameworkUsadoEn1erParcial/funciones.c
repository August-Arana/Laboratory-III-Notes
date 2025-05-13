#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "funciones.h"
#include <time.h>

int inNumeroAleatorio(int m, int n){
    srand(time(0));
    return rand() % (n-m+1) + m;
}
