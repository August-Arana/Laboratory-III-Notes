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


	int nro_ciudad;
	int id_memoria;
	char cadena[50];
	char nombre[100];
	int cont;
	int id_cola_mensajes;
    int i;
	int done;
    int viento;
    int temperatura;
    int lluvia;
	hilo_ciudad *datos_ciudad;
    mensaje msg;
	done=0;
    cont=0;
	datos_ciudad=(hilo_ciudad*) parametro;
	nro_ciudad = datos_ciudad->nro_ciudad;
    strcpy(nombre,datos_ciudad->Nombre);
	id_cola_mensajes = datos_ciudad -> id_cola_mensajes;
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);


    while(done==0)
    {   
        pthread_mutex_lock(&mutex);	
        
        viento = inDevolverNumeroAleatorio(3,25);
        temperatura = inDevolverNumeroAleatorio(5,25);
        lluvia = inDevolverNumeroAleatorio(0,100);
        sprintf(cadena, "Ciudad:%s,Viento:%d,Temperatura:%d,Lluvia:%d.",nombre,viento,temperatura,lluvia);
        printf("--------------------------------------------\n");
        printf("%s\n",cadena);
        printf("--------------------------------------------\n");
        enviar_mensaje(id_cola_mensajes,MSG_NOTICIERO,MSG_CIUDADES+nro_ciudad,EVT_INFO,cadena);
        memset(cadena,0,sizeof(cadena));
        cont++;
        if (cont == 7)
        {
            for (i = 0; i < CIUDADES; i++)
            {
                if (nro_ciudad == i)
                {
                    enviar_mensaje(id_cola_mensajes,MSG_NOTICIERO,MSG_CIUDADES+nro_ciudad,EVT_FIN,"Noticiero finalizado");
                    done=1;
                }
                
            }
        }
       

        
        memset(cadena,0,sizeof(cadena));

        	
		pthread_mutex_unlock(&mutex);
        sleep(1);
		
    }

    printf("El hilo %d ha terminado\n",nro_ciudad);
    
    pthread_exit(NULL);


}
