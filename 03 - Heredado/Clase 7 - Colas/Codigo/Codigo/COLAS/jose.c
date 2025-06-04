#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#define CLAVE_BASE 33
#define LARGO_TMENSAJE 1024
#define DESDE 10
#define HASTA 20
#define INTERVALO 1

#define MSG_JOSE 		1
#define MSG_PEPITO		2
#define EVT_MENSAJE		1
#define EVT_FIN			2



typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long	long_dest; 						//Destinatario
	int 	int_rte;						//Remitente
	int 	int_evento;						//Numero de nevento
	char 	char_mensaje[LARGO_TMENSAJE];	//mensajse
};

key_t creo_clave(int r_clave)
{
	key_t clave;
	clave = ftok ("/bin/ls", r_clave);	
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave para memoria compartida\n");
		exit(0);
	}
	return clave;
}


int creo_id_cola_mensajes(int clave)
{
	int id_cola_mensajes = msgget (creo_clave(clave), 0600 | IPC_CREAT);
	if (id_cola_mensajes == -1)
	{
		printf("Error al obtener identificador para cola mensajes\n");
		exit (-1);
	}
	return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg)
{
	mensaje msg;
	msg.long_dest 	= rLongDest;
	msg.int_rte    	= rIntRte;
	msg.int_evento 	= rIntEvento;
	strcpy(msg.char_mensaje, rpCharMsg);
	printf("\t\t\t\tEnvio Mensaje   %s\n", msg.char_mensaje);
	return msgsnd (id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), IPC_NOWAIT);
}		

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg)
{
	mensaje msg;
	int res;
	res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg,  sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), 	rLongDest, 0);
	
	rMsg->long_dest 	= msg.long_dest;
	rMsg->int_rte    	= msg.int_rte;
	rMsg->int_evento 	= msg.int_evento;
	strcpy(rMsg->char_mensaje, msg.char_mensaje);
	return res;
}

int borrar_mensajes(int id_cola_mensajes)
{
	mensaje msg;
	int res;
	do
	{
		res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg,  sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), 	0, IPC_NOWAIT);
	}while(res>0);
	return res;
}

int main()
{
	int 		id_cola_mensajes;
	mensaje		msg;	
	msg.int_evento = 0;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	borrar_mensajes(id_cola_mensajes);

	printf("\nSOY DON JOSE\n");
	
	enviar_mensaje(id_cola_mensajes , MSG_PEPITO, MSG_JOSE, EVT_MENSAJE, "HOLA DON PEPITO");

	while( msg.int_evento!=EVT_FIN)
	{
		recibir_mensaje(id_cola_mensajes, MSG_JOSE, &msg);
		printf("Destino   %d\n", (int) msg.long_dest);
		printf("Remitente %d\n", msg.int_rte);
		printf("Evento    %d\n", msg.int_evento);
		printf("Mensaje   %s\n", msg.char_mensaje);
		switch (msg.int_evento)
		{
			case EVT_MENSAJE:
				printf("Recibi el EVT_MENSAJE\n");
				//printf("Mensaje   %s\n", msg.char_mensaje);
				sleep(INTERVALO);
				if(strcmp(msg.char_mensaje, "HOLA DON JOSE")==0)
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_JOSE, EVT_MENSAJE, "PASO USTED POR CASA");
				else if(strcmp(msg.char_mensaje, "POR SU CASA YO PASE")==0)
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_JOSE, EVT_MENSAJE, "VIO USTED A MI ABUELA");
				else if(strcmp(msg.char_mensaje, "A SU ABUELA YO LA VI")==0)
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_JOSE, EVT_FIN, "ADIOS DON PEPITO");
			break;
			case EVT_FIN:
				printf("Recibi el EVT_FIN\n");
			break;
			default:
				printf("\nEvento sin definir\n");
			break;
		}
		printf("------------------------------\n");
	}

	if(msg.int_evento!=EVT_FIN)	
		enviar_mensaje(id_cola_mensajes, MSG_PEPITO, MSG_JOSE, EVT_FIN, "");		

	return 0;
}


