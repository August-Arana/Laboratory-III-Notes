#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int done;
  int pienso_un_numero;

  /* Variables para threads */
  int intento;

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;
  char contenido_mensaje[99]; /* TODO Limpiar contenido inicial*/

  /* Asignacion de variables */
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  done = 0;
  pienso_un_numero = inNumeroAleatorio(ADIVINADO_DESDE, ADIVINADO_HASTA);

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0) {
    printf("Soy el pensador, estoy esperando un mensaje\n");
    recibir_mensaje(id_cola_mensajes, MSG_PIENSO, &msg);
    printf("Soy el pensador, recibi un mensaje:\n");

    switch (msg.int_evento) {

        case EVT_NUMERO:
          printf("%s\n", msg.char_mensaje);
          /* Abrir mensaje, sacar valor del string */
          sscanf(contenido_mensaje, "Es el numero %d ?\n", &intento);
          if (intento == pienso_un_numero) {

            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_ACERTO,
                           "Adivinaste! Felicitaciones");
          } else {
          }
          enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_NO_ACERTO,
                         "No adivinaste");
          break;

        case EVT_FINALIZAR:
          done = 1;
          printf("El jugador %d ha ganado\n", msg.int_rte);
          break;

        default:
          printf("\nEvento sin definir\n");
          break;
    }

    usleep(3000);
  };

  printf("JUEGO TERMINADO\n");
  return 0;
}
