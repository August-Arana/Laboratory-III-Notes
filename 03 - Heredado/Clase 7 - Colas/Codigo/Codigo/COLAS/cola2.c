#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#define CLAVE_BASE 33
#define SOY_PROCESO 2
#define DESTINATARIO 1


//
// Estructura para los mensajes que se quieren enviar y/o recibir. Deben llevar
// obligatoriamente como primer campo un long para indicar un identificador
// del mensaje. 
// Los siguientes campos son la información que se quiera transmitir en el  
// mensaje. Cuando más adelante, en el código, hagamos un cast a 
// (struct msgbuf *), todos los campos de datos los verá el sistema como
// un único (char *)
//

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long Id_Mensaje;
	int Dato_Numerico;
	char Mensaje[50];						//Numero de nevento
	
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

int enviar_mensaje(int id_Cola_Mensajes)
{
	//
	//	Se rellenan los campos del mensaje que se quiere enviar.
	//	El Id_Mensaje es un identificador del tipo de mensaje. Luego se podrá
	//	recoger aquellos mensajes de tipo 2.
	//	Dato_Numerico es un dato que se quiera pasar al otro proceso. Se pone, 
	//	por ejemplo 29.
	//	Mensaje es un texto que se quiera pasar al otro proceso.
	//
	mensaje Un_Mensaje;
	Un_Mensaje.Id_Mensaje = DESTINATARIO;
	Un_Mensaje.Dato_Numerico = 13;
	sprintf (Un_Mensaje.Mensaje, "------- Adios proceso %d ---------",DESTINATARIO);

	//
	//	Se envia el mensaje. Los parámetros son:
	//	- Id de la cola de mensajes.
	//	- Dirección al mensaje, convirtiéndola en puntero a (struct msgbuf *)
	//	- Tamaño total de los campos de datos de nuestro mensaje, es decir
	//	de Dato_Numerico y de Mensaje
	//	- Unos flags. IPC_NOWAIT indica que si el mensaje no se puede enviar
	//	(habitualmente porque la cola de mensajes esta llena), que no espere
	//	y de un error. Si no se pone este flag, el programa queda bloqueado
	//	hasta que se pueda enviar el mensaje.
	//

		
	return msgsnd (id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico)+sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT);
}		

int recibir_mensaje(int id_Cola_Mensajes)
{

	//
	//	Se recibe un mensaje del otro proceso. Los parámetros son:
	//	- Id de la cola de mensajes.
	//	- Dirección del sitio en el que queremos recibir el mensaje,
	//	convirtiéndolo en puntero a (struct msgbuf *).
	//	- Tamaño máximo de nuestros campos de datos. 
	//	- Identificador del tipo de mensaje que queremos recibir. En este caso
	//	se quiere un mensaje de tipo 2. Si ponemos tipo 2, se extrae el mensaje
	//	que se acaba de enviar en la llamada anterior a msgsnd().
	//	- flags. En este caso se quiere que el programa quede bloqueado hasta
	//	que llegue un mensaje de tipo 2. Si se pone IPC_NOWAIT, se devolvería
	//	un error en caso de que no haya mensaje de tipo 2 y el programa
	//	continuaría ejecutándose.
	//
	mensaje Un_Mensaje;
	int res;
		
	res = msgrcv (id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), 
			SOY_PROCESO, 0);

	printf("Recibido mensaje tipo: %d\n",SOY_PROCESO);
	printf("Dato_Numerico = %d\n", Un_Mensaje.Dato_Numerico);
	printf("Mensaje = %s\n", Un_Mensaje.Mensaje);

	

	return res;
}

int borrar_cola_de_mensajes(int Id_Cola_Mensajes){
	//
	//	Se borra y cierra la cola de mensajes.
	// IPC_RMID indica que se quiere borrar. El puntero del final son datos
	// que se quieran pasar para otros comandos. IPC_RMID no necesita datos,
	// así que se pasa un puntero a NULL.
	//
	msgctl (Id_Cola_Mensajes, IPC_RMID, (struct msqid_ds *)NULL);

}

int borrar_mensajes(int id_cola_mensajes)
{
	mensaje Un_Mensaje;
	int res;
	do
	{
		res = msgrcv (id_cola_mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), 
			0, IPC_NOWAIT);

	}while(res>0);
	return res;
}


int main()
{
	int id_cola_mensajes;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	//borrar los mensajes pendientes antes de comenzar
	borrar_mensajes(id_cola_mensajes);
	
	
	printf("\n---> soy proceso %d, espero para recibir un mensaje <---\n",SOY_PROCESO);

	recibir_mensaje(id_cola_mensajes);

	printf("\n---> soy proceso %d, envio un mensaje al proceso %d <---\n",SOY_PROCESO,DESTINATARIO);
	sleep(1);
	enviar_mensaje(id_cola_mensajes);
	
	borrar_cola_de_mensajes(id_cola_mensajes);

	return 0;
}


