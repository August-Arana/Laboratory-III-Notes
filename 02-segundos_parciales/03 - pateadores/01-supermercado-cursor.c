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
  int done = 0;
  int cantidad_productos = 0;
  int cliente_activo_id = 1;
  char descripcion[LONGITUD] = {0};

  /* Variables para threads */
  int intento = 0;

  /* Variables de mensajes */
  int id_cola_mensajes = -1;
  mensaje msg = {0};
  char contenido_mensaje[100] = {0};

  /* Variables de memoria */
  int id_memoria = -1;
  clt *cliente_activo = NULL;
  int cajero_destino = 0;

  /* Semaforo memoria */
  semaforo_de_memoria(1);

  /* Asignacion de variables */
  id_cola_mensajes = creo_id_cola_mensajes(CLAVEBASE);
  if (id_cola_mensajes == -1) {
    printf("Error al crear cola de mensajes\n");
    return 1;
  }

  cliente_activo = (clt *)creo_memoria(sizeof(clt), &id_memoria, CLAVEBASE);
  if (cliente_activo == NULL) {
    printf("Error al crear memoria compartida\n");
    return 1;
  }

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

  /* Limpieza final */
  if (cliente_activo != NULL) {
    shmdt((char *)cliente_activo);
  }
  if (id_memoria != -1) {
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
  }
  if (id_cola_mensajes != -1) {
    borrar_mensajes(id_cola_mensajes);
  }

  printf("JUEGO TERMINADO\n");
  return 0;
}
