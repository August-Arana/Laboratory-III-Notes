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
	int pasos_totales;
	int nro_animal;
    int fin;
	int i;
	
	mensaje msg;
	int id_cola_mensajes;

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

  	while (TRUE)
  	{
      		espera_semaforo(id_semaforo);
     	if (memoria[1] = 1)
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
        recibir_mensaje(id_cola_mensajes,MSG_CARRERA,&msg);
        
        switch (msg.evento)
        {
        case EVT_CORRO:

            if (msg.rte == 2)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Perro ha avansado un total de %d pasos\n", pasos_totales);
                vueltasPerro++;
            }
            if (msg.rte == 3)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Gato ha avansado un total de %d pasos\n", pasos_totales);
                vueltasGato++;
            }
            if (msg.rte == 4)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Conejo ha avansado un total de %d pasos\n", pasos_totales);
                vueltasConejo++;
            
            }
            
            


            break;
        
        case EVT_FIN:
            if (msg.rte == 2)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Perro ha llegado\n");
                fin ++;
            }
            if (msg.rte == 3)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Gato ha llegado\n");
                fin ++;
            }
            if (msg.rte == 4)
            {
                pasos_totales = atoi(msg.mensaje);
                printf("El Conejo ha llegado\n");
                fin ++;
            }
            break;
        }
        if (fin == 3)
        {
            printf("Todos llegaron\n");
            done = 1;
        }
    }
    printf("Carrera terminada\n");
    
    if (vueltasPerro < vueltasGato && vueltasPerro < vueltasConejo)
    {
        printf("El perro ha ganado\n");
    }
    if (vueltasGato < vueltasPerro && vueltasGato < vueltasConejo)
    {
        printf("El gato ha ganado\n");
    }
    if (vueltasConejo < vueltasPerro && vueltasConejo < vueltasGato)
    {
        printf("El conejo ha ganado\n");
    }
    else
    {
        printf("Empate\n");
    }

    vueltasConejo = 0;
    vueltasGato = 0;
    vueltasPerro = 0;
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
	

    return 0;

}
