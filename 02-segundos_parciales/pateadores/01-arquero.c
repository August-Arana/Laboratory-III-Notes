#include "cola.h"
#include "define.h"
#include "funciones.h"
#include "memoria.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Variables comunes */
  int done;
  int cantidad_productos;
  int cliente_activo_id;
  char descripcion[LONGITUD];

  /* Variables para threads */
  int intento;

  /* Variables de mensajes */
  int id_cola_mensajes;
  mensaje msg;
  char contenido_mensaje[100];

  /* Variables de memoria */
  int id_memoria;
  int cajero_destino;

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  /* Asignacion de variables */
  done = 0;
  cliente_activo_id = 1;
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);

  /* Borrar los mensajes anteriores, para empezar de 0 */
  borrar_mensajes(id_cola_mensajes);

  srand(time(0));

  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (done == 0) {
    printf("Soy el derivador, voy a crear cliente\n");
    printf("Ingrese descripcion del producto:\n");
    scanf("%s", descripcion);
    cantidad_productos = inNumeroAleatorio(1, 20);
    printf("El cliente %d quiere %d de %s\n", cliente_activo_id,
           cantidad_productos, descripcion);

    cliente_activo->id = cliente_activo_id;
    cliente_activo->producto.precio = 100 + (cantidad_productos * 250);
    strcpy(cliente_activo->producto.descripcion, descripcion);

    cliente_activo_id++;

    if (cantidad_productos < 6) {
      cajero_destino = 0;
    } else if (cantidad_productos >= 6 && cantidad_productos <= 10) {
      cajero_destino = 1;
    } else {
      cajero_destino = 2;
    }

    sprintf(contenido_mensaje, "%d", cantidad_productos);

    enviar_mensaje(id_cola_mensajes, MSG_CAJERO + cajero_destino, MSG_ADMIN,
                   EVT_CLT_INICIO, contenido_mensaje);

    recibir_mensaje(id_cola_mensajes, MSG_ADMIN, &msg);

    switch (msg.int_evento) {

    case EVT_CLT_FIN:
      /* Abrir mensaje, sacar valor del string */
      sscanf(msg.char_mensaje, "%d", &intento);
      printf("\nEl cliente %d termino la compra en el cajero %d\n",
             cliente_activo->id, msg.int_rte - 1);

      break;

    case EVT_FINALIZAR:
      printf("El jugador %d ha ganado\n", msg.int_rte);
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }

    usleep(3000);
  };

  shmdt((char *)cliente_activo);
  shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

  printf("JUEGO TERMINADO\n");
  return 0;
}
