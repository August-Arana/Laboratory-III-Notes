#include "define.h"
#include "cola.h"
#include "funciones.h"
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int i, cantidad, done, alguien_acerto, pensado;
  int intentos[99] = {0};
  int posicion;

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;

  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  borrar_mensajes(id_cola_mensajes);

  cantidad = 1;
  done = 0;
  pensado = 0;
  alguien_acerto = 0;
  posicion = 0;

  pensado = inNumeroAleatorio(ADIVINADO_DESDE, ADIVINADO_HASTA);


  while (done == 0) {
    printf("Soy el pensador, estoy esperando un mensaje\n");
    recibir_mensaje(id_cola_mensajes, MSG_ADIVINADOR, &msg);
    printf("Soy el pensador, recibi un mensaje:\n");

    switch (msg.int_evento) {

        case EVT_INTENTO_ADIVINAR:
          printf("El jugador %d: quiere adivinar con %s\n", msg.int_rte -1, msg.char_mensaje);
          enviar_mensaje(id_cola_mensajes, msg.int_rte,
                         MSG_ADIVINADOR, EVT_INTENTO_ADIVINAR,
                         "no adivinaste");
          break;

        case EVT_FIN:
          break;

        default:
          printf("\nEvento sin definir\n");
          break;
    }




    if (g_control == 0) {
      /* g_control es como una turnera, segun el numero, es a quien le toca
       * jugar */
      g_control = cantidad;
      if (alguien_acerto == 0) {

        printf("Narrador: Nadie adivino el numero %d en esta ronda\n\n",
               pensado);

        printf("Numeros intentados:\n");
        for (i = 0; i < 99; i++) {
          if (intentos[i] != 0) {
            if (i == 0) {
              printf("%d", intentos[i]);
            } else {
              printf(", %d", intentos[i]);
            }
          }
        }
        printf("\n___________________\n\n");

      } else {
        done = 1;
      }
    }
    usleep(TIEMPO_BOLILLAS * 1000);
  };

  printf("JUEGO TERMINADO\n");
  return 0;
}
