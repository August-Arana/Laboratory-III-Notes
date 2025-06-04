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
    int rondas;
    int nro_peleador;
    int nro_mensaje;
    char cadena[50];
    int ataque;
    int estado_juego;
    int bajas;
    

    
    hilo_peleadores datos_peleadores[CANTIDAD_JUGADORES];
	mensaje msg;
	int id_cola_mensajes;
    
    /* inicializacion */
    nro_mensaje = 0;
    estado_juego = 0;
    ataque = 0;
    bajas = 0;
    nro_peleador = 0;
    rondas = 0;
	done=0;
	i=0;
    fin = 0;
    memset(cadena,0,sizeof(cadena));


	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicio_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);
    
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
    for (i=0;i<CANTIDAD_JUGADORES;i++)
    {
        datos_peleadores[i].vida = 1;
    } 
    
    
    
    while (done == 0)
    {
        
        /*printf("Esperando mensajes\n");*/
        recibir_mensaje(id_cola_mensajes,MSG_CAMPO,&msg);
        nro_peleador = msg.rte-2 ;
        /*printf("Numero jugador %d\n", nro_peleador);*/
        if (nro_peleador < 0 || nro_peleador >= CANTIDAD_JUGADORES) {
        printf("Error: índice de jugador fuera de rango: %d\n", nro_peleador);
        continue; 
        }
        nro_mensaje = msg.rte;
        switch (msg.evento)
        {
            case EVT_INICIO:
                datos_peleadores[nro_peleador].nro_peleador = nro_peleador;
                datos_peleadores[nro_peleador].valor_critico = atoi(msg.mensaje);
                printf("Iniciando juego\n");
                printf("Numero jugador %d\n", nro_peleador);
                printf("Valor critico %d\n", datos_peleadores[nro_peleador].valor_critico);
                /*enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_INICIO, "");*/
                sleep(1);
            break;
            case EVT_VISION:
                printf("Vista del jugador %d\n", nro_peleador);
                if (estado_juego == 1) {
                    enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_FIN, "");
                    if (datos_peleadores[3].vida == 0) {
                        printf("Guerreros han Ganado\n");

                    }
                    fin++;

                }
                if (estado_juego == 0) {
                    if (datos_peleadores[nro_peleador].vida == 1) {
                        printf("El jugador %d tiene %d de vida\n", nro_peleador, datos_peleadores[nro_peleador].vida);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_PREPARACION, ""); 
                    }
                    if (datos_peleadores[nro_peleador].vida == 0) {
                        printf("El jugador %d ha muerto\n", nro_peleador);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_FIN, "");
                        fin++;
                    }
                }
            break;
            

            case EVT_ATAQUE:
                ataque = atoi(msg.mensaje);
                if (nro_peleador>=0 && nro_peleador<3) {
                    printf("\n\n-----Ataque de Guerro-----\n\n");
                    printf("El Guerrero %d ha atacado al Destructor\n", nro_peleador);
                    printf("Ataque %d\n", ataque);
                    if (ataque == datos_peleadores[3].valor_critico) {
                        printf("El Guerrero %d ha matado al Destructor\n", nro_peleador);
                        datos_peleadores[3].vida = 0;
                        estado_juego = 1;
                        
                    }
                    else {
                        printf("El Guerrero %d ha fallado\n", nro_peleador);
                    }
                    printf("\n---Fin de ataque---\n");
                }
                if (nro_peleador==3) {
                    printf("\n\n-----Ataque de Destructor-----\n\n");
                    printf("El Destructor ha atacado a los Guerreros\n");
                    printf("Ataque %d\n", ataque);
                    if (ataque == datos_peleadores[0].valor_critico) {
                        if (datos_peleadores[0].vida == 1) {
                            printf("El Destructor ha matado al Guerrero %d\n",datos_peleadores[0].nro_peleador);
                            printf("Vida del Guerrero %d\n", datos_peleadores[0].vida);
                            datos_peleadores[0].vida = 0;
                            printf("Vida del Guerrero %d\n", datos_peleadores[0].vida);
                            bajas++;
                            
                        }
                            if (datos_peleadores[2].vida == 0) {
                            printf("YA NO HAY GUERRERO\n");
                            
                        }
                        

                    }
                    if (ataque == datos_peleadores[1].valor_critico) {
                        if (datos_peleadores[1].vida == 1) {
                            printf("El Destructor ha matado al Guerrero %d\n",datos_peleadores[1].nro_peleador);
                            printf("Vida del Guerrero %d\n", datos_peleadores[1].vida);
                            datos_peleadores[1].vida = 0;
                            printf("Vida del Guerrero %d\n", datos_peleadores[1].vida);
                            bajas++;
                            
                        }
                            if (datos_peleadores[2].vida == 0) {
                            printf("YA NO HAY GUERRERO\n");
                            
                        }
                    }
                    if (ataque == datos_peleadores[2].valor_critico) {
                        if (datos_peleadores[2].vida == 1) {
                            printf("El Destructor ha matado al Guerrero %d\n",datos_peleadores[2].nro_peleador);
                            printf("Vida del Guerrero %d\n", datos_peleadores[2].vida);
                            datos_peleadores[2].vida = 0;
                            printf("Vida del Guerrero %d\n", datos_peleadores[2].vida);
                            bajas++;
                            
                        }
                            if (datos_peleadores[2].vida == 0) {
                            printf("YA NO HAY GUERRERO\n");
                            
                        }
                    }
                    printf("\n---Fin de ataque---\n");
                    
                    if (bajas == 3) {
                        estado_juego = 1;
                        printf("\n\nEl Destructor ha Ganado\n\n");
                    }
                }
                    
                

            break; 
        }
        memset(cadena,0,sizeof(cadena));
        if (fin == CANTIDAD_JUGADORES)
        {
            done = 1;
        }
        
                
    }
    
    

    
    voLiberar_memoria(memoria, id_memoria);
    eliminar_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
    eliminar_cola_mensajes(id_cola_mensajes);
	

    return 0;

}
