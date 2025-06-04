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
#include "archivos.h"

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
    char suceso[100+1];
    int ataque;
    int estado_juego;
    int objetivo1;
    int objetivo2;
    int bajas1;
    int bajas2;   
    int pulgar;

    
    hilo_peleadores datos_peleadores[CANTIDAD_JUGADORES];
	mensaje msg;
	int id_cola_mensajes;
    
    /* inicializacion */
    objetivo1=0;
    objetivo2=0;
    pulgar=0;
    nro_mensaje = 0;
    estado_juego = 0;
    ataque = 0;
    bajas1 = 0;
    bajas2 =0;
    nro_peleador = 0;
    rondas = 0;
	done=0;
	i=0;
    fin = 0;
    memset(suceso,0,sizeof(suceso));
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
        datos_peleadores[i].nro_peleador=i;
        datos_peleadores[i].vida = 100;
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
               /* datos_peleadores[nro_peleador].nro_peleador = nro_peleador;
                datos_peleadores[nro_peleador].vida = atoi(msg.mensaje);*/
                printf("Iniciando juego\n");
                printf("Numero jugador %d\n", nro_peleador);
                printf("Vida %d\n", datos_peleadores[nro_peleador].vida);
                /*enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_INICIO, "");*/
                sleep(1);
            break;
            case EVT_VISION:
                
                printf("Vista del jugador %d\n", nro_peleador);
                if (estado_juego == 1) {
                    printf("Luchadores han Ganado\n");
                    if (!inAbrirArchivo("suceso.txt", "a")) {
                            printf("Error al abrir archivo \n");
                            continue;
                    }
                    sprintf(suceso,"Combatiente %d ha salido con vida",nro_peleador);
                    inEscribirArchivo(suceso);
                    voCerrarArchivo;
                    memset(suceso,0,sizeof(suceso));


                    enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_FIN, "");
                    

                    fin++;

                }
                if (estado_juego == 2) {
                    
                    printf("Gladiadores han ganado\n");
                    printf("pero...\n");
                    pulgar=inDevolverNumeroAleatorio(1,2);
                    if(pulgar == 1){
                        sprintf(cadena,"Gladiador Ejecutado\n");
                        if (!inAbrirArchivo("suceso.txt", "a")) {
                            printf("Error al abrir archivo \n");
                            continue;
                        }
                        sprintf(suceso,"Combatiente %d ha muerto\n",nro_peleador);
                        inEscribirArchivo(suceso);
                        voCerrarArchivo;
                        memset(suceso,0,sizeof(suceso));
                    }
                    if(pulgar==2){
                        sprintf(cadena,"Gladiador Liberado\n");
                        if (!inAbrirArchivo("suceso.txt", "a")) {
                            printf("Error al abrir archivo \n");
                            continue;
                        }
                        sprintf(suceso,"Combatiente %d ha salido con vida\n",nro_peleador);
                        inEscribirArchivo(suceso);
                        voCerrarArchivo;
                        memset(suceso,0,sizeof(suceso));
                    }
                    enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_FIN, cadena);

                    fin++;

                }
                if (estado_juego == 0) {
                    if (datos_peleadores[nro_peleador].vida > 0) {
                        printf("El jugador %d tiene %d de vida\n", nro_peleador, datos_peleadores[nro_peleador].vida);
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_PREPARACION, ""); 
                    }
                    if (datos_peleadores[nro_peleador].vida <= 0) {
                        printf("El jugador %d ha muerto\n", nro_peleador);
                        if (!inAbrirArchivo("suceso.txt", "a")) {
                            printf("Error al abrir archivo \n");
                            continue;
                        }
                        sprintf(suceso,"Combatiente %d ha muerto",nro_peleador);
                        inEscribirArchivo(suceso);
                        voCerrarArchivo;
                        memset(suceso,0,sizeof(suceso));
                        enviar_mensaje(id_cola_mensajes, nro_mensaje, MSG_CAMPO, EVT_FIN, "");
                        fin++;
                    }
                }
            break;
            

            case EVT_ATAQUE:
                ataque = atoi(msg.mensaje);
                if (nro_peleador>=0 && nro_peleador<5) {
                    printf("\n\n-----Ataque de Luchador-----\n\n");
                    printf("El Luchador %d ha atacado\n", nro_peleador);
                    printf("Ataque %d\n", ataque);
                    if(objetivo1==0){
                        datos_peleadores[5].vida-=ataque;
                    }
                    if(objetivo1==1){
                        datos_peleadores[6].vida-=ataque;
                    }
                    if(objetivo1==2){
                        datos_peleadores[7].vida-=ataque;
                    }
                    if (datos_peleadores[5].vida<=0){
                        printf("Murio el Gladiador %d\n",datos_peleadores[5].nro_peleador);
                        objetivo1=1;
                    }
                    if (datos_peleadores[6].vida<=0){
                        printf("Murio el Gladiador %d\n",datos_peleadores[6].nro_peleador);
                        objetivo1=2;
                    }
                    if (datos_peleadores[7].vida<=0){
                        printf("Murio el Maximo\n");
                        estado_juego=1;
                        objetivo1=4;
                    }
                    
                    printf("\n---Fin de ataque---\n");
                }
                if (nro_peleador>=5 && nro_peleador <= 8) {
                    printf("\n\n-----Ataque de Gladiador-----\n\n");
                    printf("El Gladiador %d ha atacado a los Luchadores\n",nro_peleador);
                    printf("Ataque %d\n", ataque);
                    if(objetivo2==0){
                        datos_peleadores[0].vida-=ataque;
                    }
                    if(objetivo2==1){
                        datos_peleadores[1].vida-=ataque;
                    }
                    if(objetivo2==2){
                        datos_peleadores[2].vida-=ataque;
                    }
                    if(objetivo2==3){
                        datos_peleadores[3].vida-=ataque;
                    }
                    if(objetivo2==4){
                        datos_peleadores[4].vida-=ataque;
                    }
                    if (datos_peleadores[0].vida<=0){
                        printf("Murio el Luchador %d\n",datos_peleadores[0].nro_peleador);
                        objetivo2=1;
                    }
                    if (datos_peleadores[1].vida<=0){
                        printf("Murio el Luchador %d\n",datos_peleadores[1].nro_peleador);
                            objetivo2=2;
                    }
                    if (datos_peleadores[2].vida<=0){
                        printf("Murio el Luchador %d\n",datos_peleadores[2].nro_peleador);
                        objetivo1=3;
                    }
                    if (datos_peleadores[3].vida<=0){
                        printf("Murio el Luchador %d\n",datos_peleadores[3].nro_peleador);
                        objetivo1=4;
                    }
                    if (datos_peleadores[4].vida<=0){
                        printf("Murio el Luchador %d\n",datos_peleadores[4].nro_peleador);
                        estado_juego=2;
                        objetivo1=5;
                    }
                   
                    
                    printf("\n---Fin de ataque---\n");
                    
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
