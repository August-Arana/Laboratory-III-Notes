#include "funciones.h"
#include "define.h"
#include "stdlib.h"
#include <time.h>

int inNumeroAleatorio(int m, int n) {
  srand(time(0));
  return rand() % (n - m + 1) + m;
}

int obtener_saldo(clt clientes[], int id_cliente) {
  int i;
  for (i = 0; i < CANTIDAD_CLIENTES; i++) {
    if (clientes[i].id_cliente == id_cliente) {
      return clientes[i].saldo;
    }
  }
  return -1;
}

int depositar(clt clientes[], int id_cliente, int monto) {
  int i;
  for (i = 0; i < CANTIDAD_CLIENTES; i++) {
    if (clientes[i].id_cliente == id_cliente) {
      clientes[i].saldo += monto;
      return clientes[i].saldo;
    }
  }
  return -1;
}

int extraer(clt clientes[], int id_cliente, int monto) {
  int i;
  for (i = 0; i < CANTIDAD_CLIENTES; i++) {
    if (clientes[i].id_cliente == id_cliente) {
      if (monto > 0 && clientes[i].saldo >= monto && clientes[i].saldo > 0) {
        clientes[i].saldo -= monto;
      } else {
        return -1;
      }
      return clientes[i].saldo;
    }
  }
  return -1;
}
