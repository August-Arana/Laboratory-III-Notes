#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/ipc.h"
#include "sys/msg.h"
#include "cola.h"
#include "clave.h"
#include "def.h"

int inCreo_id_cola_mensajes(int clave)
{
    int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
    
    if (id_cola_mensajes == -1)
    {
        printf("Error al obtener identificador para cola mensajes\n");
        exit(-1);
    }
    return id_cola_mensajes;
}


int inEnviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char *rpCharMsg)
{

    mensaje msg;
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;
    strcpy(msg.char_mensaje, rpCharMsg);
    return msgsnd(id_cola_mensajes, &msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), IPC_NOWAIT);

}


int inRecibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg)
{
	int res;
	res = msgrcv(id_cola_mensajes, rMsg, sizeof(*rMsg) - sizeof(rMsg->long_dest), rLongDest, 0);
    	return res;
}


int inBorrar_mensajes(int id_cola_mensajes)
{
    mensaje msg;
    int res;
    do
    {
        res = msgrcv(id_cola_mensajes, &msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}
