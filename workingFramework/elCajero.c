#include "cola.h"
#include "define.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  int id_cola_mensajes;
  mensaje msg;
  msg.int_evento = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  borrar_mensajes(id_cola_mensajes);

  printf("\nInicio sistema cajero\n");

  while (msg.int_evento != EVT_FIN) {
    recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);

    switch (msg.int_evento) {
    case EVT_MENSAJE:
      printf("\n%s\n", msg.char_mensaje);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_CONSULTA_SALDO, "Deseo conocer el saldo de mi cuenta");
      sleep(INTERVALO);
      break;
    case EVT_CONSULTA_SALDO:
      printf("\n%s\n", msg.char_mensaje);
      sleep(INTERVALO);
      break;

    case EVT_FIN:
      printf("Recibi el EVT_FIN\n");
      break;
    default:
      printf("\nEvento sin definir\n");
      break;
    }
    printf("------------------------------\n");
  }

  if (msg.int_evento != EVT_FIN)
    enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_FIN, "");

  return 0;
}
