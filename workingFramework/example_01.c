#include "cola.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  int id_cola = creo_id_cola_mensajes(1234);

  long destino = 2;
  int remitente = 1;
  int evento = 42;
  char mensaje_texto[] = "Hola desde proceso 1";

  if (enviar_mensaje(id_cola, destino, remitente, evento, mensaje_texto) ==
      -1) {
    perror("Error al enviar mensaje");
  } else {
    printf("Proceso 1: mensaje enviado\n");
  }

  return 0;
}
