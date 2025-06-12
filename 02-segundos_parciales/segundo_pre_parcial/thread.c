#include "archivos.h"
#include "cola.h"
#include "define.h"
#include "global.h"
#include "memoria.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*  */

void *ThreadCajeros(void *parametro) {
  /* Variables comunes */
  int *done;
  int cantidad;
  int total;
  int total_caja;

  /* Variables de mensajes */
  mensaje msg;
  char mensaje_final[LONGITUD];

  /* Variables de hilos */
  caj *datos_thread = (caj *)parametro;
  int nro_cajero;
  int id_cola_mensajes;

  /* Variables de Memoria */
  int *id_memoria;
  clt *cliente_activo;

  /* Variables de Archivos */
  char nombre_archivo[30];
  char para_escribir[100];

  /* Asignacion de variables */
  nro_cajero = datos_thread->nro_cajero;
  id_cola_mensajes = datos_thread->id_cola_mensajes;
  id_memoria = datos_thread->id_memoria;
  done = datos_thread->terminar;
  cliente_activo = (clt *)creo_memoria(sizeof(clt), id_memoria, CLAVEBASE);
  total_caja = 0;

  printf("\nSoy el cajero %d\n", nro_cajero + 1);
  sprintf(nombre_archivo, "Cajero-%d.txt", nro_cajero + 1);
  inAbrirArchivo(nombre_archivo, "w");
  inCerrarArchivo();
  /* enviar_mensaje: id_cola, destinatario, remitente(yo), evento, char_mensaje
   */
  /* recibir_mensaje:id_cola, destinatario(yo), mensaje */

  while (*done == 0) {
    /* El thread se queda esperando mensaje, cuando le llegue un mensajem recien
     * ahi hace un lock de mutex, con esto evito que el mutex quede bloqueado
     * antes de que llegue un mensaje fuera al revez, primero se bloquea el
     * mutex y el thread bloquea al resto de los threads
     * */
    recibir_mensaje(id_cola_mensajes, MSG_CAJERO + nro_cajero, &msg);
    printf("Soy el cajero, recibi un mensaje\n");
    printf("Soy el cajero, bloqueo mutex\n");
    pthread_mutex_lock(&mutex);

    /* Veo que hay adentro del mensaje */

    switch (msg.int_evento) {

    case EVT_CLT_INICIO:
      /* Tengo que procesar la compra del cliente */
      printf("\ncantidad de producots %s\n", msg.char_mensaje);
      printf("\nDescripcion: %s\n", cliente_activo->producto.descripcion);
      printf("\nPrecio: %d\n", cliente_activo->producto.precio);
      printf("\nCliente numero: %d\n", cliente_activo->id);

      cantidad = atoi(msg.char_mensaje);
      total = cliente_activo->producto.precio * cantidad;
      total_caja += total;
      sprintf(para_escribir, "Cliente%d compro %s gasto %d\nTotal Caja: %d\n\n",
              cliente_activo->id, cliente_activo->producto.descripcion, total,
              total_caja);
      inAbrirArchivo(nombre_archivo, "a");
      inEscribirArchivo("%s", para_escribir);
      inCerrarArchivo();

      enviar_mensaje(id_cola_mensajes, MSG_ADMIN, MSG_CAJERO + nro_cajero,
                     EVT_CLT_FIN, mensaje_final);
      break;

    case EVT_FINALIZAR:
      printf("\nCajero %d finalizando. Total global: %d\n", nro_cajero + 1, total_caja);
      sprintf(mensaje_final, "%d", total_caja);
      enviar_mensaje(id_cola_mensajes, MSG_ADMIN, MSG_CAJERO + nro_cajero,
                     EVT_FINALIZAR, mensaje_final);
      *done = 1;
      break;

    default:
      printf("\nEvento sin definir\n");
      break;
    }

    sleep(1);

    pthread_mutex_unlock(&mutex);

    sleep(1);
  };

  pthread_exit((void *)"Listo");
}
