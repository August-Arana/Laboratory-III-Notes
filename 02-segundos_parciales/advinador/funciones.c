#include "funciones.h"
#include "stdlib.h"
#include <time.h>

int inNumeroAleatorio(int m, int n) {
  srand(time(0));
  return rand() % (n - m + 1) + m;
}
