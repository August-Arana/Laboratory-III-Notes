#include <stdio.h>
#include <unistd.h>
#include "cola.h"
#include "define.h"

int main() {
  int id_cola_mensajes;
  mensaje msg;
  msg.int_evento = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  borrar_mensajes(id_cola_mensajes);

  printf("\nInicio sistema bancario\n");

  enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_MENSAJE,
                 "Puede iniciar sesion en el cajero");

  while (msg.int_evento != EVT_FIN) {
    recibir_mensaje(id_cola_mensajes, MSG_CAJERO, &msg);
    switch (msg.int_evento) {
    case EVT_CONSULTA_SALDO:
      printf("Recibi el EVT_CONSULTA_SALDO\n");
      sleep(INTERVALO);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CAJERO, EVT_CONSULTA_SALDO, "Su saldo actual es de 500 pesos");
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

