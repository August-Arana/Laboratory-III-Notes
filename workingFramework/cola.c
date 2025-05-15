#include "cola.h"
#include "clave.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

/* lo primero que se hace es leer todos los mensjaes de la cola, esto es para
 * borrarlos, es decir, lo primero que siempre haces es LEER TODO */
/*
 * Esto, como siempre, va a formar parte de tu framework
 * */

int creo_id_cola_mensajes(int clave) {
  int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
  if (id_cola_mensajes == -1) {
    printf("Error al obtener identificador para cola mensajes\n");
    exit(-1);
  }
  return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char *rpCharMsg) {
  mensaje msg;
  msg.long_dest = rLongDest;
  msg.int_rte = rIntRte;
  msg.int_evento = rIntEvento;
  strcpy(msg.char_mensaje, rpCharMsg);
  return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg,
                sizeof(msg.int_rte) + sizeof(msg.int_evento) +
                    sizeof(msg.char_mensaje),
                IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg) {
  mensaje msg;
  int res;
  res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), rLongDest, 0);

  rMsg->long_dest = msg.long_dest;
  rMsg->int_rte = msg.int_rte;
  rMsg->int_evento = msg.int_evento;
  strcpy(rMsg->char_mensaje, msg.char_mensaje);

  return res;
}
