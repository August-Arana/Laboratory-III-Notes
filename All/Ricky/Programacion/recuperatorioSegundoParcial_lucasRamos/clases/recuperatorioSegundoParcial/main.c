#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "time.h"
#include "unistd.h"

#include "sys/ipc.h"
#include "sys/shm.h"
#include "pthread.h"

#include "def.h"
#include "funciones.h"
#include "archivo.h"
#include "claves.h"
#include "semaforos.h"
#include "memoria.h"
#include "cola.h"
#include "global.h"



int main(int arg,char *argv[]){

	/* variables */
	int *memoria=NULL;
	hormiga hormigas[3];
	int id_memoria;
	int id_semaforo;
	int done;
	int cantidad_hormigas;

	int nro_hormiga;
	int fin;
	int i;
	
	mensaje msg;
	int id_cola_mensajes;
	
	/*Inicializacion de variables*/
	done=0;
	fin=0;
	cantidad_hormigas=3;
	i=0;
	memoria = (int*)creoMemoria(sizeof(4), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicia_semaforo(id_semaforo,VERDE);

   	espera_semaforo(id_semaforo);
   	memoria[0] = 1;
   	levanta_semaforo(id_semaforo);

	/*Compruebo si el proceso generador de hilos esta corriendo*/
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
      		usleep(500 * 1000);
   	}
	
	for(i=0;i<cantidad_hormigas;i++){
		hormigas[i].contador_vueltas=0;
		hormigas[i].pasos_total=0;
	}
	
	/*Logica receptor/panel de mensajes*/
	while(done==0){
		
		recibir_mensaje(id_cola_mensajes,MSG_PISTA,&msg);
		nro_hormiga = msg.rte-MSG_HORMIGA;
		
		switch(msg.evento){
		
			case EVT_RESULTADO:

				if(nro_hormiga==0)
				{
					hormigas[0].contador_vueltas++;
					hormigas[0].pasos_total+=atoi(msg.mensaje);
				}
				else if(nro_hormiga==1)
				{
					hormigas[1].contador_vueltas++;
					hormigas[1].pasos_total+=atoi(msg.mensaje);
				}
				else
				{
					hormigas[2].contador_vueltas++;
					hormigas[2].pasos_total+=atoi(msg.mensaje);
				}
				
				system("clear");

				printf("\n----------------ESTADISTICAS CORREDORAS----------------\n");

				printf("\nEstadisticas Hormiga reina: ");
				printf("\nPasos: %d",hormigas[0].pasos_total);
				printf("\nVueltas: %d\n",hormigas[0].contador_vueltas);

				printf("\nEstadisticas Hormiga roja: ");
				printf("\nPasos: %d",hormigas[1].pasos_total);
				printf("\nVueltas: %d\n",hormigas[1].contador_vueltas);
				
				printf("\nEstadisticas Hormiga negra: ");
				printf("\nPasos: %d",hormigas[2].pasos_total);
				printf("\nVueltas: %d\n",hormigas[2].contador_vueltas);
				
				printf("\n-------------------------------------------------------\n");
			break;
			case EVT_FIN:

				if(nro_hormiga==0)
				{
					fin++;
				}
				if(nro_hormiga==1)
				{
					fin++;
				}
				if(nro_hormiga==2)
				{
					fin++;
				}
				
				if(fin==3)
				{
					done++;
				}
				

			break;

				

		}
		

	}
	/*Una vez terminada la carrera, verifico el ganador o si hubo un empate*/
	if(hormigas[0].contador_vueltas < hormigas[1].contador_vueltas && hormigas[0].contador_vueltas  < hormigas[2].contador_vueltas)
	{
		printf("\nLa ganadora con %d vueltas en total es",hormigas[0].contador_vueltas);
		for(i=0;i<5;i++){
		sleep(1);
		printf(".");
		fflush(stdout);
		}
		printf("\nLa hormiga reina !!!\n");


	}
	else if(hormigas[1].contador_vueltas < hormigas[0].contador_vueltas && hormigas[1].contador_vueltas  < hormigas[2].contador_vueltas)
	{
		printf("\nLa ganadora con %d vueltas en total es",hormigas[1].contador_vueltas);
		for(i=0;i<5;i++){
		sleep(1);
		printf(".");
		fflush(stdout);
		}
		printf("\nLa hormiga roja !!!\n");

	}
	else if(hormigas[2].contador_vueltas < hormigas[1].contador_vueltas && hormigas[2].contador_vueltas  < hormigas[0].contador_vueltas)
	{
		printf("\nLa ganadora con %d vueltas en total es",hormigas[2].contador_vueltas);
		for(i=0;i<5;i++){
		sleep(1);
		printf(".");
		fflush(stdout);
		}
		printf("\nla hormiga negra!!!\n");

	}
	else
	{
		printf("\nLa ganadora es");
		for(i=0;i<5;i++){
		sleep(1);
		printf(".");
		fflush(stdout);
		}
		printf("\nNingunaaa !!! hubo un empateee !!!\n");
		
	}

	/*limpieza*/
	shmdt ((int *)memoria);
	shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);	
	elimina_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
	return 0;



}
