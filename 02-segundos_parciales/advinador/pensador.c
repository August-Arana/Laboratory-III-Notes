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

  /* Asignacion de variables */
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  done = 0;
  pienso_un_numero = inNumeroAleatorio(ADIVINADO_DESDE, ADIVINADO_HASTA);

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  printf("Tienen que adivinar el %d\n\n", pienso_un_numero);
  while (done == 0) {
    printf("Soy el pensador, estoy esperando un mensaje\n");
    recibir_mensaje(id_cola_mensajes, MSG_PIENSO, &msg);
    printf("Recibi un mensaje:\n");

    switch (msg.int_evento) {

    case EVT_NUMERO:
      /* Abrir mensaje, sacar valor del string */
      sscanf(msg.char_mensaje, "Es el numero %d?", &intento);
      printf("Jugador %d quiere adivinar con %d\n", msg.int_rte - 1, intento);

      if (intento == pienso_un_numero) {

        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_ACERTO,
                       "Adivinaste! Felicitaciones");
        printf("\nAdivino!\n");
      } else {
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_NO_ACERTO,
                       "No adivinaste");
        printf("No adivino\n\n");
        break;
      }

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
