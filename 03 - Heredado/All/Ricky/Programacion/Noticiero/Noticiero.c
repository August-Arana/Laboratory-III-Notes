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
    int j;
    int cont;
    int numero_ciudad;

    hilo_ciudad datos_ciudad[10];
	mensaje msg;
	int id_cola_mensajes;
	done=0;
	i=0;
    fin = 0;
    cont = 0;
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicio_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);
    for ( i = 0; i < CIUDADES; i++)
    {
        datos_ciudad[i].nro_ciudad=i;
        datos_ciudad[i].viento=0;
        datos_ciudad[i].temperatura=0;
        datos_ciudad[i].lluvia=0;
    }
    

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
       
        recibir_mensaje(id_cola_mensajes,MSG_NOTICIERO,&msg);
        numero_ciudad = msg.rte-2;
        
        switch (msg.evento)
        {
        case EVT_INFO:

            if (numero_ciudad == datos_ciudad[i].nro_ciudad)
            {
                filtrarContenidoPorClave(msg.mensaje, "Ciudad", datos_ciudad[i].Nombre);
                filtrarContenidoPorClaveAEntero(msg.mensaje, "Viento", &datos_ciudad[i].viento);
                filtrarContenidoPorClaveAEntero(msg.mensaje, "Temperatura", &datos_ciudad[i].temperatura);
                filtrarContenidoPorClaveAEntero(msg.mensaje, "Lluvia", &datos_ciudad[i].lluvia);
                printf("--------------------------------------------\n");
                printf("Reportaje de la Ciudad %d\n", numero_ciudad+1);
                printf("Ciudad: %s\n", datos_ciudad[i].Nombre);
                printf("Viento: %d\n", datos_ciudad[i].viento);
                printf("Temperatura: %d\n", datos_ciudad[i].temperatura);
                printf("Lluvia: %d\n", datos_ciudad[i].lluvia);
                printf("--------------------------------------------\n");
                
            }

            
            break;
        
        case EVT_FIN:
            for ( i = 0; i < 6; i++) {
                if (numero_ciudad == datos_ciudad[i].nro_ciudad) {
                    fin++;
                    printf("Reportaje de la Ciudad %d terminado\n", numero_ciudad);
                }
            }
            break;
        }
        if (fin == 6)
        {
            printf("Se reportaron todas las ciudades\n");
            done = 1;
        }
    }
    printf("Noticiero Finalizado\n");
    
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
    eliminar_cola_mensajes(id_cola_mensajes);
	

    return 0;

}
