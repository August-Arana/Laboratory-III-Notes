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
#include "semaforo.h"

int main(int arg, char *argv[]){
/* variables */
	int *memoria=NULL;
	int id_memoria;
	int id_semaforo;
	int done;
    int fin;
	int i;
    int nro_pateador;
    int nro_mensaje;
    int suceso;
    int goles_totales;
    hilo_pateadores datos_pateadores[5];
	mensaje msg;
	int id_cola_mensajes;
    
    /* inicializacion */
    nro_mensaje = 0;
    goles_totales = 0;
    suceso = 0;
    nro_pateador = 0;
	done=0;
	i=0;
    fin = 0;
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicio_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);
    for ( i = 0; i < CANTIDAD_PATEADORES; i++)
    {
        datos_pateadores[i].goles=0;
        
    }
    srand(time(NULL));

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[1] == 1)
     	{
         	levanta_semaforo(id_semaforo);
         	break;
     	}
      	else
      	{
         	levanta_semaforo(id_semaforo);
      	}
      	usleep(TIEMPO_ESPERA);
   	}

    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes,MSG_ARQUERO,&msg);
        nro_pateador = msg.rte-2;
        if (nro_pateador < 0 || nro_pateador >= 5) {
        printf("Error: índice de pateador fuera de rango: %d\n", nro_pateador);
        continue; 
        }
        nro_mensaje = msg.rte;
        switch (msg.evento)
        {

        case EVT_TIRO:
            suceso = inDevolverNumeroAleatorio(1,4);
            usleep(TIEMPO_ESPERA);
            if (suceso == 1)
            {
                enviar_mensaje(id_cola_mensajes,nro_mensaje,MSG_ARQUERO,EVT_GOL,"");
                goles_totales++;
                datos_pateadores[nro_pateador].goles++;
                printf("Gol de pateador %d\n",nro_pateador);

            }
            if (suceso == 2)
            {
                enviar_mensaje(id_cola_mensajes,nro_mensaje,MSG_ARQUERO,EVT_PALO,"");
                printf("Palo de pateador %d\n",nro_pateador);
            }
            if (suceso == 3)
            {
                enviar_mensaje(id_cola_mensajes,nro_mensaje,MSG_ARQUERO,EVT_TRAVESANO,"");
                printf("Travesaño de pateador %d\n",nro_pateador);
            }
            if (suceso == 4)
            {
                enviar_mensaje(id_cola_mensajes,nro_mensaje,MSG_ARQUERO,EVT_FUERA,"");
                printf("Fuera de pateador %d\n",nro_pateador);
            }

            
            break;
        
        }
       fin++;
        
        if (fin == 5)
        {
            printf("Todos Patearon\n");
            done = 1;
        }
    }
    printf("Goles Totales: %d\n",goles_totales);
    for (i = 0; i < 5; i++)
    {
        if (datos_pateadores[i].goles > 0)
        {
            printf("Gol del pateador %d\n",i);
        }
    }

    
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
    eliminar_cola_mensajes(id_cola_mensajes);
	

    return 0;

}
