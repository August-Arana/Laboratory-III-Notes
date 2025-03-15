#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/ipc.h"
#include "def.h"
#include "unistd.h"
#include "memoria.h"
#include "sys/shm.h"
#include "sys/msg.h"
#include "clave.h"
#include "semaforo.h"
#include "global.h"
#include "cola.h"
#include "errno.h"  


int creo_id_cola_mensajes(int clave) {
    int id_cola_mensajes;
    id_cola_mensajes = msgget(creo_clave(CLAVE_BASE), 0600 | IPC_CREAT);
    if (id_cola_mensajes == -1) {
        perror("Error al obtener identificador para cola de mensajes");
        exit(-1);
    }
    return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg) {
    mensaje msg;
    msg.dest = rLongDest;
    msg.rte = rIntRte;
    msg.evento = rIntEvento;
    strncpy(msg.mensaje, rpCharMsg, sizeof(msg.mensaje) - 1);
    msg.mensaje[sizeof(msg.mensaje) - 1] = '\0';  
    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.evento) + sizeof(msg.mensaje), IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg) {
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.rte) + sizeof(msg.evento) + sizeof(msg.mensaje), rLongDest, 0);
    if (res == -1) {
        perror("Error al recibir mensaje");
        return -1;
    }
    rMsg->dest = msg.dest;
    rMsg->rte = msg.rte;
    rMsg->evento = msg.evento;
    strcpy(rMsg->mensaje, msg.mensaje);
    return res;
}

int borrar_mensajes(int id_cola_mensajes) {
    mensaje msg;
    int res;
    do {
        res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.rte) + sizeof(msg.evento) + sizeof(msg.mensaje), 0, IPC_NOWAIT);
    } while (res > 0);

    if (res == -1 && errno != ENOMSG) {
        perror("Error al vaciar mensajes de la cola");
        return -1;
    }

    return 0;  
}

int eliminar_cola_mensajes(int id_cola_mensajes) {
    if (msgctl(id_cola_mensajes, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar la cola de mensajes");
        return -1;
    }
    
    return 0;
}
