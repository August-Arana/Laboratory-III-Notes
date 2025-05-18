#include "cola.h"
#include "define.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*  */

/* ojo que este main no tiene los parametros, esta mal */
int main() {
  /* Declaracion de variables a utilizar */
  int id_cola_mensajes;
  mensaje msg;
  int i;
  int saldo;
  int transaccion;
  clt clientes[CANTIDAD_CLIENTES];
  char mensaje_final[100];
  msg.int_evento = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  borrar_mensajes(id_cola_mensajes);

  printf("\nInicio sistema bancario\n");
  printf("\nINICIO Carga informacion de clientes\n");
  for (i = 0; i < CANTIDAD_CLIENTES; i++) {
    clientes[i].id_cliente = i;
    clientes[i].saldo = inNumeroAleatorio(-10000, 10000);
  }
  printf("\nFIN Carga informacion de clientes\n");

  /* enviar_mensaje: id_cola, destinatario, remitente, evento, char_mensaje */
  /* recibir_mensaje:id_cola, destinatario, mensaje */

  /* aca lo que puedo hacer en realidad es quedarme escuchando mensajes y recien
   * cuando algun cajero se presente, empezar a responder, ese cajero tiene que
   * presentarse con su id y luego se responde a ese id
   * */

  /* modificar despues */

  while (msg.int_evento != EVT_FIN || msg.int_rte != 99) {

    /* -------------- RECIBIR MENSAJES -------------- */
    /* primero recibir mensaje */
    recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);

    /* luego tomar una decision de que hacer con el mensaje */
    switch (msg.int_evento) {

    case EVT_MENSAJE:
      printf("El cliente %d ha iniciado sesion\n", msg.int_rte);
      enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_MENSAJE,
                     "Ingrese su consulta");
      break;
    case EVT_CONSULTA_SALDO:

      printf("El cliente %d quiere conocer su saldo actual\n", msg.int_rte);

      saldo = obtener_saldo(clientes, msg.int_rte);

      if (saldo != -1) {
        sprintf(mensaje_final, "Su saldo actual es de %d pesos", saldo);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_SALDO,
                       mensaje_final);
      } else {
        printf("El cliente %d no existe en la base de datos\n", msg.int_rte);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO,
                       EVT_RTA_SALDO_NOK,
                       "Error en consulta de saldo, cliente no registrado");
      }
      break;

    case EVT_DEPOSITO:

      printf("El cliente %d quiere depositar %s pesos en su cuenta\n",
             msg.int_rte, msg.char_mensaje);

      transaccion = atoi(msg.char_mensaje);
      saldo = depositar(clientes, msg.int_rte, transaccion);

      if (saldo != -1) {
        sprintf(mensaje_final,
                "Deposito Correcto. Su saldo final es de %d pesos", saldo);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO,
                       EVT_RTA_DEPOSITO_OK, mensaje_final);
      } else {

        printf("El cliente %d no existe en la base de datos\n", msg.int_rte);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO,
                       EVT_RTA_DEPOSITO_NOK,
                       "Error en consulta de saldo, cliente no registrado");
      }
      break;

    case EVT_EXTRACCION:
      printf("El cliente %d quiere extraer %s pesos de su cuenta\n",
             msg.int_rte, msg.char_mensaje);

      transaccion = atoi(msg.char_mensaje);
      saldo = extraer(clientes, msg.int_rte, transaccion);

      if (saldo != -1) {
          sprintf(mensaje_final,
                  "Extraccion correcta. Su saldo final es de %d pesos", saldo);

          enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO,
                         EVT_RTA_EXTRACCION_OK, mensaje_final);

      } else {
        printf("El cliente %d no existe en la base de datos\n", msg.int_rte);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO,
                       EVT_RTA_EXTRACCION_NOK,
                       "Error en consulta de saldo, cliente no registrado o saldo insuficiente");
      }
      break;

    case EVT_FIN:
      printf("El cliente %d se ha desconectado\n", msg.int_rte);
      enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_FIN, "");
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }
    printf("------------------------------\n");
  }

  if (msg.int_evento == EVT_FIN && msg.int_rte == 99)
    enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_FIN, "");

  return 0;
}
