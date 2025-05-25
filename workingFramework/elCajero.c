#include "cola.h"
#include "define.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Declaracion de variables a utilizar */
  int id_cola_mensajes;
  int cliente_id;
  int opcion;
  int importe;
  char contenido_mensaje[100];
  mensaje msg;
  msg.int_evento = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  borrar_mensajes(id_cola_mensajes);

  printf("\nInicio Cajero Automatico\n");
  printf("\nBienvenido!\n");
  printf("Ingrese su número de cliente: ");
  scanf("%d", &cliente_id);

  /* enviar_mensaje: id_cola, destinatario, remitente, evento, char_mensaje */
  /* recibir_mensaje:id_cola, destinatario, mensaje */

  /* En este caso lo que tendria que hacer es que
   * ni bien el cajero inicia sesion, le pide permiso al banco para entrar
   * */

  /* modificar despues */

  enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id, EVT_MENSAJE,
                 "Quiero Iniciar sesion");

  while (msg.int_evento != EVT_FIN) {

    /* -------------- RECIBIR MENSAJES -------------- */
    /* primero recibir mensaje */
    recibir_mensaje(id_cola_mensajes, cliente_id, &msg);

    /* luego tomar una decision de que hacer con el mensaje */
    switch (msg.int_evento) {
    case EVT_MENSAJE:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_SALDO:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_SALDO_NOK:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_DEPOSITO_OK:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_DEPOSITO_NOK:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_EXTRACCION_OK:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_RTA_EXTRACCION_NOK:
      printf("\n%s\n", msg.char_mensaje);
      break;

    case EVT_FIN:
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }
    printf("------------------------------\n");

    /* Luego, darle opciones al usuario de que desea hacer */
    /* -------------- ENVIAR MENSAJES -------------- */
    if (msg.int_evento != EVT_FIN) {
      printf("\n--- MENU ---\n");
      printf("1. Consultar saldo\n");
      printf("2. Depositar\n");
      printf("3. Extraer\n");
      printf("4. Salir\n");
      printf("Seleccione una opción: ");
      scanf("%d", &opcion);

      switch (opcion) {
      case 1:
        enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id,
                       EVT_CONSULTA_SALDO, "Quiero conocer mi saldo");
        break;

      case 2:
        printf("\nIngrese el importe a depositar: ");
        scanf("%d", &importe);
        sprintf(contenido_mensaje, "%d", importe);
        enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id, EVT_DEPOSITO,
                       contenido_mensaje);
        break;

      case 3:
        printf("\nIngrese el importe a extraer: ");
        scanf("%d", &importe);
        sprintf(contenido_mensaje, "%d", importe);
        enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id, EVT_EXTRACCION,
                       contenido_mensaje);
        break;

      case 4:
        enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id, EVT_FIN,
                       "Quiero terminar sesion");
        break;

      default:
        printf("Opción inválida.\n");
        break;
      }
    }
  }

  if (msg.int_evento == EVT_FIN)
    enviar_mensaje(id_cola_mensajes, MSG_BANCO, cliente_id, EVT_FIN, "");

  return 0;
}
