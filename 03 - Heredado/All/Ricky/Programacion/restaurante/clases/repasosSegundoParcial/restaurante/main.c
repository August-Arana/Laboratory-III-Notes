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
	historialMenu historialMenus[3+1];
	int id_memoria;
	int id_semaforo;
	int done;
	int verificar_postre;
	int cantidad_menus;
	int nro_mesero;
	int fin;
	int i;
	
	mensaje msg;
	int id_cola_mensajes;
	
	/*Inicializacion de variables*/
	done=0;
	fin=0;
	verificar_postre=0;
	cantidad_menus=3;
	i=0;
	memoria = (int*)creoMemoria(sizeof(2), &id_memoria, CLAVE_BASE);
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	

	id_semaforo = creo_semaforo();
   	memoria[0] = 0;
   	inicia_semaforo(id_semaforo,VERDE);

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
      		usleep(500 * 1000);
   	}
	
	for(i=0;i<cantidad_menus;i++){
		
		historialMenus[i].dinero_obtenido=0;
		historialMenus[i].precioMenu=(1250 + i * 100);
		historialMenus[i].cantidad_menus_pedidos=0;
		historialMenus[i].cantidad_menus_conPostre=0;
		historialMenus[i].precioPostre=500;
		strcpy(historialMenus[i].descripcionMenu,argv[i+1]);
		
		
	}
	
	liberoMemoria(id_memoria,(int*)memoria);
	while(done==0){
		
		recibir_mensaje(id_cola_mensajes,MSG_PANEL,&msg);
		nro_mesero = msg.rte-MSG_MESERO;
		
		switch(msg.evento){
		
			case EVT_MENU1:

				verificar_postre=atoi(msg.mensaje);
				historialMenus[0].cantidad_menus_pedidos++;
					
				if(verificar_postre==1)
				{
					historialMenus[0].dinero_obtenido+=historialMenus[0].precioMenu;
					historialMenus[0].dinero_obtenido+=historialMenus[0].precioPostre;
					historialMenus[0].cantidad_menus_conPostre++;
					
				}
				else
				{
					historialMenus[0].dinero_obtenido+=historialMenus[0].precioMenu;
				}
				
				printf("\n--------------PEDIDO MENU1--------------");
				printf("\nMESERO: %d",nro_mesero+1);
				printf("\nDESCRIPCION: %s",historialMenus[0].descripcionMenu);

				if(verificar_postre==1)
				{
					printf("\nCON POSTRE? SI");
					printf("\nCOSTO: %d",(historialMenus[0].precioMenu+historialMenus[0].precioPostre));
				}
				else
				{
					printf("\nCON POSTRE? NO");
					printf("\nCOSTO: %d",historialMenus[0].precioMenu);
				}
			
				printf("\n----------------------------------------\n");
				
			break;
			
			case EVT_MENU2:
				
				verificar_postre=atoi(msg.mensaje);
				historialMenus[1].cantidad_menus_pedidos++;

				if(verificar_postre==1)
				{
					historialMenus[1].dinero_obtenido+=historialMenus[1].precioMenu;
					historialMenus[1].dinero_obtenido+=historialMenus[1].precioPostre;
					historialMenus[1].cantidad_menus_conPostre++;
				}
				else
				{
					historialMenus[1].dinero_obtenido+=historialMenus[1].precioMenu;
				}
				
				printf("\n--------------PEDIDO MENU2--------------");
				printf("\nMESERO: %d",nro_mesero+1);
				printf("\nDESCRIPCION: %s",historialMenus[1].descripcionMenu);
				if(verificar_postre==1)
				{
					printf("\nCON POSTRE? SI");
					printf("\nCOSTO: %d",(historialMenus[1].precioMenu+historialMenus[1].precioPostre));
				}
				else
				{
					printf("\nCON POSTRE? NO");
					printf("\nCOSTO: %d",historialMenus[1].precioMenu);
				}
			
				printf("\n----------------------------------------\n");				
				
			break;
			
			case EVT_MENU3:

				verificar_postre=atoi(msg.mensaje);
				historialMenus[2].cantidad_menus_pedidos++;
	
				if(verificar_postre==1)
				{
					historialMenus[2].dinero_obtenido+=historialMenus[2].precioMenu;
					historialMenus[2].dinero_obtenido+=historialMenus[2].precioPostre;
					historialMenus[2].cantidad_menus_conPostre++;
				}
				else
				{
					historialMenus[2].dinero_obtenido+=historialMenus[2].precioMenu;
				}
				
				printf("\n--------------PEDIDO MENU3--------------");
				printf("\nMESERO: %d",nro_mesero+1);
				printf("\nDESCRIPCION: %s",historialMenus[2].descripcionMenu);
				if(verificar_postre==1)
				{
					printf("\nCON POSTRE? SI");
					printf("\nCOSTO: %d",(historialMenus[2].precioMenu+historialMenus[2].precioPostre));
				}
				else
				{
					printf("\nCON POSTRE? NO");
					printf("\nCOSTO: %d",historialMenus[2].precioMenu);
				}
			
				printf("\n----------------------------------------\n");	
				
			break;
			
			case EVT_FIN:
			
				if(nro_mesero==0)
				{
					fin++;
				}
				else if(nro_mesero==1)
				{
					fin++;
				}
				else
				{
					fin++;
				}
				if(fin==3)
				{
					done++;
				}
				
			break;

			case EVT_NULO:
	
				printf("\n******* SE MANDO EL EVENTO NULO *******");
				
			break;	
			default:

				printf("\n******* Error inesperado *******");
			break;

		}
		

	}

	for(i=0;i<3;i++)
	{
		printf("\n--------------RESULTADOS VENTAS: MENU%d--------------",i+1);
		printf("\nDESCRIPCION MENU: %s",historialMenus[i].descripcionMenu);
		printf("\nCANTIDAD DE MENUS VENDIDOS: %d",historialMenus[i].cantidad_menus_pedidos);
		printf("\nCON POSTRE: %d",historialMenus[i].cantidad_menus_conPostre);
		printf("\nDINERO OBTENIDO: %d",historialMenus[i].dinero_obtenido);
		printf("\n-----------------------------------------------------\n",i+1);
		sleep(1);
	}
	
		
		
	elimina_semaforo(id_semaforo);
	borrar_mensajes(id_cola_mensajes);
	return 0;

}
