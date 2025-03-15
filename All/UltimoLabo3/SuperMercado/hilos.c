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
#include "archivos.h"


void *hilos(void *parametro){


	int nro_caja;
    int total;
	int id_memoria;
	char cadena[50];
    char TotalCaja[50];
	char *producto=NULL;
	int cont;
	int id_cola_mensajes;
    int i;
	int done;

	hilo_caja *datos_caja;
    mensaje msg;
	done=0;
    cont=0;

	datos_caja=(hilo_caja*) parametro;
	nro_caja = datos_caja->nro_caja;
    total = datos_caja->total;

    
	id_cola_mensajes = datos_caja -> id_cola_mensajes;
	srand(time(NULL));
	borrar_mensajes(id_cola_mensajes);

    printf("Caja %d\n",nro_caja);
    sprintf(cadena,"Caja%d.txt",nro_caja);
    while(done==0)
    {   
        pthread_mutex_lock(&mutex);	
        
        enviar_mensaje(id_cola_mensajes,MSG_DERIVADOR,MSG_CAJA+nro_caja,EVT_CONSULTA,cadena);
        recibir_mensaje(id_cola_mensajes,MSG_CAJA+nro_caja,&msg);

        switch (msg.evento)
        {
        case EVT_NINGUNO:
                printf("No hay nadie en la caja %d\n",nro_caja);
            break;
        
        case EVT_CAJA:
            total+=atoi(msg.mensaje);
            if (inAbrirArchivo(cadena, "r") == -1) {
                printf("Error al abrir el archivo en modo lectura.\n");
                continue;
            }
            producto = inLeerArchivo();
            if (producto != NULL) {
                printf("%s", producto);
                free(producto);  
            }

            voCerrarArchivo();
            break;
        
        case EVT_FIN:
            if (!inAbrirArchivo(cadena, "w")) {
                    printf("Error al abrir archivo \n");
                    continue;
                }
            sprintf(TotalCaja,"Total Facturado por la caja %d: %d\n",nro_caja,total);
            printf("%s",TotalCaja);
            inEscribirArchivo(TotalCaja);
            voCerrarArchivo();
            done=1;
            break;
        
        }
        

    
		pthread_mutex_unlock(&mutex);
        sleep(5);
		
    }
    memset(cadena,0,sizeof(cadena));

    printf("El hilo %d ha terminado\n",nro_caja);
    
    pthread_exit(NULL);


}
