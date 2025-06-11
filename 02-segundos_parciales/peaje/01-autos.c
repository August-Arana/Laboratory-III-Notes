#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "memoria.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int done;
  int cantidad_autos;
  int cantidad_lanes;
  int autos_generados;
  int via_aleatoria;
  int tiempo_espera;
  int i;

  /* Variables de mensajes */
  int id_cola_mensajes;
  char contenido_mensaje[100];

  if (argc > 1) {
    cantidad_lanes = atoi(argv[1]);
    cantidad_autos = atoi(argv[2]);
  } else {
    cantidad_lanes = 1;
    cantidad_autos = 100;
  }

  /* Asignacion de variables */
  done = 0;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  srand(time(0));

  /* Falta corroborar limpiado inicial y final de memoria */

  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0) {
    printf("Soy el generador de autos, voy a crear autos\n");
    autos_generados = inNumeroAleatorio(1, 5);
    via_aleatoria = inNumeroAleatorio(0, cantidad_lanes - 1);

    sprintf(contenido_mensaje, "%d", autos_generados);
    if (cantidad_autos > 0) {

      /* Modificar destino de mensaje */
      enviar_mensaje(id_cola_mensajes, MSG_VIA + via_aleatoria, MSG_AUTOS,
                     EVT_VEHICULOS, contenido_mensaje);
      cantidad_autos -= autos_generados;

    } else {

      autos_generados += cantidad_autos;

      for (i = 0; i < cantidad_lanes; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_VIA + i, MSG_AUTOS, EVT_FINALIZA,
                       contenido_mensaje);
      }

      done = 1;
    }

    printf("Quedan %d autos", cantidad_autos);

    /* Seteo tiempo espera */
    tiempo_espera = inNumeroAleatorio(100, 500);

    usleep(tiempo_espera * 1000);
  };

  printf("NO HAY MAS AUTOS!\n");
  return 0;
}
