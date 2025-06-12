#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "colas.h"
#include "claves_ipc.h"

int creo_id_cola_mensajes(int clave) {
    int id_cola_mensajes = msgget(crear_clave_ipc_ruta_hardcodeada(clave), 0600 | IPC_CREAT);
    if (id_cola_mensajes == -1) {
        printf("Error al obtener identificador para cola mensajes\n");
        exit(-1);
    }
    return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long destinatario, int remitente, int evento, char *char_msg) {
    t_mensaje msg;
    msg.destinatario = destinatario;
    msg.remitente = remitente;
    msg.evento = evento;
    strcpy(msg.mensaje, char_msg);
    return msgsnd(id_cola_mensajes, (struct msgbuf *) &msg, sizeof(msg.remitente) + sizeof(msg.evento) + sizeof(msg.mensaje), IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long destinatario, t_mensaje *mensaje) {
    t_mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *) &msg, sizeof(msg.remitente) + sizeof(msg.evento) + sizeof(msg.mensaje), destinatario, 0);

    mensaje->destinatario = msg.destinatario;
    mensaje->remitente = msg.remitente;
    mensaje->evento = msg.evento;
    strcpy(mensaje->mensaje, msg.mensaje);
    return res;
}

int borrar_mensajes(int id_cola_mensajes) {
    t_mensaje msg;
    int res;
    do {
        res = msgrcv(id_cola_mensajes, (struct msgbuf *) &msg, sizeof(msg.remitente) + sizeof(msg.evento) + sizeof(msg.mensaje), 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}

int borrar_cola_de_mensajes(int id_cola_mensajes) {
    msgctl(id_cola_mensajes, IPC_RMID, (struct msqid_ds *) NULL);
    return 0;
}
