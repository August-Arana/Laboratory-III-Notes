#include <stdlib.h>
#include <time.h>
#include "aleatorios.h"

/* Genera un numero aleatorio */
int generar_aleatorio(int desde, int hasta)
{
    return (rand() % (hasta - desde + 1)) + desde;
}

/* Inicializa la semilla para generar aleatorios */
void inicialiazar_aleatorios()
{
    srand(time(NULL));
}

