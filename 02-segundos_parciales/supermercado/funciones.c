#include "funciones.h"
#include "stdlib.h"

int inNumeroAleatorio(int desde, int hasta) {
  return rand() % (hasta - desde + 1) + desde;
}
