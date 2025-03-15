#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <def.h>
#include <funciones.h>
#include <time.h>
#include <archivo.h>
#include <memoria.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <semaforo.h>
#include <thread.h>
#include <global.h>
#include <pthread.h> 



int main(int argc,char *argv[]){
	
	pthread_t idHilo;
	pthread_attr_t 	atributos;
	int i;
	char* valorDevuelto = NULL;


	if(argc != 0){
	
		printf("Hubo un error con los parametros\n");

	}

	pthread_mutex_init (&mutex, NULL);
	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, funcionThread, NULL)!= 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}
	
	for(i=0; i<CANTIDAD; i++)
	{
		pthread_mutex_lock (&mutex);
		printf("Soy el padre y tengo el mutex\n");
		sleep (1);
		pthread_mutex_unlock (&mutex);
		sleep(1);
	}
	
	printf ("Padre : Espero al thread\n");
	pthread_join(idHilo, (void **)&valorDevuelto);
	printf ("Padre : Ya ha terminado el thread\n");
	printf ("Padre : devuelve \"%s\"\n", valorDevuelto);
	
	return 0;

}
