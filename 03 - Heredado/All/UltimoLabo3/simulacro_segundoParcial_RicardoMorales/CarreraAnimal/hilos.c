#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "time.h"
#include "pthread.h"
#include "clave.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "cola.h"
#include "funciones.h"
#include "hilos.h"

void *hilos(void *parametro){


	int nro_animal;
	int id_memoria;
	char cadena[50];
	
	int pasos_totales=0;
    int pasos=0;
	int cont;
	int id_cola_mensajes;
	int done;
	hilo_animal *datos_animal;

	done=0;
	datos_animal=(hilo_animal*) parametro;
	nro_animal = datos_animal->nro_animal;
	id_cola_mensajes = datos_animal -> id_cola_mensajes;
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);


    while(done==0)
    {
        pthread_mutex_lock(&mutex);	
        
        if (nro_animal == 0)
        {
            pasos=inDevolverNumeroAleatorio(3,8);
            printf("El perro Avanza %d pasos\n",pasos);
            pasos_totales += pasos;
            sprintf(cadena, "%d",pasos_totales);
            printf(" llevo un total de %s pasos\n", cadena);
            enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_PERRO,EVT_CORRO,cadena);
        }

        if (nro_animal == 1)
        {
            pasos=inDevolverNumeroAleatorio(1,10);
            printf("El Gato Avanza %d pasos\n",pasos);
            pasos_totales += pasos;
            sprintf(cadena, "%d",pasos_totales);
            printf(" llevo un total de %s pasos\n", cadena);
            enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_GATO,EVT_CORRO,cadena);
        }

        if (nro_animal == 2)        
        {
            pasos=inDevolverNumeroAleatorio(4,9);
            printf("El Conejo Avanza %d pasos\n",pasos);
            pasos_totales += pasos;
            sprintf(cadena, "%d",pasos_totales);
            printf(" llevo un total de %s pasos\n", cadena);
            enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_CONEJO,EVT_CORRO,cadena);
        }
        memset(cadena,0,sizeof(cadena));
        if (pasos_totales >= 50)
        {  
           if (nro_animal == 0)
           {
                printf("El Perro ha llegado a la meta\n");
                sprintf(cadena, "%d",pasos_totales);
                enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_PERRO,EVT_FIN,cadena);
           }

           if (nro_animal == 1)
           {
                printf("El Gato ha llegado a la meta\n");
                sprintf(cadena, "%d",pasos_totales);
                enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_GATO,EVT_FIN,cadena);
           }

           if (nro_animal == 2)        
           {
                printf("El Conejo ha llegado a la meta\n");
                sprintf(cadena, "%d",pasos_totales);
                enviar_mensaje(id_cola_mensajes,MSG_CARRERA,MSG_CONEJO,EVT_FIN,cadena);
           }
            done = 1;
        }

        
        memset(cadena,0,sizeof(cadena));

        	
		
		pthread_mutex_unlock(&mutex);
		usleep(TIEMPO_ESPERA);
    }

    printf("El hilo %d ha terminado\n",nro_animal);
    
    pthread_exit(NULL);


}
